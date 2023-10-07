#include<bits/stdc++.h>
using namespace std;
string $;

bool calc(int obs) {
	int c = 0, m = 0;
	for (const auto& x : $) {
		m = max(m, c);
		if (x == 'R') c++; else if (x == 'L' and c > obs + 1) c--;
	}
	return c > m;
}

int main() {
	ifstream("input.txt") >> $;
	ofstream $$("output.txt");
	if ($.back() == 'L') for (auto& x : $) x = 158 - x;
	if (calc(-100000000)) return $$ << 1, 0;
	int l = -$.size(), r = 0;
	while (l + 1 < r) {
		int m = (l + r) / 2;
		if (calc(m)) r = m; else l = m + 1;
	}
	$$ << (calc(l) ? abs(l) : abs(r));
}