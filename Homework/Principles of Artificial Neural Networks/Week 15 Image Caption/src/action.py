"""Action"""

import torch
import torch.nn as nn
import torch.nn.functional as F
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import skimage.transform
from scipy.misc import imread, imresize
from PIL import Image

class Action:
    def __init__(self):
        super(Action, self).__init__()
        # sets device for model and PyTorch tensors
        pass


    def get_optimizer(self, model, learning_rate):
        """Get optimizer"""
        optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)
        return optimizer

    def get_loss_fn(self):
        """Get loss function"""
        loss_fn = nn.CrossEntropyLoss()
        return loss_fn

    def clip_gradient(self, optimizer, grad_clip):
        """
        Clips gradients computed during backpropagation to avoid explosion of gradients.

        :param optimizer: optimizer with the gradients to be clipped
        :param grad_clip: clip value
        """
        for group in optimizer.param_groups:
            for param in group["params"]:
                if param.grad is not None:
                    param.grad.data.clamp_(-grad_clip, grad_clip)

    def caption_by_beam_search(self, decoder, encoder_out, word_map, beam_size=5):
        """Caption by beam search

        :param decoder: decoder model
        :param beam_size: number of sequences to consider at each decode-step
        :return: caption, weights for visualization
        """
        device = encoder_out.device
        vocab_size = len(word_map)

        # Lists to store completed sequences, their alphas and scores
        complete_seqs = list()
        complete_seqs_alpha = list()
        complete_seqs_scores = list()

        enc_image_size = encoder_out.size(1)
        # Tensor to store top k previous words at each step;
        # now they're just <start>
        k_prev_words = torch.LongTensor([[word_map["<start>"]]] * beam_size).to(device)
        # Tensor to store top k sequences; now they're just <start>
        seqs = k_prev_words

        # Tensor to store top k sequences' scores; now they're just 0
        top_k_scores = torch.zeros(beam_size, 1).to(device)

        # Tensor to store top k sequences' alphas; now they're just 1s
        # (k, 1, enc_image_size, enc_image_size)
        seqs_alpha = torch.ones(beam_size, 1, enc_image_size,
                                enc_image_size).to(device)

        # Start decoding
        step = 1
        h, c = decoder.init_hidden_state(encoder_out)

        # s is a number less than or equal to k,
        # because sequences are removed from this process once they hit <end>
        while True:
            # (s, embed_dim)
            embeddings = decoder.embedding(k_prev_words).squeeze(1)
            attention_weighted_encoding, alpha = \
                decoder.attention(encoder_out, h)
            # (s, enc_image_size, enc_image_size)
            alpha = alpha.view(-1, enc_image_size, enc_image_size)
            # gating scalar, (s, encoder_dim)
            gate = decoder.sigmoid(decoder.f_beta(h))
            attention_weighted_encoding = gate * attention_weighted_encoding

            # (s, decoder_dim)
            h, c = decoder.decode_step(torch.cat([embeddings, \
                attention_weighted_encoding], dim=1), (h, c))

            # (s, vocab_size)
            scores = decoder.fc(h)
            scores = F.log_softmax(scores, dim=1)

            # Add
            # (s, vocab_size)
            scores = top_k_scores.expand_as(scores) + scores

            # For the first step, all k points will have the same
            # scores (since same k previous words, h, c)
            if step == 1:
                top_k_scores, top_k_words = scores[0].topk(beam_size, 0)
            else:
                top_k_scores, top_k_words = scores.view(-1).topk(beam_size, 0)

            # Convert unrolled indices to actual indices of scores
            prev_word_inds = top_k_words / vocab_size  # (s)
            next_word_inds = top_k_words % vocab_size  # (s)

            # Add new words to sequences, alphas
            # (s, step+1)
            seqs = torch.cat([seqs[prev_word_inds], next_word_inds.unsqueeze(1)], dim=1)
            # (s, step+1, enc_image_size, enc_image_size)
            seqs_alpha = torch.cat([seqs_alpha[prev_word_inds], alpha[prev_word_inds].unsqueeze(1)],
                                   dim=1)

            # Which sequences are incomplete (didn't reach <end>)?
            incomplete_inds = [ind for ind, next_word in enumerate(next_word_inds) if
                               next_word != word_map['<end>']]
            complete_inds = list(set(range(len(next_word_inds))) - set(incomplete_inds))

            # Set aside complete sequences
            if len(complete_inds) > 0:
                complete_seqs.extend(seqs[complete_inds].tolist())
                complete_seqs_alpha.extend(seqs_alpha[complete_inds].tolist())
                complete_seqs_scores.extend(top_k_scores[complete_inds])
            # reduce beam length accordingly
            beam_size -= len(complete_inds)

            # Proceed with incomplete sequences
            if beam_size == 0:
                break
            seqs = seqs[incomplete_inds]
            seqs_alpha = seqs_alpha[incomplete_inds]
            h = h[prev_word_inds[incomplete_inds]]
            c = c[prev_word_inds[incomplete_inds]]
            encoder_out = encoder_out[prev_word_inds[incomplete_inds]]
            top_k_scores = top_k_scores[incomplete_inds].unsqueeze(1)
            k_prev_words = next_word_inds[incomplete_inds].unsqueeze(1)

            # Break if things have been going on too long
            if step > 50:
                break
            step += 1

        i = complete_seqs_scores.index(max(complete_seqs_scores))
        seq = complete_seqs[i]
        alphas = complete_seqs_alpha[i]

        return seq, alphas

    def visualize_att(self, image, seq, alphas, rev_word_map, smooth=True):
        """
        Visualizes caption with weights at every word.

        Adapted from paper authors' repo: https://github.com/kelvinxu/arctic-captions/blob/master/alpha_visualization.ipynb

        :param image: image that has been captioned
        :param seq: caption
        :param alphas: weights
        :param rev_word_map: reverse word mapping, i.e. ix2word
        :param smooth: smooth weights?
        """
        words = [rev_word_map[ind] for ind in seq]

        for t in range(len(words)):
            if t > 50:
                break
            plt.subplot(np.ceil(len(words) / 5.), 5, t + 1)

            plt.text(0, 1, '%s' % (words[t]), color='black', backgroundcolor='white', fontsize=12)
            plt.imshow(image)
            current_alpha = alphas[t, :]
            if smooth:
                alpha = skimage.transform.pyramid_expand(current_alpha.numpy(), upscale=24, sigma=8)
            else:
                alpha = skimage.transform.resize(current_alpha.numpy(), [14 * 24, 14 * 24])
            if t == 0:
                plt.imshow(alpha, alpha=0)
            else:
                plt.imshow(alpha, alpha=0.8)
            plt.set_cmap(cm.Greys_r)
            plt.axis('off')
        plt.show()


class AverageMeter:
    """
    Keeps track of most recent, average, sum, and count of a metric.
    """

    def __init__(self):
        self.reset()

    def reset(self):
        self.val = 0
        self.avg = 0
        self.sum = 0
        self.count = 0

    def update(self, val, n=1):
        self.val = val
        self.sum += val * n
        self.count += n
        self.avg = self.sum / self.count
