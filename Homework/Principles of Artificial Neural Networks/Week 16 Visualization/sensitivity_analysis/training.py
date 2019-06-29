import torch
from torch.autograd import Variable
from torchvision import datasets, transforms
from torch.utils.data import DataLoader
from torch import nn, optim


class MNIST_CNN(nn.Module):
    def __init__(self):
        super(MNIST_CNN, self).__init__()

        # layer1
        self.layer1 = nn.Sequential(nn.Conv2d(1, 32, 3, stride=1, padding=1), nn.ReLU(True),
                                    nn.MaxPool2d(2, 2, padding=1), nn.Dropout(p=0.7))
        # layer2
        self.layer2 = nn.Sequential(nn.Conv2d(32, 64, 3, stride=1, padding=1), nn.ReLU(True),
                                    nn.MaxPool2d(2, 2, padding=1), nn.Dropout(p=0.7))

        # layer3
        self.layer3 = nn.Sequential(nn.Conv2d(64, 128, 3, stride=1, padding=1), nn.ReLU(True),
                                    nn.MaxPool2d(2, 2, padding=1), nn.Dropout(p=0.7))

        # layer4
        self.layer4 = nn.Sequential(nn.Linear(128 * 5 * 5, 625), nn.ReLU(True),
                                    nn.Dropout(0.5))

        # layer5
        self.layer5 = nn.Sequential(nn.Linear(625, 10))

    def forward(self, x):
        x = self.layer1(x)
        x = self.layer2(x)
        x = self.layer3(x)
        x = x.view(-1, 128 * 5 * 5)
        x = self.layer4(x)
        x = self.layer5(x)
        return x


def exp_lr_scheduler(optimizer, epoch, init_lr=0.01, lr_decay_epoch=5):
    """Decay learning rate by a factor of 0.1 every lr_decay_epoch epochs."""
    lr = init_lr * (0.1 ** (epoch // lr_decay_epoch))

    for param_group in optimizer.param_groups:
        param_group['lr'] = lr

    return optimizer


# training settings
batch_size = 32
init_lr = 1e-2
epochs = 15

train_mnist = datasets.MNIST('../dataset/mnist', train=True, download=True, transform=transforms.ToTensor())
test_mnist = datasets.MNIST('../dataset/mnist', train=False, download=True, transform=transforms.ToTensor())
train_loader = DataLoader(train_mnist, batch_size=batch_size, shuffle=True)
test_loader = DataLoader(test_mnist, batch_size=batch_size, shuffle=False)

model = MNIST_CNN()
if torch.cuda.is_available():
    model = model.cuda()

criterion = nn.CrossEntropyLoss()
optimizer = optim.SGD(model.parameters(), lr=init_lr, momentum=0.9)

for epoch in range(epochs):
    running_loss = 0.0
    running_acc = 0.0
    print('epoch {0}'.format(epoch + 1))
    print('*' * 10)
    for i, data in enumerate(train_loader, 1):
        img, label = data
        if torch.cuda.is_available():
            img = Variable(img).cuda()
            label = Variable(label).cuda()
        else:
            img = Variable(img)
            label = Variable(label)
        out = model(img)
        loss = criterion(out, label)

        # the loss of (i * batch_size) images
        running_loss += loss.item() * label.size(0)
        _, pred = torch.max(out, 1)
        num_correct = (pred == label).sum()
        running_acc += num_correct.item()

        optimizer = exp_lr_scheduler(optimizer=optimizer, epoch=epoch + 1, init_lr=init_lr)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        if i % 500 == 0:
            print('{}/{} Loss: {:.6f}, Acc: {:.6f}'.format(epoch + 1, epochs, running_loss / (batch_size * i),
                                                           running_acc / (batch_size * i)))

    print('Finish {} epochs, Loss:{:.6f}, Acc:{:.6f}'.format(epoch + 1,
                                                             running_loss / len(train_mnist),
                                                             running_acc / len(train_mnist)))

    model.eval()
    eval_loss = 0.0
    eval_acc = 0.0
    with torch.no_grad():
        for data in test_loader:
            img, label = data

            if torch.cuda.is_available():
                img = Variable(img).cuda()
                label = Variable(label).cuda()
            else:
                img = Variable(img)
                label = Variable(label)
            out = model(img)
            _, pred = torch.max(out, 1)
            loss = criterion(out, label)
            eval_loss += loss.item()

            num_correct = (pred == label).sum()
            eval_acc += num_correct.item()

    print('Test Loss: {:.6f}, Acc: {:.6f}'.format(eval_loss / len(test_mnist), eval_acc / len(test_mnist)))

torch.save(model.state_dict(), 'cnn_weights.pkl')

# best result :Test Loss: 0.000653, Acc: 0.993000