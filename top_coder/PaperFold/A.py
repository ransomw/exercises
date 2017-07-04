
from math import log, floor, ceil

def dim_folds(p, b):
    return max(ceil(log(float(p)/b, 2)), 0)

def num_folds_no_rotate(paper, box):
    folds1 = dim_folds(paper[0], box[0])
    folds2 = dim_folds(paper[1], box[1])
    return folds1 + folds2

def num_folds(paper, box):
    totFolds = min(num_folds_no_rotate(paper, box),
                   num_folds_no_rotate([paper[1], paper[0]], box))
    if totFolds > 8:
        return -1
    return totFolds

class PaperFold(object):
    def numFolds(self, paper, box):
        return num_folds(paper, box)


pf = PaperFold()
print pf.numFolds((8, 11), (6, 10))
print pf.numFolds((11, 17), (6, 4))
print pf.numFolds((11, 17), (5, 4))
print pf.numFolds((1000, 1000), (62, 63))
print pf.numFolds((100, 30), (60, 110))
print pf.numFolds((1895, 6416), (401, 1000))
