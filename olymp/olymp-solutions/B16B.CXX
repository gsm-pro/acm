#include<fstream>
#include<vector>
using namespace std;
#define INF 1LL<<50
typedef long long LL;
ifstream I("input.txt");
ofstream O("output.txt");
vector<pair<LL, LL>> x;
LL z[10010][3003];
int n, k;

LL rec(int p, int k) {
	if (k == 0) return INF;
	if (p < 0) return 0;
	if (z[p][k] != -1) return z[p][k];
	LL t = INF, t1, t2;
	if (((t1 = rec(p - 1, k) + x[p].first)) <= x[p].second) t = min(t, t1);
	if (((t2 = rec(p - 1, k - 1))) <= x[p].second) t = min(t, t2);
	return z[p][k] = t;
}

int main() {
	I >> n >> k;
	x.resize(n);
	for (int i = 0; i < n; i++) {
		I >> x[i].first >> x[i].second;
		for (int j = 0; j <= k; j++) z[i][j] = -1;
	}
	for (int spent = 0; spent <= k - 1; spent++)
		if (rec(n - 1, spent + 1) != INF) return O << k - spent, 0;
	O << -1;
}