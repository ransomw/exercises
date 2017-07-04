

def max_wait(arr, ser):
    if len(arr) == 1:
        return 0
    mw = 0
    orderReady = arr[0] + ser[0]
    for i in range(1, len(arr)):
        mw = max(mw, orderReady - arr[i])
        orderReady = max(arr[i], orderReady) + ser[i]
    return mw

class BigBurger(object):
    def maxWait(self, arrival, service):
        return max_wait(arrival, service)

# bb = BigBurger()
# print bb.maxWait([2, 10, 12], [15, 1, 15])
