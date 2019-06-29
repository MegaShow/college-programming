import torch.nn as nn
import torch
from torch.autograd import Variable

class MNIST_DNN(nn.Module):
    def __init__(self):
        super(MNIST_DNN, self).__init__()
        self.dense1 = nn.Linear(784, 512)
        self.dropout1 = nn.Dropout(p=0.7)

        self.dense2 = nn.Linear(512, 512)
        self.dropout2 = nn.Dropout(p=0.7)

        self.dense3 = nn.Linear(512, 512)
        self.dropout3 = nn.Dropout(p=0.7)

        self.dense4 = nn.Linear(512, 512)
        self.dropout4 = nn.Dropout(p=0.7)

        self.dense5 = nn.Linear(512, 10)

    def forward(self, x):
        x = self.dense1(x)
        x = self.dropout1(x)

        x = self.dense2(x)
        x = self.dropout2(x)

        x = self.dense3(x)
        x = self.dropout3(x)

        x = self.dense4(x)
        x = self.dropout4(x)

        x = self.dense5(x)
        return x


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
                                    nn.MaxPool2d(2, 2, padding=1),nn.Dropout(p=0.7))

        # layer4
        self.layer4= nn.Sequential(nn.Linear(128 * 5 * 5, 625), nn.ReLU(True),
                                   nn.Dropout(0.5))

        # layer5
        self.layer5 = nn.Sequential(nn.Linear(625, 10))

    def forward(self, x):
        x = self.layer1(x)
        x = self.layer2(x)
        x = self.layer3(x)
        x = x.view(-1, 128*5*5)
        x = self.layer4(x)
        x = self.layer5(x)
        return x

if __name__ == '__main__':
    tensor = torch.randn(32,1,28,28)
    if torch.cuda.is_available():
        tensor = Variable(tensor).cuda()
    else:
        tensor = Variable(tensor)

    model = MNIST_CNN()
    if torch.cuda.is_available():
        model = model.cuda()

    out = model(tensor)
    print(model(tensor).size())