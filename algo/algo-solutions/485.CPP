#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define NMAX 111111
int n, a;
vector<vector<int>> g;
vector<int> ans;

int main() {
	g.resize(NMAX);
	ans.resize(NMAX);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a;
		g[a].push_back(i);
	}
	int thr = g[1].size();
	for (int i = 1; i <= NMAX; i++) {
		if ((int)g[i].size() > thr) {
			cout << -1;
			exit(0);
		}
		thr = (int)g[i].size();
	}
	int cnt = g[1].size();
	for (int i = 1; i <= NMAX; i++) {
		cnt = max(cnt, (int)g[i].size());
		for (int j = 0; j < (int)g[i].size(); j++) {
			ans[g[i][j]] = j + 1;
		}
	}
	cout << cnt << endl;
	for (int i = 1; i <= n; i++) {
		cout << ans[i] << " ";
	}
}