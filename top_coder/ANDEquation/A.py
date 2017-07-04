INPUT_01 = (191411,256951,191411,191411,191411,256951,195507,191411,192435,191411, 191411,195511,191419,191411,256947,191415,191475,195579,191415,191411, 191483,191411,191419,191475,256947,191411,191411,191411,191419,256947, 191411,191411,191411)



def ANDall (nums):
    andAll = nums[0]
    for num in nums[1:]:
        andAll &= num
    return andAll

class ANDEquation (object):
    def restoreY (self, A):
        Y = ANDall(A)
        try:
            idxY = A.index(Y)
        except ValueError:
            return -1
        if Y == ANDall(A[:idxY]+A[idxY+1:]):
            return Y
        else:
            return -1

andEquation = ANDEquation()

print andEquation.restoreY(INPUT_01)
