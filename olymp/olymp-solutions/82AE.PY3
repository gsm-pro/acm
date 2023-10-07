IF = open("input.txt")
OF = open("output.txt", "w")
n = int(IF.readline())
a = list(map(int, IF.readline().split()))
t = min(a.count(1), a.count(2), a.count(3))
OF.write(str(t) + "\n")
for i in range(t):
    r, b, c = a.index(1), a.index(2), a.index(3)
    OF.write(str(r + 1) + " " + str(b + 1) + " " + str(c + 1) + "\n")
    a[r] = a[b] = a[c] = 0