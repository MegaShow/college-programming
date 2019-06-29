import torch
from torch.autograd import Variable
from torch import nn, optim

import matplotlib.pyplot as plt
import numpy as np

from class_prototype.model import MNIST_DNN
from utils.utils import set_parameters_static
from utils.utils import get_img_means

lmda = 0.1

class Prototype(nn.Module):
    def __init__(self):
        super(Prototype, self).__init__()


criterion = nn.CrossEntropyLoss()
regular = nn.MSELoss()

model = MNIST_DNN()
if torch.cuda.is_available():
    model = model.cuda()

model.load_state_dict(torch.load('MNIST_CNN.pkl'))
# don't update parameters of original model
model = set_parameters_static(model)

# init images and labels:0-9
x_prototype = torch.zeros(10, 784)
y_prototype = torch.linspace(0, 9, 10)
y_prototype = y_prototype.type(torch.LongTensor)
if torch.cuda.is_available():
    x_prototype = Variable(x_prototype, requires_grad=True).cuda()
    y_prototype = Variable(y_prototype).cuda()
else:
    x_prototype = Variable(x_prototype, requires_grad=True)
    y_prototype = Variable(y_prototype)

imgs_means = get_img_means('../dataset/mnist')
if torch.cuda.is_available():
    imgs_means = Variable(imgs_means).cuda()
else:
    imgs_means = Variable(imgs_means)

optimizer = optim.Adam([x_prototype], lr=0.01)

for i in range(10000):
    optimizer.zero_grad()
    logits_prototype = model(x_prototype)
    cost_protype = criterion(logits_prototype, y_prototype) + lmda * regular(x_prototype, imgs_means)
    cost_protype.backward()
    optimizer.step()
    if i % 500 == 0:
        print('cost_protype={:.6f}'.format(cost_protype.item()))

x_prototype = x_prototype.data.numpy()

assert x_prototype.shape == (10, 784)
plt.figure(figsize=(7, 7))
for i in range(5):
    left = x_prototype[2*i,:].reshape(28, 28)
    plt.subplot(5, 2, 2 * i +1)
    plt.imshow(left, cmap='gray', interpolation='none')
    plt.title('Digit:{}'.format(2 * i))
    plt.colorbar()

    right = x_prototype[2*i+1,:].reshape(28, 28)
    plt.subplot(5, 2, 2 * i + 2)
    plt.imshow(right, cmap='gray', interpolation='none')
    plt.title('Digit:{}'.format(2 * i + 1))
    plt.colorbar()

plt.tight_layout()
plt.show()
