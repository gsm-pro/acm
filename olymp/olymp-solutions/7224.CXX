#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
typedef pair<int, int> PII;
typedef vector<int> VI;
vector<PII> e;

bool cmp(PII a, PII b) {
	if (a.first > b.first) return 1;
	if (a.first == b.first && a.second < b.second) return 1;
	return 0;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, i;
	scanf("%d", &n);
	e.resize(n);
	for (i = 0; i < n; i++) scanf("%d%d", &e[i].first, &e[i].second);
	sort(e.begin(), e.end(), cmp);
	VI a(n), d(n + 1, INF), no(n + 1), p(n);
	for (i = 0; i < n; i++) a[i] = e[i].second;
	d[0] = -INF;
	no[0] = -1;
	for (i = 0; i < n; i++) {
		auto j = upper_bound(d.begin(), d.end(), a[i]) - d.begin() - 1;
		if (d[j] <= a[i] && a[i] <= d[j + 1]) d[j + 1] = a[i], p[i] = no[j], no[j + 1] = i;
	}
	VI result;
	for (i = n; i >= 1; i--)
		if (d[i] != INF) {
			for (int cur = no[i]; cur != -1; cur = p[cur]) result.push_back(cur);
			break;
		}
	printf("%d\n", (int)result.size());
	for (auto r : result)printf("%d %d\n", e[r].first, e[r].second);
}