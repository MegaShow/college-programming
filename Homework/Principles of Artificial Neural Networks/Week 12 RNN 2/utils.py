"""Utils"""

import time
import math
import re
import unicodedata
from typing import *

import torch
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

SOS_token = 0
EOS_token = 1
MAX_LENGTH = 10
eng_prefixes = (
    "i am ", "i m ",
    "he is", "he s ",
    "she is", "she s ",
    "you are", "you re ",
    "we are", "we re ",
    "they are", "they re "
)

class Lang:
    """Helper class to keep track of all word as the inputs and targets
    of the networks. Lang encode per word with a unique index.
    """
    def __init__(self, name):
        self.name = name
        self.word2index = dict()
        self.index2word = {0: "SOS", 1: "EOS"}
        self.word2count = dict()
        self.n_words = 2 # Count SOS and EOS

    def add_sentence(self, sentence):
        for word in sentence.split(" "):
            self.add_word(word)

    def add_word(self, word):
        if word not in self.word2index:
            self.word2index[word] = self.n_words
            self.word2count[word] = 1
            self.index2word[self.n_words] = word
            self.n_words += 1
        else:
            self.word2count[word] += 1

def unicode_to_ascii(s):
    """Convert files in Unicode to ASCII
    """
    # Mn means Nonspacing_mark
    return "".join(
        c for c in unicodedata.normalize("NFD", s)
        if unicodedata.category(c) != "Mn")

def normalize_string(s):
    """convert string to ascii and remove illegal input and punctuation
    """
    s = unicode_to_ascii(s.lower().strip())
    s = re.sub(r"([.!?])", r" \1", s)
    s = re.sub(r"[^a-zA-Z.!?]+", r" ", s)
    return s

def read_langs(lang1, lang2, reverse=False):
    """Split the files into lines and then split lines into pairs"""
    print("Reading lines...")

    lines = open("data/%s-%s.txt" % (lang1, lang2), encoding="utf-8").\
            read().strip().split("\n")
    pairs = [[normalize_string(s) for s in l.split("\t")] for l in lines]

    if reverse:
        pairs = [list(reversed(p)) for p in pairs]
        input_lang = Lang(lang2)
        output_lang = Lang(lang1)
    else:
        input_lang = Lang(lang1)
        output_lang = Lang(lang2)

    return input_lang, output_lang, pairs

def filter_pair(p):
    """Filter specific pair for simplicity
    """
    return len(p[0].split(" ")) < MAX_LENGTH and \
           len(p[1].split(" ")) < MAX_LENGTH and \
           p[1].startswith(eng_prefixes)

def filter_pairs(pairs):
    """Trim the data set to only relatively short and simple sentences
    """
    return [pair for pair in pairs if filter_pair(pair)]

def prepare_data(lang1: str, lang2: str, reverse: bool):
    """Prepare data for training
    Args:
        lang1: source language
        lang2: target langage
        reverse: whether to reverse source sentence and target sentence
    """
    input_lang, output_lang, pairs = read_langs(lang1, lang2, reverse)
    print("Read %s sentence pairs" % len(pairs))

    if reverse:
        print("Reverse source sentence")
    else:
        print("Not to reverse source sentence")

    pairs = filter_pairs(pairs)
    print("Trimmed to %s sentence pairs" % len(pairs))
    print("Counting words ...")

    for pair in pairs:
        input_lang.add_sentence(pair[0])
        output_lang.add_sentence(pair[1])
    print("Counting words:")
    print(input_lang.name, input_lang.n_words)
    print(output_lang.name, output_lang.n_words)
    return input_lang, output_lang, pairs

def indexes_from_sentence(lang, sentence):
    """Convert index to sentence"""
    return [lang.word2index[word] for word in sentence.split(" ")]

def tensor_from_sentence(lang, sentence):
    """Convert sentence to tensor"""
    indexes = indexes_from_sentence(lang, sentence)
    indexes.append(EOS_token)
    return torch.tensor(indexes, dtype=torch.long).view(-1, 1)

def tensor_from_pair(pair: Tuple, input_lang: str, output_lang: str):
    """Convert pair to tensor
    Args:
        pair:
        input_lang:
        output_lang:
    Returns:
        pairs:
    """
    input_tensor = tensor_from_sentence(input_lang, pair[0])
    target_tensor = tensor_from_sentence(output_lang, pair[1])
    return (input_tensor, target_tensor)

def as_minutes(s):
    m = math.floor(s / 60)
    s -= m * 60
    return "%dm %ds" % (m, s)

def time_since(since, percent):
    """Time since"""
    now = time.time()
    s = now - since
    es = s / (percent)
    rs = es - s
    return "%s (- %s)" % (as_minutes(s), as_minutes(rs))
