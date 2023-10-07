import sys

sys.stdin = open("input.txt", 'r')
sys.stdout = open("output.txt", 'w')
n = int(input())
a = [int(x) for x in input().split()]
a = [(a[i], i) for i in range(len(a))]
a.sort(reverse=True)
x = 0
shots = 0
ans = []
for v, i in a:
    ans.append(i + 1)
    shots += v * x + 1
    x += 1
print(shots)
print(*ans)