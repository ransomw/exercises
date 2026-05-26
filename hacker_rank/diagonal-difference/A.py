from functools import reduce
from operator import add

def diagonalDifference(arr):
    n = len(arr)
    rdiag = [arr[i][i] for i in range(n)]
    ldiag = [arr[i][n - 1 - i] for i in range(n)]
    rsum = reduce(add, rdiag)
    lsum = reduce(add, ldiag)
    return abs(rsum - lsum)


arr1 = [[1, 2, 3], [4, 5, 6], [9, 8, 9]]

if __name__ == '__main__':
    print(diagonalDifference(arr1))
