IF = open("input.txt")
OF = open("output.txt", "w")
lmax = 1111
n = int(IF.readline())
a = list(map(int, IF.readline().split()))
b = list(map(int, IF.readline().split()))
c = [0] * lmax
d = [0] * lmax
for x in a:
    c[x] += 1
for x in b:
    d[x] += 1
for i in range(0, lmax):
    e = min(c[i], d[i])
    c[i] -= e
    d[i] -= e
ans = 0
for i in range(0, lmax):
    ans += c[i] + d[i]
OF.write(str(ans // 2))