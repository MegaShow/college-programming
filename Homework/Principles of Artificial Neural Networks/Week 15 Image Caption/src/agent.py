"""Agent"""

import torch
from torch.nn.utils.rnn import pack_padded_sequence

from net import Decoder, Encoder
from action import Action, AverageMeter
from dataset import Dataset

class Agent:
    def __init__(self):
        super(Agent, self).__init__()
        #self.config = config
        self.action = Action()
        self.dataset = Dataset()

        self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
        self.grad_clip = 5

        embed_dim = 512 # dimension of word embeddings
        decoder_dim = 512  # dimension of decoder RNN
        dropout = 0.5
        #batch_size = 32
        self.n_epochs = 20

        self.encoder = Encoder()
        self.decoder = Decoder(embed_dim=embed_dim,
                               decoder_dim=decoder_dim,
                               vocab_size=self.dataset.get_word_map_len(),
                               dropout=dropout)

    def fit(self):
        """fit model"""
        self.run(self.encoder, self.decoder)


    def run(self, encoder, decoder):
        """Main function to run"""
        device = self.device

        encoder_lr = 1e-4  # learning rate for encoder if fine-tuning
        decoder_lr = 4e-4  # learning rate for decoder
        encoder_optimizer = self.action.get_optimizer(encoder, encoder_lr)
        decoder_optimizer = self.action.get_optimizer(decoder, decoder_lr)

        encoder = encoder.to(device)
        decoder = decoder.to(device)

        loss_fn = self.action.get_loss_fn().to(device)

        train_loader, val_loader = self.dataset.get_dataloader()

        for epoch in range(self.n_epochs):
            self.train_epoch(train_loader, encoder, decoder, loss_fn,
                             encoder_optimizer, decoder_optimizer, epoch)
            self.eval_epoch(val_loader, encoder, decoder, loss_fn, epoch)


    def train_epoch(self, train_loader, encoder, decoder, loss_fn,
                    encoder_optimizer, decoder_optimizer, epoch):
        """
        Performs one epoch's training.

        :param train_loader: DataLoader for training data
        :param encoder: encoder model
        :param decoder: decoder model
        :param criterion: loss layer
        :param encoder_optimizer: optimizer to update encoder's weights (if fine-tuning)
        :param decoder_optimizer: optimizer to update decoder's weights
        """
        device = self.device
        grad_clip = self.grad_clip
        encoder.train()
        decoder.train()

        losses = AverageMeter()

        for idx, (imgs, caps, caplens) in enumerate(train_loader):

            # Move to GPU, if available
            imgs = imgs.to(device)
            caps = caps.to(device)
            caplens = caplens.to(device)

            # Forward prop.
            imgs = encoder(imgs)
            scores, caps_sorted, decode_lengths, alphas, sort_ind = \
                decoder(imgs, caps, caplens)

            # Since we decoded starting with <start>, the targets are
            # all words after <start>, up to <end>
            targets = caps_sorted[:, 1:]

            # Remove timesteps that we didn't decode at, or are pads
            # pack_padded_sequence is an easy trick to do this
            #TODO
            scores = pack_padded_sequence(scores, decode_lengths, batch_first=True)
            targets = pack_padded_sequence(targets, decode_lengths, batch_first=True)
            scores = scores[0]
            targets = targets[0]

            # Calculate loss
            loss = loss_fn(scores, targets)

            if alphas is not None:
                loss += (1 - alphas.sum(dim=1) ** 2).mean()

            # Back prop.
            decoder_optimizer.zero_grad()
            if encoder_optimizer is not None:
                encoder_optimizer.zero_grad()
            loss.backward()

            # Clip gradients
            if self.grad_clip is not None:
                self.action.clip_gradient(decoder_optimizer, grad_clip)
                if encoder_optimizer is not None:
                    self.action.clip_gradient(encoder_optimizer, grad_clip)

            # Update weights
            decoder_optimizer.step()
            if encoder_optimizer is not None:
                encoder_optimizer.step()

            losses.update(loss.item(), sum(decode_lengths))

            if idx % 100:
                print(">>Epoch(Train): [{0}][{1}/{2}]\tLoss {loss.avg:.4f}".format
                      (epoch, idx, len(train_loader), loss=losses))

    def eval_epoch(self, val_loader, encoder, decoder, loss_fn, epoch):
        """
        Performs one epoch's validation.

        :param val_loader: DataLoader for validation data.
        :param encoder: encoder model
        :param decoder: decoder model
        :param criterion: loss layer
        """
        device = self.device
        decoder.eval()
        encoder.eval()

        losses = AverageMeter()

        with torch.no_grad():
            for idx, (imgs, caps, caplens, allcaps) in enumerate(val_loader):
                # Move to device, if available
                imgs = imgs.to(device)
                caps = caps.to(device)
                caplens = caplens.to(device)

                # Forward prop.
                imgs = encoder(imgs)
                scores, caps_sorted, decode_lengths, alphas, sort_ind = \
                    decoder(imgs, caps, caplens)

                # Since we decoded starting with <start>, the targets are all
                # words after <start>, up to <end>
                targets = caps_sorted[:, 1:]
                scores = pack_padded_sequence(scores, decode_lengths, batch_first=True)
                targets = pack_padded_sequence(targets, decode_lengths, batch_first=True)
                scores = scores[0]
                targets = targets[0]

                # Calculate loss
                loss = loss_fn(scores, targets)

                if alphas is not None:
                    loss += (1 - alphas.sum(dim=1) ** 2).mean()

                losses.update(loss.item(), sum(decode_lengths))

                if idx % 100 == 0:
                    print(">>Epoch(Eval): [{epoch}][{idx}/{iters}]\tLoss \
                        {loss.avg:.4f}".format(
                            epoch=epoch, idx=idx, iters=len(val_loader),
                            loss=losses))

    def caption_image_beam_search(self):
        """
        captions images with beam search.

        :param encoder: encoder model
        :param decoder: decoder model
            :param image_path: path to image
        :param word_map: word map
        :param beam_size: number of sequences to consider at each decode-step
        :return: caption, weights for visualization
        """
        # Load image
        #  Get caption by beam search
        pass

