#include<bits/stdc++.h>
using namespace std;
typedef long double LD;
set<LD> S;
LD ans = -1., pi = 3.1415926535897932384626433832795L;

int main() {
	int n;
	ifstream I("input.txt");
	I >> n;
	vector<LD> L;
	while (I >> n) {
		L.push_back(fmod(n, 2 * pi));
		S.insert(L.back());
	}
	sort(L.begin(), L.end());
	for (size_t i = 0; i < L.size() - 1; i++) ans = max(ans, sin(L[i] + L[i + 1]));
	for (size_t i = 0; i < L.size(); i++) {
		S.erase(L[i]);
		for (int j = -7; j <= 9; j += 4) {
			auto it = S.lower_bound(j * pi / 2 - L[i]);
			if (it != S.end()) {
				ans = max(ans, sin(L[i] + *it));
				if (it != S.begin()) ans = max(ans, sin(L[i] + *(--it)));
			}
		}
		S.insert(L[i]);
	}
	ofstream("output.txt") << fixed << setprecision(15) << ans;
}