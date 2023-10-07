#include<iostream>
using namespace std;
int a[100011], b[100011], n, k;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	__int64 mid, s = 1LL, e = 2000000000LL, res = 0;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
	while (s <= e) {
		mid = (s + e) / 2;
		__int64 magic = 0LL;
		for (int i = 1; i <= n; i++) {
			magic += max(mid * a[i] - b[i], 0LL);
			if (magic > k) {
				e = mid - 1;
				break;
			}
		}
		if (magic <= k) s = mid + 1, res = mid;
	}
	printf("%lld", res);
}