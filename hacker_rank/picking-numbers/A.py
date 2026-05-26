from itertools import chain, combinations


def powerset(iterable):
    "powerset([1,2,3]) --> () (1,) (2,) (3,) (1,2) (1,3) (2,3) (1,2,3)"
    s = list(iterable)
    return chain.from_iterable(combinations(s, r) for r in range(len(s)+1))

def absDiffLeqOne(s):
    if len(s) < 2:
        return True
    return max([abs(p[0]-p[1]) for p in combinations(s, 2)]) <= 1

def pickingNumbersTooSlow(a):
    return max([len(s) for s in powerset(a) if absDiffLeqOne(s)])

def pickingNumbers(a):
    a.sort()
    llen = 0
    for i in range(len(a)):
        clen = 1
        while (i + clen - 1 < len(a) and
            abs(a[i]-a[i+clen-1]) <= 1):
            clen += 1
        if clen > llen:
            llen = clen
    return llen
    

arr = [4,6,5,3,3,1]

if __name__ == '__main__':
    res = pickingNumbers(arr)
    print(res)
