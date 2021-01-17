import os
import json
import soundfile as sf
from tqdm import tqdm
import numpy as np

input_root='\\\\163.239.192.82\\nas1_data\\DB\\[DB]AV-TR(서울대병원)'
info = input_root+'/'+'tr_intervals_nocaretaker.json'


def split(root,target,info) : 
    data,sr = sf.read(root+'/raw/'+target+'.wav')
    cnt = 0
    for i in info['nurse'] :
        t = i.split('~')
        start = float(t[0])
        stop  = float(t[1])
        start_idx = int(start*sr)
        stop_idx = int(stop*sr)
        if cnt == 0 :
            tmp = data[start_idx:stop_idx][:];
        else :
            tmp2= data[start_idx:stop_idx][:];
            np.concatenate([tmp,tmp2])
        cnt+=1
    sf.write(root+'/'+'nurse'+'/'+target+'_nurse.wav',tmp,sr)
        
    cnt = 0  
    for i in info['patient'] :
        t = i.split('~')
        start = float(t[0])
        stop  = float(t[1])
        start_idx = int(start*sr)
        stop_idx = int(stop*sr)
        if cnt == 0 :
            tmp = data[start_idx:stop_idx][:];
        else :
            tmp2= data[start_idx:stop_idx][:];
            np.concatenate([tmp,tmp2]) 
        cnt+=1
    sf.write(root+'/'+'patient'+'/'+target+'_patient.wav',tmp,sr)    
    
if __name__=='__main__':
    with open(info, "rb") as file_json:
        j = json.load(file_json)
    root = input_root
    cnt = 0
    for i in tqdm(j) :
        tmp = root +'/raw/'+ i + '.wav' 
        tmp2 = os.path.isfile(tmp)
        if tmp2 :
            split(input_root,i,j[i])
            cnt +=1
    print("files : " + str(cnt)+'/'+ str(len(j)))