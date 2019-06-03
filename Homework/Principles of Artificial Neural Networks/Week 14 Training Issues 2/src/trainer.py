import numpy as np
import torch
import matplotlib.pyplot as plt


def fit(train_loader, val_loader, model, loss_fn, optimizer, n_epochs, get_grad=False):
    """train and val model here, we use train_epoch to train model and
    val_epoch to val model prediction performance
    Args:
        train_loader: train data
        val_loader: validation data
        model: prediction model
        loss_fn: loss function to judge the distance between target and outputs
        optimizer: optimize the loss function
        n_epochs: training epochs
        get_grad: Whether to get grad of hidden2 layer and hidden3 layer
    Returns:
        train_accs: accuracy of train n_epochs, a list
        train_losses: loss of n_epochs, a list
    """

    grad_1 = [] # save grad for hidden 1 every epoch
    grad_2 = [] # save grad for hidden 2 every epoch

    train_accs = [] # save train accuracy every epoch
    train_losses = [] # save train loss every epoch

    for epoch in range(n_epochs): # train for n_epochs
        # train model on training datasets, optimize loss function and update model parameters
        train_loss, average_grad1, average_grad2 = train(train_loader, model, loss_fn, optimizer, get_grad)

        # evaluate model performance on train dataset
        _, train_accuracy = evaluate(train_loader, model, loss_fn)
        message = 'Epoch: {}/{}. Train set: Average loss: {:.4f}, Accuracy: {:.4f}'.format(epoch+1, \
                                                                n_epochs, train_loss, train_accuracy)
        print(message)

        # save loss, accuracy, grad
        train_accs.append(train_accuracy)
        train_losses.append(train_loss)
        grad_1.append(average_grad1)
        grad_2.append(average_grad2)

        # evaluate model performance on val dataset
        val_loss, val_accuracy = evaluate(val_loader, model, loss_fn)
        message = 'Epoch: {}/{}. Validation set: Average loss: {:.4f}, Accuracy: {:.4f}'.format(epoch+1, \
                                                                n_epochs, val_loss, val_accuracy)
        print(message)


    return train_accs, train_losses, grad_1, grad_2


def train(train_loader, model, loss_fn, optimizer, get_grad=False):
    """train model using loss_fn and optimizer. When thid function is called, model trains for one epoch.
    Args:
        train_loader: train data
        model: prediction model
        loss_fn: loss function to judge the distance between target and outputs
        optimizer: optimize the loss function
        get_grad: True, False
    Returns:
        total_loss: loss
        average_grad1: average grad for hidden 1 in this epoch
        average_grad2: average grad for hidden 2 in this epoch
    """

    # set the module in training model, affecting module e.g., Dropout, BatchNorm, etc.
    model.train()

    total_loss = 0
    grad_1 = 0.0 # store sum(grad) for hidden 3 layer
    grad_2 = 0.0 # store sum(grad) for hidden 3 layer

    for batch_idx, (data, target) in enumerate(train_loader):
        optimizer.zero_grad() # clear gradients of all optimized torch.Tensors'
        outputs = model(data) # make predictions
        loss = loss_fn(outputs, target) # compute loss
        total_loss += loss.item() # accumulate every batch loss in a epoch
        loss.backward() # compute gradient of loss over parameters

        if get_grad == True:
            g1, g2 = model.get_grad() # get grad for hiddern 2 and 3 layer in this batch
            grad_1 += g1 # accumulate grad for hidden 2
            grad_2 += g2 # accumulate grad for hidden 2

        optimizer.step() # update parameters with gradient descent

    average_loss = total_loss / batch_idx # average loss in this epoch
    average_grad1 = grad_1 / batch_idx # average grad for hidden 2 in this epoch
    average_grad2 = grad_2 / batch_idx # average grad for hidden 3 in this epoch

    return average_loss, average_grad1, average_grad2


def evaluate(loader, model, loss_fn):
    """test model's prediction performance on loader.
    When thid function is called, model is evaluated.
    Args:
        loader: data for evaluation
        model: prediction model
        loss_fn: loss function to judge the distance between target and outputs
    Returns:
        total_loss
        accuracy
    """

    # context-manager that disabled gradient computation
    with torch.no_grad():

        # set the module in evaluation mode
        model.eval()

        correct = 0.0 # account correct amount of data
        total_loss = 0  # account loss

        for batch_idx, (data, target) in enumerate(loader):
            outputs = model(data) # make predictions
            # return the maximum value of each row of the input tensor in the
            # given dimension dim, the second return vale is the index location
            # of each maxium value found(argmax)
            _, predicted = torch.max(outputs, 1)
            # Detach: Returns a new Tensor, detached from the current graph.
            #The result will never require gradient.
            correct += (predicted == target).sum().detach().numpy()
            loss = loss_fn(outputs, target)  # compute loss
            total_loss += loss.item() # accumulate every batch loss in a epoch

        accuracy = correct*100.0 / len(loader.dataset) # accuracy in a epoch
        average_loss = total_loss / len(loader)

    return average_loss, accuracy
