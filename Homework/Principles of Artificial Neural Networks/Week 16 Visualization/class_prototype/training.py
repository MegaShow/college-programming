import torch
from torch.autograd import Variable
from torchvision import datasets, transforms
from torch.utils.data import DataLoader
from torch import nn, optim

from class_prototype.model import MNIST_DNN
from utils.utils import exp_lr_scheduler

# training settings
batch_size = 32
init_lr = 1e-2
epochs = 50

train_mnist = datasets.MNIST('../dataset/mnist', train=True, download=True, transform=transforms.ToTensor())
test_mnist = datasets.MNIST('../dataset/mnist', train=False, download=True, transform=transforms.ToTensor())
train_loader = DataLoader(train_mnist, batch_size=batch_size, shuffle=True)
test_loader = DataLoader(test_mnist, batch_size=batch_size, shuffle=False)

model = MNIST_DNN()
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
        img = img.view(img.size(0), -1)
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

        optimizer = exp_lr_scheduler(optimizer=optimizer, epoch =epoch + 1, init_lr=init_lr)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        if i % 500 == 0:
            print('{}/{} Loss: {:.6f}, Acc: {:.6f}'.format(epoch + 1,epochs,running_loss/(batch_size * i),
                                                               running_acc/(batch_size * i)))

    print('Finish {} epochs, Loss:{:.6f}, Acc:{:.6f}'.format(epoch + 1,
                                                         running_loss/len(train_mnist),
                                                         running_acc/len(train_mnist)))

    model.eval()
    eval_loss = 0.0
    eval_acc = 0.0
    for data in test_loader:
        img,label = data

        img = img.view(img.size(0), -1)
        if torch.cuda.is_available():
            img = Variable(img, volatile=True).cuda()
            label = Variable(label, volatile=True).cuda()
        else:
            img = Variable(img, volatile=True)
            label = Variable(label, volatile=True)
        out = model(img)
        _, pred = torch.max(out, 1)
        loss = criterion(out, label)
        eval_loss += loss.item()

        num_correct = (pred == label).sum()
        eval_acc+= num_correct.item()

    print('Test Loss: {:.6f}, Acc: {:.6f}'.format(eval_loss/len(test_mnist), eval_acc/len(test_mnist)))

torch.save(model.state_dict(), 'MNIST_CNN.pkl')

# best result :Test Loss: 0.008280, Acc: 0.924300