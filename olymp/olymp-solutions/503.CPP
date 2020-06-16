#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;
vector<pair<int, int>> cmd;
int n, d[2002][2002][2], oo = 2000000000, ans = oo;
ifstream I("input.txt");
ofstream O("output.txt");

int main() {
	I >> n;
	cmd.resize(n);
	for (int i = 0; i < n; i++) {
		I >> cmd[i].first >> cmd[i].second;
	}
	sort(cmd.begin(), cmd.end());
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			d[i][j][0] = d[i][j][1] = oo;
		}
	}
	d[0][n - 1][0] = max(abs(cmd[0].first), cmd[0].second);
	d[0][n - 1][1] = max(abs(cmd[n - 1].first), cmd[n - 1].second);
	for (int L = 0; L < n; L++) {
		for (int R = n - 1; R >= L; R--) {
			for (int D = 0; D <= 1; D++) {
				d[L + !D][R - D][0] = min(d[L + !D][R - D][0], max(d[L][R][D] + abs(cmd[D ? R : L].first - cmd[L + !D].first), cmd[L + !D].second));
				d[L + !D][R - D][1] = min(d[L + !D][R - D][1], max(d[L][R][D] + abs(cmd[D ? R : L].first - cmd[R - D].first), cmd[R - D].second));
			}
		}
	}
	for (int i = 0; i < n; i++) {
		ans = min(ans, d[i][i][0]);
	}
	O << ans;
}