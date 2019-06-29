import torch
from torch.autograd import Variable

from sensitivity_analysis.model import MNIST_CNN
from utils.utils import get_all_digit_imgs

import numpy as np
import matplotlib.pyplot as plt

# the model is trained and saved on gpu and load weight on cpu
is_training_on_gpu = True
model = MNIST_CNN()
if torch.cuda.is_available():
    model = model.cuda()
if is_training_on_gpu:
    weights = torch.load('cnn_weights.pkl', map_location=lambda storage, loc: storage)
else:
    weights = torch.load('cnn_weights.pkl')
model.load_state_dict(weights)

imgs = get_all_digit_imgs('../dataset/mnist')
print(imgs.shape)
if torch.cuda.is_available():
    imgs = Variable(imgs, requires_grad=True).cuda()
else:
    imgs = Variable(imgs, requires_grad=True)

logits = model(imgs)

logits.backward(torch.ones(logits.size()))

gradients = imgs.grad.data.numpy()
# reset grad to zero in same case(e.g. training) because gradient is accumulated when automatically computed .
# imgs.grad.data.zero_()

assert gradients.shape == (10, 1, 28, 28)
gradients = np.squeeze(np.square(gradients), 1).reshape(10, 784)

sample_imgs = imgs.data.numpy()
plt.figure(figsize=(7, 7))
for i in range(5):
    plt.subplot(5, 2, 2 * i +1)
    plt.imshow(np.reshape(sample_imgs[2 * i,:], (28, 28)), cmap='gray')
    plt.imshow(np.reshape(gradients[2 * i,:], (28, 28)), cmap='hot', alpha=0.5)
    plt.title('Digit:{}'.format(2 * i))

    plt.subplot(5, 2, 2 * i + 2)
    plt.imshow(np.reshape(sample_imgs[2 *i + 1, :], (28, 28)), cmap='gray')
    plt.imshow(np.reshape(gradients[2*i + 1, :], (28, 28)), cmap='hot', alpha=0.5)
    plt.title('Digit:{}'.format(2 * i + 1))

plt.tight_layout()
plt.show()