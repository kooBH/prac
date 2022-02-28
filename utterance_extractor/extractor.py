import os, glob
import argparse

import numpy as np
import librosa
import soundfile as sf
import torch

# utils
from tqdm import tqdm
from multiprocessing import Pool, cpu_count

# Due to 'PySoundFile failed. Trying audioread instead' 
import warnings
warnings.filterwarnings('ignore')

# param
parser = argparse.ArgumentParser()
parser.add_argument('--input_root', '-i', type=str, required=True)
parser.add_argument('--output_root', '-o', type=str, required=True)
args = parser.parse_args()

## ROOT
root = args.input_root
output_root = args.output_root


## PATH
target_list = [x for x in glob.glob(os.path.join(root,'*'))]
print(len(target_list))

def process(idx):
    target_path = target_list[idx]
    target_name = target_path.split('/')[-1]
    target_id = target_name.split('.')[0]

    x,_ = librosa.load(target_path,sr=16000,mono=True)

    x = x/np.max(np.abs(x))
    
    # process

    y = librosa.effects.split(x,top_db=30)

    cnt = 0
    # save
    for i in range(len(y)):
        if y[i,1] - y[i,0] < 4000:
            continue
        if np.mean(np.abs(x[y[i,0]:y[i,1]])) < 0.05:
            continue
        cnt += 1
        data = x[y[i,0]:y[i,1]]
        data = data/np.max(np.abs(data))
        sf.write(os.path.join(output_root,str(idx)+'_'+str(cnt)+'.wav'),data,16000)

if __name__=='__main__': 
    cpu_num = cpu_count()

    # categories 
    arr = list(range(len(target_list)))
    with Pool(cpu_num) as p:
        r = list(tqdm(p.imap(process, arr), total=len(arr),ascii=True,desc='processing'))

    output_list = [x for x in glob.glob(os.path.join(output_root,'*'))]
    print(len(output_list))