#include<fstream>
#include<set>
using namespace std;
unsigned w[30], n, k, $$ = 2000000000, sum = 0;
multiset<unsigned> $;

void add(unsigned z) {
	sum += z;
	$.insert(z);
	if ($.size() > n) sum -= *--$.end(), $.erase(--$.end());
}

unsigned del() {
	unsigned z = *$.begin();
	sum -= z, $.erase($.begin());
	return z;
}

signed main() {
	ifstream I("input.txt");
	I >> n >> k;
	for (unsigned i = 0; i < k; i++) I >> w[i], add(w[i]);
	while (' ') {
		bool b = n == $.size() && sum < $$;
		if (!($.size() < n || b)) return ofstream("output.txt") << $$, 0;
		if (b) $$ = sum;
		for (unsigned i = 0, z = del(); i < k; i++) add(z + w[i]);
	}
}