from typing import *
import math

import torch
import torch.nn as nn
from torch.nn import Parameter
from torch.nn import init
from torch import Tensor
import numpy as np

class NaiveRNN(nn.Module):
    """Simple RNN"""
    def __init__(self, input_size: int, hidden_size: int):
        super().__init__()
        self.input_size, self.hidden_size = input_size, hidden_size
        self.w_ih = Parameter(Tensor(hidden_size, input_size))
        self.b_ih = Parameter(Tensor(hidden_size, 1))
        self.w_hh = Parameter(Tensor(hidden_size, hidden_size))
        self.b_hh = Parameter(Tensor(hidden_size, 1))

        self.reset_weights()

    def reset_weights(self):
        stdv = 1.0 / math.sqrt(self.hidden_size)
        for weight in self.parameters():
            init.uniform_(weight, -stdv, stdv)

    def forward(self, inputs: Tensor, state=None) -> torch.Tensor:
        """Assumes x is of shape (batch, sequence, feature)
        Args:
            Inputs: [batch_size, sequence_len, dimention]
            state:  [batch_size, dimention]
        """
        bs, sequence_len, _ = x.size()
        hidden_seq = []

        if state is None:
            h_t = torch.zeros(1, self.hidden_size).t().to(x.device)
        else:
            h_t = state.t()

        for t in range(sequence_len):
            x_t = inputs[:, t, :].t()
            h_t = torch.tanh(self.weight_ih @ x_t + self.b_ih +
                             self.weight_hh @ h_t + self.b_hh)
            hidden_seq.append(h_t.t())
        hidden_seq = torch.cat(hidden_seq, dim=0)
        return hidden_seq, h_t
