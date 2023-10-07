#include<iostream>
#include<vector>
using namespace std;
vector<int> a[333];
int n, m, x, i, j, t;

bool fail() {
	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++) {
			bool u = false;
			for (t = 0; t < n; t++) {
				if (a[i][j] > a[i][t] + a[t][j]) return true;
				if (t != i && t != j && a[i][j] == a[i][t] + a[t][j]) u = true;
			}
			if (!u) m--;
		}
	return m < 0;
}

int main() {
	cin >> n >> m;
	for (i = 0; i < n; i++) {
		a[i].push_back(0);
		for (j = i + 1; j < n; j++) {
			cin >> x;
			a[i].push_back(x);
			a[j].push_back(x);
		}
	}
	for (i = fail(); i < 5; i += 2) cout << "YNEOS"[i];
}