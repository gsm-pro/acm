#include<fstream>
#include<vector>
using namespace std;
vector<int> x;
int n, a, ans = 0;

int main() {
	ifstream I("input.txt");
	ofstream O("output.txt");
	I >> n;
	x.resize(n);
	for (int i = 0; i < n; i++) I >> x[i];
	for (int i = 0; i < n; i++) {
		for (int j = i, s = 0, t = 0; j < n; j++) {
			t++;
			s += x[j];
			if (s > 100 * t) ans = max(ans, t);
		}
	}
	O << ans;
}