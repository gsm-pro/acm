#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;
#define N 220022
#define INF (1 << 30)
vector<int> g[N], cmp[N];
int cm[N], us[N], n, m;
__int64 ans = 0;

void dfs(int x, int cur) {
	if (cm[x] != -1) return;
	cm[x] = cur;
	for (size_t i = 0; i < g[x].size(); i++) dfs(g[x][i], cur);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> m;
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	while (true) {
		int cc = 0;
		for (int i = 0; i < n; i++) cm[i] = -1;
		for (int i = 0; i < n; i++) if (cm[i] == -1) dfs(i, cc++);
		for (int i = 0; i < cc; i++) cmp[i].clear();
		for (int i = 0; i < n; i++) cmp[cm[i]].push_back(i);
		if (cc == 1) break;
		set<pair<int, int>> st;
		memset(us, 0, sizeof us);
		for (int i = 0; i < n; i++) st.insert(make_pair(a[i], i));
		for (int i = 0; i < cc; i++) {
			if (us[i]) continue;
			for (size_t j = 0; j < cmp[i].size(); j++) {
				int y = cmp[i][j];
				st.erase(st.find(make_pair(a[y], y)));
			}
			int v1 = -1, v2 = -1, w = INF;
			for (size_t j = 0; j < cmp[i].size(); j++) {
				int y = cmp[i][j];
				set<pair<int, int>>::iterator it = st.begin();
				if (it != st.end()) {
					int cv1 = y, cv2 = it->second, cw = (a[cv1] + a[cv2]) % m;
					if (cw < w) v1 = cv1, v2 = cv2, w = cw;
				}
				it = st.lower_bound(make_pair(m - a[y], -INF));
				if (it != st.end()) {
					int cv1 = y, cv2 = it->second, cw = (a[cv1] + a[cv2]) % m;
					if (cw < w) v1 = cv1, v2 = cv2, w = cw;
				}
			}
			for (size_t j = 0; j < cmp[i].size(); j++) {
				int y = cmp[i][j];
				st.insert(make_pair(a[y], y));
			}
			ans += w, us[i] = 1, us[cm[v2]] = 1;
			g[v1].push_back(v2);
			g[v2].push_back(v1);
		}
	}
	cout << ans;
}