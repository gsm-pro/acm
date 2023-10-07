IF = open("input.txt")
OF = open("output.txt", "w")
s = IF.readline().strip().replace("-", "").replace("+", "")
if len(s) == 6:
    OF.write("+78452" + s)
else:
    if s[0] == '8':
        OF.write("+7" + s[1:])
    else:
        OF.write("+" + s)