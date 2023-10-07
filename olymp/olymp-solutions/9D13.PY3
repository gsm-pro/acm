IF = open("input.txt")
OF = open("output.txt", "w")
n = int(IF.readline())
L = 0
R = 0
z = []
for i in range(n, 0, -1):
    if L <= R:
        L += i
        z.append(i)
    else:
        R += i
OF.write(str(abs(L - R)) + "\n" + str(len(z)) + " " + ' '.join(str(it) for it in z))