#include<bits/stdc++.h>
using namespace std;
string s, t;
int $, n, i, j, k, z[101][101], p[101];

int main() {
	ifstream I("input.txt");
	I >> s >> n;
	n = s.length();
	for (i = 0; i < n; i++)	for (j = 0; j < n; j++)	if (i != j) z[i][j] = 1000000;
	while (getline(I, t)) {
		if (!t.empty()) {
			stringstream ss(t);
			if (ss >> i >> j) z[i][j] = z[j][i] = 1; else p[i] = 1, $ += (s[i] == 'D');
		}
	}
	for (k = 0; k < n; k++)	for (i = 0; i < n; i++)	for (j = 0; j < n; j++)
		z[i][j] = min(z[i][j], z[i][k] + z[k][j]);
	for (i = 0; i < n; i++)
		if (s[i] == 'D' && !p[i]) {
			k = 1000000;
			for (j = 0; j < n; j++)	if (p[j]) k = min(k, z[i][j] + 1);
			$ += k;
		}
	ofstream("output.txt") << ($ >= 1000000 ? -1 : $);
}