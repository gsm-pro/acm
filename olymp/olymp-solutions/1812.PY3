IF = open("input.txt")
OF = open("output.txt", "w")
find_left = {}
find_right = {}
n = int(IF.readline())
for i in range(n):
    a, b = map(int, IF.readline().split())
    find_left[a] = b
    find_right[b] = a
first_el = 0
for key in find_left:
    if key not in find_right:
        first_el = key
        break
second_el = find_left[0]
ans = [0] * n
ans[0] = first_el
ans[1] = second_el
for i in range(2, n):
    ans[i] = find_left[ans[i - 2]]
for val in ans:
    OF.write(str(val) + " ")