from pdb import set_trace as st


def parse_pair(pstr):
    sstr = pstr.split(',')
    return [int(sstr[0]), int(sstr[1])]

def sp(pos, pieces):
    if pos[1] == 7:
        return 0
    if (pos[1] > 7 or
        pos[0] < 0 or
        pos[0] > 7):
        return -1
    nextr = [pos[0]+1, pos[1]+1]
    nextrr = [pos[0]+2, pos[1]+2]
    nextl = [pos[0]-1, pos[1]+1]
    nextll = [pos[0]-2, pos[1]+2]
    if nextr not in pieces:
        minr = sp(nextr, pieces)
    elif nextrr in pieces or nextrr[0] > 7 or nextrr[1] > 7:
        minr = -1
    else:
        while ([nextrr[0]+1, nextrr[1]+1] in pieces and
               nextrr[0] + 2 <= 7 and nextrr[1] + 2 <= 7 and
               [nextrr[0]+2, nextrr[1]+2] not in pieces):
            nextrr = [nextrr[0] + 2, nextrr[1] + 2]
        minr = sp(nextrr, pieces)
    if nextl not in pieces:
        minl = sp(nextl, pieces)
    elif nextll in pieces or nextll[0] < 0 or nextll[1] > 7:
        minl = -1
    else:
        while ([nextll[0]-1, nextll[1]+1] in pieces and
               nextll[0] - 2 >= 0 and nextll[1] + 2 <= 7 and
               [nextll[0]-2,nextll[1]+2] not in pieces):
            nextll = [nextll[0]-2, nextll[1]+2]
        minl = sp(nextll, pieces)
    if minr == -1 and minl == -1:
        return -1
    elif minr == -1:
        return minl + 1
    elif minl == -1:
        return minr + 1
    else:
        return min(minl, minr) + 1

class Checkers(object):
    def compute(self, pos, pieces):
        return sp(parse_pair(pos),
                  [parse_pair(p) for p in  pieces])


c = Checkers()
print c.compute("1,0", ("2,1", "0,3", "4,3", "5,6", "4,2"))
print c.compute("4,4", ())
print c.compute("4,4", ("6,6", "5,5", "3,5", "2,6"))
print c.compute("4,1", ("2,4", "3,4", "4,4", "5,4", "2,6", "3,6", "4,6", "5,6"))
