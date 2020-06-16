#include<vector>
#include<iostream>
#include<algorithm>
#include<cassert>
using namespace std;
long long sum = 0, l = 0, r = (1LL << 60), mid, a[55] = { 0 };
int n, k;

int main() {
	cin >> k >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	assert(k <= n);
	sort(a, a + n);
	for (int i = 0; i < n - k; i++) sum += a[i];
	long long ans = a[n - k];
	while (l <= r) {
		mid = (l + r) >> 1;
		long long s = sum;
		vector<long long> temp;
		for (int i = n - k; i < n; i++) temp.push_back(a[i]);
		for (int i = 0; i < k; i++) {
			if (temp[i] < mid) {
				long long s_temp = s;
				s -= min(mid - temp[i], s);
				temp[i] += min(mid - temp[i], s_temp);
				if (s <= 0) break;
			}
		}
		long long minimum = (1LL << 60);
		for (int i = 0; i < k; i++) minimum = min(minimum, temp[i]);
		if (minimum < mid) {
			r = mid - 1;
		}
		if (minimum >= mid) {
			l = mid + 1;
		}
		if (minimum >= mid && minimum > ans) {
			ans = minimum;
		}
	}
	cout << ans;
}