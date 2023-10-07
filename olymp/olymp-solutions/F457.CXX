#include<fstream>
#include<vector>
using namespace std;
int n, m, k, from[210], to[210], cnt = 0;
vector<pair<int, int>> ans;
bool empty[210];

int main() {
	for (int i = 0; i < 210; i++) empty[i] = true;
	ifstream I("input.txt");
	I >> n >> m;
	for (int i = 0; i < m; i++) {
		I >> k;
		for (int j = 0; j < k; j++)
			I >> from[cnt], from[cnt]--, to[cnt] = cnt, empty[from[cnt]] = false, cnt++;
	}
	while (true) {
		bool finish = true, found = false;
		for (int i = 0; i < cnt; i++)
			if (from[i] != to[i]) finish = false;
		if (finish) break;
		for (int i = 0; i < cnt; i++)
			if (empty[to[i]]) {
				found = true, empty[to[i]] = false, empty[from[i]] = true, ans.push_back(make_pair(from[i], to[i]));
				from[i] = to[i];
				break;
			}
		if (found) continue;
		int x = -1, y = -1, id = -1;
		for (int i = 0; i < n; i++)
			if (empty[i]) y = i;
		for (int i = 0; i < cnt; i++)
			if (from[i] != to[i]) x = from[i], id = i;
		empty[x] = true, empty[y] = false, from[id] = y, ans.push_back(make_pair(x, y));
	}
	ofstream O("output.txt");
	O << ans.size() << endl;
	for (int i = 0; i < ans.size(); i++)
		O << ans[i].first + 1 << ' ' << ans[i].second + 1 << endl;
}