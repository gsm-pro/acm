import sys

sys.stdin = open("input.txt", 'r')
sys.stdout = open("output.txt", 'w')
W = list(map(int, input().split()))
B1 = list(map(int, input().split()))
B2 = list(map(int, input().split()))

def intersection(a, b):
    x = [max(a[0], b[0]), max(a[1], b[1]), min(a[2], b[2]), min(a[3], b[3])]
    return x

def area(x):
    return max((x[2] - x[0]), 0) * max((x[3] - x[1]), 0)

if area(intersection(W, B1)) + area(intersection(W, B2)) - area(intersection(W, intersection(B2, B1))) == area(W):
    print('NO')
else:
    print("YES")