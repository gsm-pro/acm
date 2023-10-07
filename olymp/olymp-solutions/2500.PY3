import math

n = int(open("input.txt").readline())
k = 2 * n * n * (n - 1) * (n - 1)
if n > 3:
    k += 2 * n * n * math.factorial(n - 1) // math.factorial(n - 4)
open("output.txt", "w").write(str(k))