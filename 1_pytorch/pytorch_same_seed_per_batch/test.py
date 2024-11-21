import torch
import torch.nn as nn
import numpy as np


def worker_func(idx):
    print("wroker_func")
    np.random.seed(0)

class RandomDataset(torch.utils.data.Dataset):
    def __init__(self):
        super().__init__()
        self.val = np.random.randint(5)

    def __getitem__(self, index):
        #self.val+=1
        print(self.val)
        return np.random.randint(0, 1000, 2)

    def __len__(self):
        return 9

    def reset(self):
        np.random.seed(0)


n_worker = 4
n_batch = 6
epoch = 10

dataset = RandomDataset()
dataloader = torch.utils.data.DataLoader(dataset, num_workers= n_worker, batch_size = n_batch,worker_init_fn = worker_func,shuffle=True)
cnt = 0
for val in dataloader : 
    print("cnt : {} | val : {}".format(cnt,val))
    dataset.reset()
    cnt+=1

