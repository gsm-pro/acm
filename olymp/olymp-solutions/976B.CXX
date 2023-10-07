#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("unroll-loops")
#include<fstream>
#include<algorithm>
#include<unordered_map>
using namespace std;
double* w;
double* inv;

struct __attribute__((packed)) Piece {
	unsigned id : 8;
	unsigned cuts : 24;
	double value;

	Piece() {}

	Piece(unsigned id, unsigned cuts) :id(id), cuts(cuts), value(w[id] * inv[cuts]) {}
} pieces[15000152];

signed main() {
	inv = new double[100001];
	for (unsigned i = 0; i <= 100000; i++) inv[i] = 1. / (i + 1);
	ifstream I("input.txt");
	unsigned n, k, L = 0, R = -1;
	double ans = 2e9;
	I >> n >> k;
	w = new double[n + 1];
	unsigned sz = 0;
	for (unsigned i = 1; i <= n; i++) {
		I >> w[i];
		for (unsigned j = 0; j <= k; j++) pieces[sz++] = Piece(i, j);
	}
	sort(pieces, pieces + sz, [](const Piece& p1, const Piece& p2)
		{ return p1.value > p2.value; });
	unordered_map<unsigned, unsigned> ids2qty;
	bool stopR = false;
	unsigned cur_cuts = 0;
	while (L < sz) {
		if (ids2qty.size() < n) {
			if (stopR) break;
			R++;
			while (!stopR) {
				if (++ids2qty[pieces[R].id] == 1)
					cur_cuts += pieces[R].cuts;
				if (R + 1 == sz) {
					stopR = true;
					break;
				}
				if (ids2qty.size() == n) break;
				R++;
			}
		}
		if (ids2qty.size() == n && cur_cuts <= k)
			ans = min(ans, pieces[L].value - pieces[R].value);
		if (!--ids2qty[pieces[L].id]) {
			ids2qty.erase(pieces[L].id);
			cur_cuts -= pieces[L].cuts;
		}
		else cur_cuts++;
		L++;
	}
	ofstream O("output.txt");
	O.precision(9);
	O << fixed << ans;
}