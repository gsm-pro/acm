import sys

sys.stdin = open("input.txt", 'r')
sys.stdout = open("output.txt", 'w')
n = int(input())
print(750 * n - (n // 13) * 350)