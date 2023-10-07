#include<fstream>
#include<vector>
#include<map>
#include<queue>
using namespace std;
vector<vector<int>> G;
vector<int> color012, color, parent;
map<pair<int, int>, int> W;
int N, K, SUM = 0, ANS = 0, CYC_S, CYC_F, i, u, v;

int getW(int x, int y) {
	return W[make_pair(min(x, y), max(x, y))];
}

bool putW(int x, int y, int w) {
	bool exist = getW(x, y) > 0;
	W[make_pair(min(x, y), max(x, y))] += w;
	return exist;
}

bool dfs(int v, int prev_v) {
	color012[v] = 1;
	for (size_t j = 0; j < G[v].size(); j++) {
		int to = G[v][j];
		if (to == prev_v) continue;
		if (color012[to] == 0) {
			parent[to] = v;
			if (dfs(to, v)) return true;
		}
		else if (color012[to] == 1) {
			CYC_F = v, CYC_S = to;
			return true;
		}
	}
	color012[v] = 2;
	return false;
}

int main() {
	ifstream I("input.txt");
	ofstream O("output.txt");
	I >> N >> K;
	G.resize(N);
	for (i = 0; i < N; i++) {
		I >> u >> v;
		SUM += v;
		if (!putW(u - 1, i, v)) {
			G[i].push_back(u - 1);
			G[u - 1].push_back(i);
		}
	}
	if (K == 1) {
		O << SUM << endl;
		for (i = 0; i < N; i++) O << "1 ";
		return 0;
	}
	color.resize(N);
	color012.resize(N);
	parent.assign(N, -1);
	for (i = 0; i < N; i++) {
		if (color[i] == 0) {
			queue<int> q;
			if (dfs(i, -1)) {
				vector<int> cycle;
				cycle.push_back(CYC_S);
				for (int v = CYC_F; v != CYC_S; v = parent[v]) cycle.push_back(v);
				cycle.push_back(CYC_S);
				if (K == 2 && !(cycle.size() & 1)) {
					int r1, r2, r, min_r = 1000000;
					for (size_t j = 0; j < cycle.size() - 1; j++)
						if ((r = getW(cycle[j], cycle[j + 1])) < min_r)
							min_r = r, r1 = cycle[j], r2 = cycle[j + 1];
					ANS += min_r;
					q.push(r1), color[r1] = 1;
					q.push(r2), color[r2] = 1;
				}
			}
			if (q.empty()) q.push(i), color[i] = 1;
			while (!q.empty()) {
				v = q.front();
				q.pop();
				map<int, bool> allowed;
				for (int c = 1; c <= min(K, 3); c++) allowed[c] = true;
				for (size_t j = 0; j < G[v].size(); j++) {
					int to = G[v][j];
					if (color[to] != 0 && color[v] == 0) allowed.erase(color[to]);
					if (color[to] == 0) q.push(to);
				}
				if (color[v] == 0) color[v] = allowed.begin()->first;
			}
		}
	}
	O << ANS << endl;
	for (i = 0; i < N; i++) O << color[i] << " ";
}