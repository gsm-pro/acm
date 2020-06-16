#include<iostream>
#include<algorithm>

int main() {
	int n, k, p, ans = 0;
	scanf_s("%d", &n);
	int* L = new int[n];
	int* R = new int[n];
	for (int i = 0; i < n; ++i) {
		scanf_s("%d%d", &L[i], &R[i]);
	}
	std::sort(L, L + n);
	std::sort(R, R + n);
	scanf_s("%d", &k);
	int* X = new int[k];
	for (int i = 0; i < k; i++) {
		scanf_s("%d", &X[i]);
	}
	scanf_s("%d", &p);
	for (int i = 0, x, cnt = 0; i < k; ++i) {
		x = X[i];
		int left = 0, right = n - 1, m;
		while (left <= right) {
			m = (left + right) / 2;
			if (L[m] > x) {
				right = m - 1;
			}
			else {
				left = m + 1;
			}
		}
		cnt = right + 1;
		left = 0;
		right = n - 1;
		while (left <= right) {
			m = (left + right) / 2;
			if (R[m] < x) {
				left = m + 1;
			}
			else {
				right = m - 1;
			}
		}
		cnt -= right + 1;
		if (cnt >= p) {
			ans++;
		}
	}
	delete[] L, R, X;
	printf("%d", ans);
}