#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>  
#include<algorithm>  
using namespace std;
#define M 555555
int n, p = 0;
pair<int, int> a[M];

bool z(long double t) {
	long double d = -1e24;
	for (int i = 0; i < n; i++) {
		if (a[i].second > 0) {
			d = max(d, a[i].first + t*a[i].second);
			continue;
		}
		if (a[i].first + t*a[i].second <= d) {
			return true;
		}
	}
	return false;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &a[i].first, &a[i].second);
	}
	long double l = 0.0, r = 1e12;
	while (p++ < 111) {
		long double mid = (l + r) / 2;
		if (z(mid)) {
			r = mid;
		}
		else {
			l = mid;
		}
	}
	if (r == 1e12) {
		puts("-1");
		return 0;
	}
	printf("%.18lf", l);
}