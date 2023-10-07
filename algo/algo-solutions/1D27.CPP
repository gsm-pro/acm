#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define INF 1e10
#define SZ 111
double w[SZ][SZ];
vector<double> s, a;

double rec(int l, int r)
{
	if (r == l + 1) return .0;
	if (w[l][r] != -1) return w[l][r];
	double q = INF;
	for (int i = l + 1; i < r; i++)
		q = min(q, (a[r] - a[l]) + rec(l, i) + rec(i, r));
	w[l][r] = q;
	return q;
}

int main() {
	double t, c;
	int n;
	cin >> t >> n;
	for (int i = 0; i < n; i++) {
		cin >> c;
		s.push_back(c);
	}
	sort(s.begin(), s.end());
	a.push_back(0);
	for (size_t i = 0; i < s.size(); i++)
		a.push_back((a.back() * 100.0 / t + s[i]) * t / 100.0);
	for (int i = 0; i < SZ; i++) for (int j = 0; j < SZ; j++) w[i][j] = -1.0;
	cout.precision(9);
	cout << fixed << rec(0, n) + t;
}