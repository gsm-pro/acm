IF = open("input.txt")
OF = open("output.txt", "w")
n, m = map(int, IF.readline().split())
is_rect = [0] * m
for i in range(0, n):
    s = IF.readline()
    in_rect = False
    for j in range(0, m):
        line = s[j] <= "B"
        edge = s[j] >= "C"
        if in_rect:
            if edge:
                if is_rect[j]:
                    OF.write("C")
                    is_rect[j] = False
                else:
                    OF.write("F")
                    is_rect[j] = True
                in_rect = False
            if line:
                OF.write("A")
                is_rect[j] = False
            continue
        if not in_rect:
            if edge:
                if is_rect[j]:
                    OF.write("D")
                    is_rect[j] = False
                else:
                    OF.write("E")
                    is_rect[j] = True
                in_rect = True
            if line:
                OF.write("B")
                is_rect[j] = True
            continue
    OF.write("\n")