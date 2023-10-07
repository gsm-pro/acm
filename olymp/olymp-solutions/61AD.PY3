IF = open("input.txt")
OF = open("output.txt", "w")
a = list(map(int, IF.readline().split()))
if a[0] <= a[2] <= a[1]:
    OF.write(str(a[3]))
elif a[2] < a[0]:
    OF.write(str(a[3] + 4 * (a[0] - a[2])))
elif a[2] > a[1]:
    OF.write(str(a[3] + 4 * (a[2] - a[1])))