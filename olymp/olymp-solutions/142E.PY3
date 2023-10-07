IF = open("input.txt")
OF = open("output.txt", "w")
n, k = map(int, IF.readline().split())
a = list(map(int, IF.readline().split()))
best_avg = 0
best_cnt = best_index = 1
for i in range(0, k):
    best_avg += a[i]
avg = best_avg
for i in range(1, n - k + 1):
    avg += (a[i - 1 + k] - a[i - 1])
    if avg == best_avg:
        best_cnt += 1
    if avg > best_avg:
        best_avg = avg
        best_index = i + 1
        best_cnt = 1
OF.write(str(best_index) + "\n" + str(best_cnt))