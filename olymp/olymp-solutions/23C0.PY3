import sys

sys.stdin = open("input.txt", 'r')
sys.stdout = open("output.txt", 'w')
n = int(input())
s = input()
t = input() + "#"
ps = 0
pt = 0
err = 0
pos = 0
while ps < n:
    if s[ps] == t[pt]:
        ps += 1
        pt += 1
    else:
        ps += 1
        err += 1
        pos = ps
print(pos * (err == 1))