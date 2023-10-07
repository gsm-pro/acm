#include<iostream>
int N, M, cur, pair[500005], L[500005], R[500005];
char s[500002], c;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d%d%s", &N, &M, &cur, s + 1);
	for (int i = 1; i <= N; i++) {
		static int stack[500005], D;
		if (s[i] == '(') stack[++D] = i; else pair[i] = stack[D], pair[stack[D--]] = i;
	}
	for (int i = 0; i <= N; i++) R[i] = i + 1, L[i + 1] = i;
	while (M--) {
		do c = getchar(); while (c != 'L' && c != 'R' && c != 'D');
		if (c == 'L') cur = L[cur]; else if (c == 'R') cur = R[cur]; else {
			int x = cur, y = pair[cur], l, r;
			if (x < y) l = L[x], r = R[y]; else l = L[y], r = R[x];
			L[r] = l, R[l] = r;
			cur = r == N + 1 ? l : r;
		}
	}
	for (int i = R[0]; i <= N; i = R[i]) putchar(s[i]);
}