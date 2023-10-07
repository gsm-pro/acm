from itertools import repeat

IF = open("input.txt")
OF = open("output.txt", "w")
a = IF.readline().strip()
b, c = map(int, IF.readline().split())
z = len(a)
n = list(map(int, a, repeat(10, z)))
rems = []
rem = 0
d = 1
for i in range(z - 1, -1, -1):
    rem = (rem + n[i] * d) % c
    d = d * 10 % c
    rems.append(rem)
rems.reverse()
rem = 0
for i, x in enumerate(n[:-1]):
    rem = (rem * 10 + x) % b
    if n[i + 1] and not rem and not rems[i + 1]:
        OF.write("YES\n" + str(a[:i + 1]) + "\n" + str(a[i + 1:]))
        exit(0)
OF.write("NO")