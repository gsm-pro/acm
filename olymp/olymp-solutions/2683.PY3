IF = open("input.txt")
OF = open("output.txt", "w")
n = int(IF.readline())
a1 = list(map(int, IF.readline().split()))
a2 = list(map(int, IF.readline().split()))
b = list(map(int, IF.readline().split()))
res = []
for index in range(len(b)):
    res.append(b[index] + sum(a1[:index]) + sum(a2[index:]))
res.sort()
OF.write(str(res[0] + res[1]))