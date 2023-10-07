import sys
from math import gcd as gcd

sys.stdin = open("input.txt", 'r')
sys.stdout = open("output.txt", 'w')
n = int(input())
sw = [int(x) for x in input().split()]
swx = max(sw)
y = 0
z = 0
for x in sw:
    z = gcd(z, swx - x)
for x in sw:
    if x != swx:
        y += (swx - x) // z
print(y, z)