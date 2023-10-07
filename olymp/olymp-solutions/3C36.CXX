#include<fstream>
#include<vector>
using namespace std;
int m, n, k, c;
vector<int> color[100001];

int main() {
	ifstream I("input.txt");
	I >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		I >> c;
		color[c].push_back(i);
	}
	int ans = 0;
	for (int c = 1; c <= m; c++) {
		for (int i = 0, j = 0; j < color[c].size(); j++) {
			while ((color[c][j] - color[c][i] - j + i) > k) i++;
			ans = max(ans, j - i + 1);
		}
	}
	ofstream("output.txt") << ans;
}