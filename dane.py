import random

def losowo(ile):
    return [random.randrange(i+1)+1 for i in range(ile)]

def malejace(ile):
    return sorted([i+1 for i in range(ile)],reverse=True)

def rosnace(ile):
    return [i+1 for i in range(ile)]

def aksztaltne(ile):
    return [i+1 if i < ile/2 else ile-i for i in range(ile)]

def staly(ile):
    i = random.randrange(ile+1%20+1)
    return [i for j in range(ile)]

def los_bez_pow(ile):
    a = [i+1 for i in range(ile)]
    for i in range(int(ile)):
        r1 = random.randrange(ile)
        r2 = random.randrange(ile)
        a[r1],a[r2] = a[r2],a[r1]
    return a

def Main():
    ilosc = [1000,2000,5000,10000,20000,30000,40000,60000,80000,100000]
    print(los_bez_pow(ilosc[0]))

if __name__=="__main__":
    Main()
