import torch
from torchvision import datasets, transforms
import numpy as np


def exp_lr_scheduler(optimizer, epoch, init_lr=0.01, lr_decay_epoch=5):
    """Decay learning rate by a factor of 0.1 every lr_decay_epoch epochs."""
    lr = init_lr * (0.1 ** (epoch // lr_decay_epoch))

    for param_group in optimizer.param_groups:
        param_group['lr'] = lr

    return optimizer


def set_parameters_static(model):
    for para in list(model.parameters()):
        para.requires_grad = False
    return model


def get_img_means(path):
    train_mnist = datasets.MNIST(path, train=True, download=True, transform=transforms.ToTensor())

    mnist_imgs = [data[0].view(1, 784).numpy() for data in train_mnist]
    mnist_labels = [data[1] for data in train_mnist]

    imgs_means = np.zeros((10, 784))
    for i in range(10):
        imgs = []
        for index, label in enumerate(mnist_labels):
            if label == i:
                imgs.append(mnist_imgs[index])
        imgs_means[i, :] = np.mean(imgs, axis=0)
    return torch.from_numpy(imgs_means).type(torch.FloatTensor)


def get_all_digit_imgs(path, is_feed_cnn=True):
    train_mnist = datasets.MNIST(path, train=True, download=True, transform=transforms.ToTensor())
    if is_feed_cnn:
        mnist_imgs = [data[0].numpy() for data in train_mnist]
        mnist_labels = [data[1] for data in train_mnist]
    else:
        mnist_imgs = [data[0].view(784,).numpy() for data in train_mnist]
        mnist_labels = [data[1] for data in train_mnist]

    imgs = [mnist_imgs[mnist_labels.index(i)] for i in range(10)]

    return torch.from_numpy(np.array(imgs)).type(torch.FloatTensor)


def pixel_range(img):
    vmin, vmax = np.min(img), np.max(img)
    if vmin * vmax >= 0:
        return (vmin, vmax)
    else:
        if -vmin > vmax:
            vmax = -vmin
        else:
            vmin = -vmax

        return (vmin, vmax)

if __name__ == '__main__':
    # imgs = get_all_digit_imgs(is_feed_cnn=False)
    print(get_img_means('../dataset/mnist').size())
    # assert imgs.size() == (10, 1, 28, 28) or imgs.size() == (10, 784)
    # sample_imgs = get_img_means()
    # assert sample_imgs.size() == (10, 784)
