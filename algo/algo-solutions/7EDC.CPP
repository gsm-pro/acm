#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<algorithm>
using namespace std;
const int NMAX = 111111;
const int KMAX = 100;
int n, k;
int ans[NMAX];
pair<pair<int, int>, int> a[NMAX];

int main() {
	scanf("%d%d%*d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i].first.first);
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i].first.second);
		a[i].second = i + 1;
	}
	sort(a, a + n);
	double lf = 0, rg = n;
	for (int iter = 0; iter < KMAX; iter++) {
		double md;
		if (iter == KMAX - 1) {
			md = rg;
		}
		else {
			md = (lf + rg) / 2;
		}
		int j = 1;
		for (int i = 0; i < n && j <= k; i++) {
			if (j <= a[i].first.second * md) {
				ans[j++] = a[i].second;
			}
		}
		if (j > k) {
			rg = md;
		}
		else {
			lf = md;
		}
	}
	for (int j = 1; j <= k; j++) {
		printf("%d ", ans[j]);
	}
}