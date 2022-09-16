from multiprocessing import Process
import multiprocessing
import os
import time

def info(title):
    print(title)
    print('module name:', __name__)
    print('parent process:', os.getppid())
    print('process id:', os.getpid())

def f(name,q):
    print(q.get())
    q.put("adios")
    q.put("mundo")
    info('function f')
    print('hello', name)

def apellido(name,q):
    time.sleep(5)
    info('function apellido')
    print('hello', name)
    print(q.get())

if __name__ == '__main__':
    q = multiprocessing.Queue()
    q.put("hola")
    procesos =[]
    p = Process(target=apellido, args=('jocxan',q,))
    procesos.append(p)

    p = Process(target=f, args=('sandi',q,))
    procesos.append(p)

    for i in procesos:
        i.start()

    for i in procesos:
        i.join()