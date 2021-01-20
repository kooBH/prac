import os
import json
import soundfile as sf
from tqdm import tqdm

input_root='\\\\163.239.192.82\\nas1_data\\DB\\[DB]AV-TR(서울대병원)'
info = input_root+'/'+'tr_intervals_nocaretaker.json'

def split(root,target,info) : 
    data,sr = sf.read(root+'/raw/'+target+'.wav')
    cnt = 0
    for i in info['nurse'] :
        t = i.split('~')
        start = float(t[0])
        stop  = float(t[1])
        #print(str(start)+' ~ ' + str(stop))
        start_idx = int(start*sr)
        stop_idx = int(stop*sr)
        #print(str(start_idx)+' ~ ' + str(stop_idx))
        tmp = data[start_idx:stop_idx][:];
        sf.write(root+'/'+'nurse'+'/'+target+'_nurse_'+str(cnt)+'.wav',tmp,sr)
        cnt+=1
    cnt = 0  
    for i in info['patient'] :
        t = i.split('~')
        start = float(t[0])
        stop  = float(t[1])
        #print(str(start)+' ~ ' + str(stop))
        start_idx = int(start*sr)
        stop_idx = int(stop*sr)
        tmp = data[start_idx:stop_idx][:];
        #print(str(start_idx)+' ~ ' + str(stop_idx))
        sf.write(root+'/'+'patient'+'/'+target+'_patient_'+str(cnt)+'.wav',tmp,sr)
        cnt+=1
        
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