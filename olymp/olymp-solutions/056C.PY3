IF = open("input.txt")
OF = open("output.txt", "w")
n = int(IF.readline())
a = [int(i) for i in IF.readline().split()]
u, v, ans = [], [], 0
for i in a:
    c = int(i ** (1 / 2))
    if c * c == i:
        u.append(i)
    else:
        v.append(min(i - c * c, (c + 1) * (c + 1) - i))
u.sort(reverse=True)
v.sort()
for i in range(len(u) - n // 2):
    ans += 1 + (u[i] == 0)
for i in range(n // 2 - len(u)):
    ans += v[i]
OF.write(str(ans))