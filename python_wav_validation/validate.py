import os,glob
import librosa
import numpy as np

# utils
from tqdm import tqdm
from multiprocessing import Pool, cpu_count

target_root = '/home/data/kbh/AVTR/20210608_simu_bluetooth/'
target_list = [x for x in glob.glob(os.path.join(target_root,'*','*.wav'))]

def validate(idx):
    target_path = target_list[idx]
    raw,_ =  librosa.load(target_path,sr=16000)

cpu_num = cpu_count()

arr = list(range(len(target_list)))
with Pool(cpu_num) as p:
    r = list(tqdm(p.imap(validate, arr), total=len(arr),ascii=True,desc='validate'))