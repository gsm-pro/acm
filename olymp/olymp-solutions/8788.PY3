IF = open("input.txt")
OF = open("output.txt", "w")
n = int(IF.readline())
a = list(map(int, IF.readline().split()))
p = [0] * n
for i in range(0, n):
    p[a[i] - 1] = i + 1
s = 0
for i in range(1, n):
    s += abs(p[i] - p[i - 1])
OF.write(str(s))