#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;
vector<pair<int, int>> lr;
set<int> times;
map<int, int> trans;
int n, t, x[1000];

int main() {
	cin >> n;
	lr.resize(n);
	times.insert(0);
	for (int i = 0; i < n; i++) {
		cin >> lr[i].first >> lr[i].second;
		times.insert(lr[i].first);
		times.insert(lr[i].second);
	}
	cin >> t;
	times.insert(t);
	int counter = 0;
	for (set<int>::iterator it = times.begin(); it != times.end(); it++) {
		trans[*it] = counter++;
	}
	for (int i = 0; i < n; i++) {
		lr[i].first = 2 * trans[lr[i].first];
		lr[i].second = 2 * trans[lr[i].second];
	}
	t = 2 * trans[t];
	for (int i = 0; i < n; i++) {
		x[lr[i].first]++;
		x[lr[i].second + 1]--;
	}
	int ans = 999, cur = 0;
	for (int i = 0; i <= t; i++) {
		cur += x[i];
		ans = min(ans, cur);
	}
	cout << ans;
}