#include<vector>
#include<string>
#include<iostream>
using namespace std;
vector<string> v;
vector<vector<pair<int, int>>> ans;
vector<vector<int>> z;

inline vector<int> prefix_function(string &s, int vnum) {
	size_t len = s.length();
	vector<int> pi(len);
	for (size_t i = 1; i < len; i++) {
		if (i < z[vnum].size() && z[vnum][i] != -1) {
			pi[i] = z[vnum][i];
		}
		else {
			int j = pi[i - 1];
			while (j > 0 && s[i] != s[j]) j = pi[j - 1];
			if (s[i] == s[j]) j++;
			pi[i] = j;
			if (i < z[vnum].size()) z[vnum][i] = pi[i];
		};
	}
	return pi;
}

int main() {
	int n, m, x, y, w;
	cin >> n;
	v.resize(n);
	ans.resize(n);
	z.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
		ans[i].resize(v[i].size());
	}
	for (int i = 0; i < n; i++) {
		int len_vi = v[i].size();
		z[i].assign(len_vi, -1);
		for (int j = 0; j < n; j++) {
			int len_vj = v[j].size();
			string u = v[i] + "#" + v[j];
			u[len_vi + 1] = '*';
			vector<int> p = prefix_function(u, i);
			for (size_t k = len_vi + 1; k < p.size(); k++) {
				int index_j = k - len_vi - 1;
				if (ans[j][index_j].second < p[k]) {
					ans[j][index_j].first = i + 1;
					ans[j][index_j].second = p[k];
				}
			}
		}
	}
	cin >> m;
	while (m-- > 0) {
		scanf_s("%d%d", &x, &y);
		--x, --y;
		w = ans[x][y].second;
		printf("%d %d\n", w == 0 ? 1 : ans[x][y].first, w);
	}
}