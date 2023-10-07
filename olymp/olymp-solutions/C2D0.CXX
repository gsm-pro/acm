#include<fstream>
#include<vector>
using namespace std;
vector<pair<int, int>> a, b;
int n, x;

int main() {
	ifstream I("input.txt");
	ofstream O("output.txt");
	I >> n;
	while (n--) {
		I >> x;
		if (a.size() && a.back().first == x) a.back().second++;
		else a.push_back(make_pair(x, 1));
	}
	int ans = 0;
	while (a.size()) {
		int maxl = 0, index = 0;
		for (size_t i = 0; i < a.size(); i++)
			if (a[i].second > maxl) {
				maxl = a[i].second;
				index = int(i);
			}
		b.clear();
		for (size_t i = 0; i < a.size(); i++)
			if (i != index) b.push_back(a[i]);
		for (size_t i = 0; i < b.size(); i++)
			if (i && b[i - 1].first == b[i].first) {
				b[i - 1].second += b[i].second;
				b[i].second = 0;
			}
		a.clear();
		for (size_t i = 0; i < b.size(); i++)
			if (b[i].second > 0) a.push_back(b[i]);
		ans++;
	}
	O << ans;
}