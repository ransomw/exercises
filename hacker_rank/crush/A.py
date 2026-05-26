def arrayManipulation(n, queries):
    parr = [0]*(n+1)
    for query in queries:
        [a, b, k] = query
        parr[a-1] += k
        parr[b] += -k
    arr = []
    psum = 0
    for i in range(n):
        psum += parr[i]
        arr.append(psum)
    return max(arr)


n = 5
qs = [[1, 2, 100], [2, 5, 100], [3, 4, 100]]

if __name__ == '__main__':
    res = arrayManipulation(n, qs)
    print(res)
