#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
typedef unsigned long long ULL;
typedef unsigned int UI;
using namespace std;
ifstream I("input.txt");
ofstream O("output.txt");

struct Query {
	ULL q, pos_in_block;
	UI order;
	char answer;
};

vector<Query> queries;

inline UI digcnt(UI x) {
	switch (x) {
	case 1:
		return 1;
	case 10:
		return 2;
	case 100:
		return 3;
	case 1000:
		return 4;
	case 10000:
		return 5;
	case 100000:
		return 6;
	case 1000000:
		return 7;
	case 10000000:
		return 8;
	case 100000000:
		return 9;
	}
	return 0;
}

char digit(ULL num, UI index) {
	return to_string(num)[index];
}

char digit(ULL pib) {
	if (pib <= 9LL) return digit(pib, 0);
	pib -= 9;
	if (pib <= 180LL) return digit(10LL + (pib - 1) / 2, (pib - 1) % 2);
	pib -= 180LL;
	if (pib <= 2700LL) return digit(100LL + (pib - 1) / 3, (pib - 1) % 3);
	pib -= 2700LL;
	if (pib <= 36000LL) return digit(1000LL + (pib - 1) / 4, (pib - 1) % 4);
	pib -= 36000LL;
	if (pib <= 450000LL) return digit(10000LL + (pib - 1) / 5, (pib - 1) % 5);
	pib -= 450000LL;
	if (pib <= 5400000LL) return digit(100000LL + (pib - 1) / 6, (pib - 1) % 6);
	pib -= 5400000LL;
	if (pib <= 63000000LL) return digit(1000000LL + (pib - 1) / 7, (pib - 1) % 7);
	pib -= 63000000LL;
	if (pib <= 720000000LL) return digit(10000000LL + (pib - 1) / 8, (pib - 1) % 8);
	pib -= 720000000LL;
	if (pib <= 8100000000LL) return digit(100000000LL + (pib - 1) / 9, (pib - 1) % 9);
	pib -= 8100000000LL;
	if (pib <= 90000000000LL) return digit(1000000000LL + (pib - 1) / 10, (pib - 1) % 10);
	throw;
}

signed main() {
	ULL q, total_len = 0, prev_total_len = 0;
	UI n, cur_block = 1, number_len = 0, block_len = 0, cur_len, cur_query = 0;
	I >> n;
	for (UI i = 0; i < n; i++) {
		I >> q;
		queries.push_back({ q, 0, i, ' ' });
	}
	sort(queries.begin(), queries.end(), [](const Query& q1, const Query& q2)
		{ return q1.q < q2.q; });
	while (true) {
		if ((cur_len = digcnt(cur_block)) != 0) number_len = cur_len;
		block_len += number_len, total_len += block_len;
		if (total_len >= queries[cur_query].q) {
			while (total_len >= queries[cur_query].q) {
				queries[cur_query].pos_in_block = queries[cur_query].q - prev_total_len;
				cur_query++;
				if (cur_query == n) break;
			}
			if (cur_query == n) break;
		}
		prev_total_len = total_len, cur_block++;
	}
	sort(queries.begin(), queries.end(), [](const Query& q1, const Query& q2)
		{ return q1.order < q2.order; });
	for (UI i = 0; i < n; i++) O << digit(queries[i].pos_in_block) << endl;
}