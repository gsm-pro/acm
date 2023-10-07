#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define forn(i,n) for (int i = 0; i < int(n); i++)
#define all(a) a.begin(), a.end()
#define sz(a) int(a.size())
#define mp make_pair
#define pb push_back
#define fs first
#define sc second
const int N = 355;
const int M = 110011;
const int oo = 1 << 30;
typedef pair<int, int> pii;
int n, m;

struct edge {
	int x, y, len, id;

	edge() {}
	edge(int x, int y, int len, int id) : x(x), y(y), len(len), id(id) {}
};

vector<edge> g;
int W[M];

int relax(int v, const vector<vector<int>> &g, vector<pii> &in) {
	int& ans = in[v].fs;
	if (ans != -1) {
		return ans;
	}
	ans = in[v].sc;
	forn(i, sz(g[v])) {
		ans ^= relax(g[v][i], g, in);
	}
	return ans;
}

inline vector<int> ChuLiuEdmondsLosImpl(int root, int n, vector<edge> e) {
	vector<pii> in(sz(e), mp(-1, 0));
	vector<vector<int>> g(sz(e));
	vector<bool> rem(n, true);
	rem[root] = false;
	forn(i, sz(e)) {
		e[i].id = i;
	}
	while (1) {
		vector<int> p(n, -1);
		vector<int> pw(n, oo);
		forn(i, sz(e)) {
			int v = e[i].y;
			if (v != root && pw[v] > e[i].len) {
				pw[v] = e[i].len, p[v] = i;
			}
		}
		forn(i, n) {
			if (rem[i] && p[i] == -1) {
				return vector<int>();
			}
		}
		int c = 0;
		vector<int> cycle, comp(n, -1);
		forn(i, n) {
			if (comp[i] == -1) {
				int v = i;
				while (v != -1 && comp[v] == -1) {
					cycle.pb(v);
					comp[v] = c;
					v = p[v] == -1 ? -1 : e[p[v]].x;
				}
				if (v != -1 && comp[v] == c) {
					int idx = int(find(all(cycle), v) - cycle.begin());
					forn(j, idx) {
						comp[cycle[j]] = -1;
					}
					cycle.erase(cycle.begin(), cycle.begin() + idx);
					break;
				}
				cycle.clear();
				c++;
			}
		}
		if (cycle.empty()) {
			forn(i, n) {
				if (p[i] != -1) {
					in[e[p[i]].id].sc ^= 1;
				}
			}
			break;
		}
		int mv = oo, mp = -1;
		forn(i, sz(cycle)) {
			edge& cure = e[p[cycle[i]]];
			in[cure.id].sc ^= 1;
			if (mv > cure.len) {
				mv = cure.len, mp = cure.id;
			}
			rem[cycle[i]] = (i == 0);
		}
		in[mp].sc ^= 1;
		forn(i, sz(e)) {
			if (comp[e[i].x] != c || comp[e[i].y] != c) {
				if (comp[e[i].y] == c) {
					e[i].len -= pw[e[i].y];
					e[i].len += mv;
					g[e[p[e[i].y]].id].pb(e[i].id);
					g[mp].pb(e[i].id);
				}
				if (comp[e[i].x] == c) {
					e[i].x = cycle[0];
				}
				if (comp[e[i].y] == c) {
					e[i].y = cycle[0];
				}
			}
		}
		forn(i, sz(e)) {
			if (comp[e[i].x] == c && comp[e[i].y] == c) {
				swap(e[i], e.back());
				e.pop_back();
				i--;
			}
		}
	}
	vector<int> ans;
	forn(i, sz(in)) {
		if (relax(i, g, in)) {
			ans.pb(i);
		}
	}
	return ans;
}

int main() {
	cin >> n >> m;
	forn(i, m) {
		int x, y, len;
		cin >> x >> y >> len;
		x--, y--;
		if (y == 0 || x == y) {
			len = oo;
		}
		g.pb(edge(x, y, len, i));
		W[i] = len;
	}
	vector<int> ans = ChuLiuEdmondsLosImpl(0, n, g);
	if (sz(ans) == 0 && n > 1) {
		return puts("-1"), 0;
	}
	cout << sz(ans) << endl;
	forn(i, sz(ans)) {
		cout << ans[i] + 1 << " ";
	}
}