import sys

sys.stdin = open("input.txt", 'r')
sys.stdout = open("output.txt", 'w')
input()
s = input()
p = 0
q = ''
for i in range(0, len(s), 2):
    f = s[i] == s[i + 1]
    p += f
    q += (s[i:i + 2], 'ab')[f]
print(p)
print(q)