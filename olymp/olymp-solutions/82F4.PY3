IF = open("input.txt")
OF = open("output.txt", "w")

def find_power(a, c):
    f = 0
    while a % c == 0:
        f += 1
        a //= c
    return f

def remove_two_three(x):
    while x % 2 == 0:
        x //= 2
    while x % 3 == 0:
        x //= 3
    return x

a1, b1 = map(int, IF.readline().split(" "))
a2, b2 = map(int, IF.readline().split(" "))
c1 = a1 * b1
c2 = a2 * b2
if remove_two_three(c1) != remove_two_three(c2):
    OF.write(str(-1))
    exit(0)
z2_1 = z3_1 = z2_2 = z3_2 = 0
k1 = find_power(c1, 3)
k2 = find_power(c2, 3)
if k1 > k2:
    z3_1 = k1 - k2
    c1 /= 3 ** z3_1
    c1 *= 2 ** z3_1
elif k1 < k2:
    z3_2 = k2 - k1
    c2 /= 3 ** z3_2
    c2 *= 2 ** z3_2
k1 = find_power(c1, 2)
k2 = find_power(c2, 2)
if k1 > k2:
    z2_1 = k1 - k2
    c1 /= 2 ** z2_1
elif k1 < k2:
    z2_2 = k2 - k1
    c2 /= 2 ** z2_2
if c1 != c2:
    OF.write(str(-1))
    exit(0)
OF.write(str(z2_1 + z3_1 + z2_2 + z3_2) + "\n")
while a1 % 3 == 0 and z3_1 > 0:
    a1 //= 3
    a1 *= 2
    z3_1 -= 1
while b1 % 3 == 0 and z3_1 > 0:
    b1 //= 3
    b1 *= 2
    z3_1 -= 1
while a2 % 3 == 0 and z3_2 > 0:
    a2 //= 3
    a2 *= 2
    z3_2 -= 1
while b2 % 3 == 0 and z3_2 > 0:
    b2 //= 3
    b2 *= 2
    z3_2 -= 1
while a1 % 2 == 0 and z2_1 > 0:
    a1 //= 2
    z2_1 -= 1
while b1 % 2 == 0 and z2_1 > 0:
    b1 //= 2
    z2_1 -= 1
while a2 % 2 == 0 and z2_2 > 0:
    a2 //= 2
    z2_2 -= 1
while b2 % 2 == 0 and z2_2 > 0:
    b2 //= 2
    z2_2 -= 1
OF.write(str(a1) + " " + str(b1) + "\n" + str(a2) + " " + str(b2))