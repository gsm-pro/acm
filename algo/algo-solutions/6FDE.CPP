#include<cstdio>

int main() {
	int t, n, a, b, r, i;
	scanf("%d", &t);
	while (t--) {
		r = 0;
		scanf("%d", &n);
		for (i = 1; i <= n; i++) {
			scanf("%d", &a);
			b = a;
			if (!(a & 3)) b--;
			if ((a & 3) == 3) b++;
			r ^= b;
		}
		printf(r ? "FIRST\n" : "SECOND\n");
	}
}