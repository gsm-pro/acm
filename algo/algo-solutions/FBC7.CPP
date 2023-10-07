#define _USE_MATH_DEFINES
#include<iostream>
#include<set>
#include<vector>
#include<algorithm>
#include<cmath>
#define C(a) (int)(a.size())
#define EPS 1e-8
using namespace std;
vector<pair<int, int>> pt;
set<vector<int>> simpleFacetsOrOneExternal;
vector<vector<int>> g;

class cmp {
	int center;
public:
	cmp(int center) : center(center) {}
	bool operator() (int a, int b) {
		double x1 = pt[a].first, y1 = pt[a].second, x2 = pt[b].first, y2 = pt[b].second;
		x1 -= pt[center].first, y1 -= pt[center].second,
			x2 -= pt[center].first, y2 -= pt[center].second;
		double ang1 = atan2(y1, x1) * 180 / M_PI + (y1 < 0) * 360,
			ang2 = atan2(y2, x2) * 180 / M_PI + (y2 < 0) * 360;
		if (ang1 < ang2) return true;
		return false;
	}
};

int main() {
	int m, n, k;
	cin >> m;
	while (m-- > 0) {
		g.clear();
		pt.clear();
		simpleFacetsOrOneExternal.clear();
		cin >> n;
		g.resize(n);
		pt.resize(n);
		for (int i = 0; i < n; i++) {
			int idx, x, y, d, v;
			cin >> idx >> x >> y >> d;
			--idx;
			pt[idx] = make_pair(x, y);
			for (int j = 0; j < d; j++) {
				cin >> v;
				--v;
				g[idx].push_back(v);
				g[v].push_back(idx);
			}
		}
		cin >> k;
		for (int i = 0; i < n; i++) {
			sort(g[i].begin(), g[i].end());
			g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end());
		}
		for (int i = 0; i < n; i++) sort(g[i].begin(), g[i].end(), cmp(i));
		vector<vector<char>> used(n);
		for (int i = 0; i < n; i++) used[i].resize(C(g[i]));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < C(g[i]); j++) {
				if (!used[i][j]) {
					used[i][j] = true;
					int v = g[i][j], pv = i;
					vector<int> facet;
					for (;;) {
						facet.push_back(v);
						vector<int>::iterator it = find(g[v].begin(), g[v].end(), pv);
						if (++it == g[v].end()) it = g[v].begin();
						if (used[v][it - g[v].begin()]) break;
						used[v][it - g[v].begin()] = true;
						pv = v, v = *it;
					}
					if (C(facet) > 0) {
						double area = 0;
						facet.push_back(facet[0]);
						for (int k = 0; k < C(facet) - 1; k++)
							area += (pt[facet[k]].first + pt[facet[k + 1]].first) * (pt[facet[k]].second - pt[facet[k + 1]].second);
						if (area > EPS) {
							facet.pop_back();
							sort(facet.begin(), facet.end());
							bool isSimple = true;
							for (int z = 0; z < C(facet) - 1; z++) {
								if (facet[z] == facet[z + 1]) isSimple = false;
							}
							if (isSimple) simpleFacetsOrOneExternal.insert(facet);
						}
					}
				}
			}
		}
		int ans = 0;
		for (set<vector<int>>::iterator it = simpleFacetsOrOneExternal.begin(); it != simpleFacetsOrOneExternal.end(); it++) {
			vector<int> p = *it;
			if (C(p) == k) ans++;
		}
		cout << ans << endl;
	}
}