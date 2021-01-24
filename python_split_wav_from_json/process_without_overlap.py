import os
import json
import soundfile as sf
from tqdm import tqdm

#input_root='\\\\163.239.192.82\\nas1_data\\DB\\[DB]AV-TR(서울대병원)'
input_root='/home/nas/DB/[DB]AV-TR(서울대병원)'
info = input_root+'/'+'tr_intervals_nocaretaker.json'

def elim_intersection(target,compare): 
    # no intersection
    if target[1]<= compare[0] or target[0] >= compare[1] :
        return [target]
    else : 
        # case 1
        if target[0] <= compare[1] and target[1] >= compare[1] : 
            target[0] = compare[1]
            return [target]
        # case 2
        elif target[0] <= compare[0] and target[1] >= compare[1] : 
            return [target[0],compare[0]],[target[1],compare[1]]
        # case 3
        elif target[0] <= compare[0] and target[1] <= compare[1] :
            target[1]=compare[0]
            return [target]
        # case 4
        elif target[0] >=compare[0] and target[1] <= compare[1] : 
            return []
        # ???
        else :
            raise Exception('unknown itersection type....')

def split(root,target,info) : 
    data,sr = sf.read(root+'/raw/'+target+'.wav')
    cnt = 0

    # How to eliminate overlapped itervals.   
    # 1. extract intervals of each speaker.
    # 2. calculate overlapped intervals.
    # 3. delete them.
    # 4. divide wav files by remaning intervals.
    
    interval_nurse = []
    interval_patient = []

    # 1. extract intervals of each speaker
    cnt = 0
    for i in info['nurse'] :
        t = i.split('~')
        start = float(t[0])
        stop  = float(t[1])
        interval_nurse.append([start,stop])
        cnt+=1

    cnt = 0  
    for i in info['patient'] :
        t = i.split('~')
        start = float(t[0])
        stop  = float(t[1])
        interval_patient.append([start,stop])
        cnt+=1

    # 2. caluate overlapped intervals     
    # 3. delete them.
    interval_nurse_without_overlapped = []
    interval_patient_without_overlapped = []

    for i in interval_nurse :
        target = []
        for j in interval_patient :
            tmp = elim_intersection(i,j)
            target.append(tmp)
            # elim duplicates
            target = list(dict.fromkeys(target))
        interval_nurse_without_overlapped.append(target)
    for i in interval_patient :
        target = []
        for j in interval_nurse :
            tmp = elim_intersection(i,j)
            target.append(tmp)
            # elim duplicates
            target = list(dict.fromkeys(target))
        interval_patient_without_overlapped.append(target)
    print(interval_nurse_without_overlapped)
    print(interval_patient_without_overlapped)

    # 4. divide wav files by remaning intervals.
    """
    for i in interval_nurse_without_overlapped :
        start_idx = int(start*sr)
        stop_idx = int(stop*sr)
        tmp = data[start_idx:stop_idx][:]
    
    for i in interval_patient_without_overlapped :
        start_idx = int(start*sr)
        stop_idx = int(stop*sr)
        tmp = data[start_idx:stop_idx][:]

    sf.write(root+'/'+'nurse'+'/'+target+'_nurse_'+str(cnt)+'.wav',tmp,sr)
    sf.write(root+'/'+'patient'+'/'+target+'_patient_'+str(cnt)+'.wav',tmp,sr)
    """
        
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