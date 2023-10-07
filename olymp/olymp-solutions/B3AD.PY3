IF = open("input.txt")
OF = open("output.txt", "w")
n = map(int, IF.readline().split())
a = list(map(int, IF.readline().split()))
k1 = 0
k2 = 0
for x in a:
    if x == 1:
        k1 += 1
    if x == 2:
        k2 += 1
k = min(k1, k2)
k1 -= k
k2 -= k
k += k1 // 3
OF.write(str(k))