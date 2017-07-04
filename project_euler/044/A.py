from pdb import set_trace as st

from math import sqrt

def isP(x):
    return sqrt(24*x+1) % 6 == 5

def P(x):
    return (x*(3*x-1))/2

st()

def test1():
    not_found = True
    n = 1
    while not_found:
        n += 1
        a = P(n)
        for m in range(1, n):
            b = P(m)
            print a, b
            if isP(a+b) and isP(a-b):
                print 'FOUND'
                not_found = False
                break


    print a
    print b
    print a - b

def test2():
    not_found = True
    n = 1
    while not_found:
        n += 1
        a = P(n)
        for m in range(1, n):
            b = P(m)
            print a, b
            if isP(a+b) and isP(a+2*b):
                print 'FOUND'
                not_found = False
                break


    print a
    print b
    print a + b
    print a + 2*b
