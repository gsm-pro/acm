#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
using namespace std;
const int NMAX = 11111;
int PERM[NMAX], SQRT[NMAX], A[NMAX], n, S[NMAX];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &PERM[i]);
	}
	for (int i = 1; i <= n; ++i) {
		if (A[PERM[i]]) {
			continue;
		}
		int cur = 0;
		for (int j = PERM[i]; !A[PERM[j]]; j = PERM[j]) {
			cur++;
			A[PERM[j]] = 1;
		}
		if (cur & 1) {
			int v = PERM[i], u = PERM[i];
			for (int j = 0; j < (cur) / 2; j++) {
				v = PERM[v];
			}
			SQRT[i] = v;
			for (int j = 0; j < cur - 1; j++) {
				SQRT[u] = PERM[v];
				v = PERM[v];
				u = PERM[u];
			}
		}
		else {
			int t = S[cur];
			if (t == 0) {
				S[cur] = i;
				continue;
			}
			S[cur] = 0;
			int u = i;
			for (int j = 0; j < cur; j++) {
				SQRT[t] = u;
				SQRT[u] = PERM[t];
				t = PERM[t];
				u = PERM[u];
			}
		}
	}
	for (int i = 0; i <= n; i += 2) {
		if (S[i]) {
			puts("No solution");
			return 0;
		}
	}
	for (int i = 1; i <= n; ++i) {
		printf("%d ", SQRT[i]);
	}
}