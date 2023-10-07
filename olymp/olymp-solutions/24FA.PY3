IF = open("input.txt")
OF = open("output.txt", "w")
n = int(IF.readline())
a = int(IF.readline())
b = int(IF.readline())
d = [n, n, n]
d[0] -= b
if a <= d[0]:
    d[0] -= a
else:
    d[1] -= a
if a <= d[0]:
    d[0] -= a
else:
    if a <= d[1]:
        d[1] -= a
    else:
        d[2] -= a
OF.write(str(int(d[0] < n) + int(d[1] < n) + int(d[2] < n)))