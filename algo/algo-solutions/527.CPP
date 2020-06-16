#include<iostream> 
#include<vector> 
#include<iomanip>
#include<algorithm>
using namespace std;
typedef long double LD;
const LD EPS = (LD)(1e-12);
const int MAX_ITERS = 1000;
vector<pair<LD, int>> k;

LD f(LD x) {
	LD z = 0;
	for (size_t i = 0; i < k.size(); i++) {
		LD d = fabsl(k[i].first - x);
		int t = k[i].second;
		if (t == 1) {
			z += d;
		}
		if (t == 2) {
			z += d * logl(d + 1.);
		}
		if (t == 3) {
			z += d * sqrtl(d);
		}
		if (t == 4) {
			z += d * d;
		}
	}
	return z;
}

int main() {
	int n;
	LD l = 1.1e6, r = -l;
	cin >> n;
	k.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> k[i].first >> k[i].second;
		l = min(l, k[i].first);
		r = max(r, k[i].first);
	}
	int i = 0;
	while (r - l > EPS && i <= MAX_ITERS) {
		LD a = l + (r - l) * 0.05;
		LD b = r - (r - l) * 0.05;
		if (f(a) < f(b)) {
			r = b;
		}
		else {
			l = a;
		}
		i++;
	}
	cout << setprecision(10) << fixed << f(l) << endl << l;
}