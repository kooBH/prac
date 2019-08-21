import multiprocessing as mp
from time import sleep

class A(object):
    def __init__(self, *args, **kwargs):
        # do other stuff
        self.ls = [None]*10
        pass

    def do_something(self):
        sleep(1)
        for i in range(10):
            self.ls[i] = i

    def run(self):
        processes = []

        p = mp.Process(target=self.do_something)
        processes.append(p)
        print('process append')

        [x.start() for x in processes]

        for i in self.ls:
            print(i)
            sleep(3)


if __name__ == '__main__':
    a = A()
    a.run()
