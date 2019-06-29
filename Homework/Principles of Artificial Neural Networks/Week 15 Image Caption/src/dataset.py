"""Dataset"""

import json
import os

import h5py
import torch
import torchvision.transforms as transforms

class Dataset:
    def __init__(self, batch_size=32):
        # Custom dataloaders
        data_folder = "./data"
        data_name = "flickr8k_5_cap_per_img_5_min_word_freq"
        # Read word map
        word_map_file = os.path.join(data_folder, 'WORDMAP_' + data_name +
                                     '.json')
        with open(word_map_file, 'r') as j:
            self.word_map = json.load(j)

        self.rev_word_map = {v: k for k, v in self.word_map.items()}  # ix2word

        train_dataset, val_dataset = self.load_dataset(data_folder, data_name)
        self.train_loader, self.val_loader = self.load_dataloader(train_dataset,
                                                                  val_dataset,
                                                                  batch_size)


    def load_dataset(self, data_folder, data_name):
        """Load dataset
        """
        normalize = transforms.Normalize(mean=[0.485, 0.456, 0.406],
                                         std=[0.229, 0.224, 0.225])
        train_dataset = CaptionDataset(data_folder, data_name, 'TRAIN',
                                       transform=transforms.Compose([normalize]))

        val_dataset = CaptionDataset(data_folder, data_name, 'VAL',
                                     transform=transforms.Compose([normalize]))
        return train_dataset, val_dataset

    def load_dataloader(self, train_dataset, val_dataset, batch_size):
        """Init dataloader"""
        train_loader = torch.utils.data.DataLoader(
            train_dataset, batch_size=batch_size, shuffle=True,
            num_workers=1, pin_memory=True)
        val_loader = torch.utils.data.DataLoader(
            val_dataset, batch_size=batch_size, shuffle=True,
            num_workers=1, pin_memory=True)
        return train_loader, val_loader

    def get_dataloader(self):
        """Get dataloader
        """
        return self.train_loader, self.val_loader

    def get_word_map(self):
        """Get word map"""
        return self.word_map

    def get_rev_word_map(self):
        return self.rev_word_map


class CaptionDataset(torch.utils.data.Dataset):
    """
    A PyTorch Dataset class to be used in a PyTorch DataLoader to create batches.
    """

    def __init__(self, data_folder, data_name, split, transform=None):
        """
        :param data_folder: folder where data files are stored
        :param data_name: base name of processed datasets
        :param split: split, one of 'TRAIN', 'VAL', or 'TEST'
        :param transform: image transform pipeline
        """
        self.split = split
        assert self.split in {'TRAIN', 'VAL', 'TEST'}

        # Open hdf5 file where images are stored
        self.h = h5py.File(os.path.join(data_folder, self.split + '_IMAGES_' + data_name + '.hdf5'), 'r')
        self.imgs = self.h['images']

        # Captions per image
        self.cpi = self.h.attrs['captions_per_image']

        # Load encoded captions (completely into memory)
        with open(os.path.join(data_folder, self.split + '_CAPTIONS_' + data_name + '.json'), 'r') as j:
            self.captions = json.load(j)

        # Load caption lengths (completely into memory)
        with open(os.path.join(data_folder, self.split + '_CAPLENS_' + data_name + '.json'), 'r') as j:
            self.caplens = json.load(j)

        # PyTorch transformation pipeline for the image (normalizing, etc.)
        self.transform = transform

        # Total number of datapoints
        self.dataset_size = len(self.captions)

    def __getitem__(self, i):
        # Remember, the Nth caption corresponds to the (N // captions_per_image)th image
        img = torch.FloatTensor(self.imgs[i // self.cpi] / 255.)
        if self.transform is not None:
            img = self.transform(img)

        caption = torch.LongTensor(self.captions[i])

        caplen = torch.LongTensor([self.caplens[i]])

        if self.split is 'TRAIN':
            return img, caption, caplen
        else:
            # For validation of testing, also return all 'captions_per_image' captions to find BLEU-4 score
            all_captions = torch.LongTensor(
                self.captions[((i // self.cpi) * self.cpi):(((i // self.cpi) * self.cpi) + self.cpi)])
            return img, caption, caplen, all_captions

    def __len__(self):
        return self.dataset_size
