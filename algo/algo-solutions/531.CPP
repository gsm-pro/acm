#include<iostream>
using namespace std;
#define LL long long
#define INF 1LL<<44
const int NMAX = 8008;
LL P[NMAX];
int n, m, used[NMAX], A[NMAX];

LL go(int v) {
	memset(used, 0, sizeof used);
	for (int i = 0; i < NMAX; ++i) {
		P[i] = INF;
	}
	P[v] = 0;
	LL ans = 0;
	for (int i = 1; i <= n; i++) {
		int pos = 0;
		LL mx = INF;
		for (int j = 1; j <= n; j++) {
			if (!used[j] && mx >= P[j]) {
				mx = P[j];
				pos = j;
			}
		}
		used[pos] = 1;
		ans += P[pos];
		for (int j = 1; j <= n; j++) {
			if (!used[j]) {
				int w = (A[pos] + A[j]) % m;
				if (P[j] > w) {
					P[j] = w;
				}
			}
		}
	}
	return ans;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> A[i];
	}
	cout << go(1);
}