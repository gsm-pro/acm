#include<fstream>
#include<string>
#include<algorithm>
#include<numeric>
using namespace std;
int n, st[10], dig[10], p[10], best = 1000000000;
string s;

int main() {
	ifstream I("input.txt");
	I >> n;
	while (n--) {
		I >> s;
		st[s[0] - 'a'] = 1;
		for (int i = (int)s.size() - 1, p = 1; i >= 0; i--, p *= 10)
			dig[s[i] - 'a'] += p;
	}
	iota(p, p + 10, 0);
	do {
		int w = 0, pos0 = 0;
		for (int i = 0; i < 10; i++) {
			w += dig[i] * p[i];
			if (p[i] == 0) pos0 = i;
		}
		if (!st[pos0]) best = min(best, w);
	} while (next_permutation(p, p + 10));
	ofstream("output.txt") << best;
}