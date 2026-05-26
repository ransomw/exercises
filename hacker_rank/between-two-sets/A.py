from functools import reduce

# Recursive function to return gcd of a and b
def gcd(a,b):
    if a == 0:
        return b
    return gcd(b % a, a)
 
# Function to return LCM of two numbers
def lcm(a,b):
    return (a // gcd(a,b))* b

#
# Complete the 'getTotalX' function below.
#
# The function is expected to return an INTEGER.
# The function accepts following parameters:
#  1. INTEGER_ARRAY a
#  2. INTEGER_ARRAY b
#

def getTotalX(a, b):
    lcm_a = reduce(lcm, a)
    min_b = min(b)
    if min_b % lcm_a != 0:
        return 0
    candidates = [lcm_a * (i+1) for i in range(min_b//lcm_a)]
    chosen = [c for c in candidates if all([x % c == 0 for x in b])]
    return len(chosen)


arr_a = [2, 4]
arr_b = [16, 32, 96]

if __name__ == '__main__':
    print(getTotalX(arr_a, arr_b))
