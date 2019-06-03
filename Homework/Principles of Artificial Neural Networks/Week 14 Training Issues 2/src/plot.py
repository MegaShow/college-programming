import matplotlib.pyplot as plt

def plot_grad(grad_1, grad_2, title, label1='Graddient for Hidden1 Layer', label2='Gradient for Hidden2 layer'):
    fig, ax = plt.subplots() # add a set of subplots to this figure
    ax.plot(grad_1, label=label1) # plot grad 1
    ax.plot(grad_2, label=label2) # plot grad 2
    # place a legend on axes
    legend = ax.legend(loc='best', shadow=True, fontsize='x-large')
    plt.title(title)

def show_weight_bias(model):
    """Show some weights and bias distribution every layers in model.
       !!YOU CAN READ THIS CODE LATER!!
    """
    # Create a figure and a set of subplots
    fig, axs = plt.subplots(2,2, sharey=False, tight_layout=True)

    # weight and bias for every hidden layer
    h1_w = model.hidden1.weight.detach().numpy().flatten()
    h1_b = model.hidden1.bias.detach().numpy().flatten()
    h2_w = model.hidden2.weight.detach().numpy().flatten()
    h2_b = model.hidden2.bias.detach().numpy().flatten()

    axs[0,0].hist(h1_w)
    axs[0,1].hist(h2_w)
    axs[1,0].hist(h1_b)
    axs[1,1].hist(h2_b)

    # set title for every sub plots
    axs[0,0].set_title('hidden1_weight')
    axs[0,1].set_title('hidden2_weight')
    axs[1,0].set_title('hidden1_bias')
    axs[1,1].set_title('hidden2_bias')
