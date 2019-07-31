import os,sys
import time
from flask import Flask, redirect, url_for, request,send_file

from multiprocessing import Process, Queue
import asyncio

app = Flask(__name__)

file_name=""

# asyncio.Task to “fire and forget”
# https://stackoverflow.com/questions/37278647/fire-and-forget-python-async-await

def fire_and_forget(f):
    def wrapped(*args, **kwargs):
        asyncio.set_event_loop(asyncio.new_event_loop())
        return asyncio.get_event_loop().run_in_executor(None, f, *args, **kwargs)

    return wrapped

@fire_and_forget
def some_process():
    global ls
    global cur_idx;
    global max_idx
    print('*** 2 : start process')
    ls= []
    cur_idx=-1
    for i in range(max_idx):
        time.sleep(1)
        ls.append(i*10)
        cur_idx += 1
        print('ls : ' + str(ls))

@app.route('/async',methods=['POST'])
def async_call():
    global max_idx
    global cur_idx
    global ls
    global pool
    type_req= request.form['request']
    print('*** NOTE:: type_req = ' + str(type_req))
#    loop = asyncio.get_event_loop()
    if type_req== 'process':
        print('*** 1 : processing ...')
        time.sleep(3)
        max_idx = 10
        # 여기서 두번째 프로세스를 돌리기시작해야함
#        asyncio.ensure_future(some_process())
        some_process()
        return str(max_idx)
    elif type_req== 'get':
        idx = request.form['idx']
        print('*** 3 : get ['+str(idx)+']')
        # 해당 idx 가 준비될 때 까지 기다린 다음 return
        while(cur_idx<int(idx)):
            pass
        return str(ls[int(idx)])
    return ""

@app.route('/')
def index():
    print('touch')
    return 'hello from flask'

if __name__ == '__main__':
   global pool

   #app.run(debug = True)

   # 모든 ip (외부 ip) 에서 접근 가능하도록 설정.
   #app.run(host='0.0.0.0',port = 1170)
   app.run(port = 8080)
