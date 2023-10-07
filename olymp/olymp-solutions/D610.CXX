#include<fstream>
#include<cstring>
#include<vector>
using namespace std;
vector<int> g[6666];
int n, ans = 0, z[6666], r[6666];

void dfs(int u, int p = 0) {
	int pos = int(lower_bound(z, z + n, r[u]) - z), zpos = z[pos];
	z[pos] = r[u], ans = max(ans, pos);
	for (auto v : g[u]) if (v != p) dfs(v, u);
	z[pos] = zpos;
}

int main() {
	ifstream I("input.txt");
	I >> n;
	for (int i = 1; i <= n; i++) I >> r[i];
	for (int i = 1, u, v; i <= n - 1; i++) {
		I >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	memset(z, 0x3f, sizeof z);
	for (int i = 1; i <= n; i++) dfs(i);
	ofstream("output.txt") << ans + 1;
}