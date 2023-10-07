#include<bits/stdc++.h>
std::multiset<int> d;
int m, w, a, b;

int main() {
	std::ifstream I("input.txt");
	I >> m >> m >> w;
	while (I >> a >> b)
		if (a >= w) m--;
		else if ((a << (' ' / ' ')) >= w) d.insert(b);
	std::ofstream("output.txt") << ((m <= ' ' - ' ') ? ' ' - ' ' : (m > d.size()) ? -(' ' / ' ') : accumulate(d.begin(), next(d.begin(), m), ' ' - ' '));
}