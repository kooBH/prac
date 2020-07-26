import multiprocessing as mp
from tqdm import tqdm 


def func(x,y):
    print(str(x) +' | ' +str(y))

def func_star(args):
    print(args)
    return func(*args)


if __name__ == "__main__":
    num_core = mp.cpu_count()
    #args = range(4)
    args = [1,2]
    args2 = [3,4]
    pool = mp.Pool(processes=num_core)
    pool.map(func_star,((args),(args2)))

    pool.close()
    pool.join()


