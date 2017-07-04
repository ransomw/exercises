def iter(frac):
    a = [frac[1], frac[0]+frac[1]]
    return [a[0]+a[1], a[1]]


FRAC = [1, 1]
NUM = 0
for _ in range(1000):
    FRAC = iter(FRAC)
    if len(str(FRAC[0])) > len(str(FRAC[1])):
        NUM += 1

print NUM
