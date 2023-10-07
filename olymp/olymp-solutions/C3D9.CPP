#include<fstream>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;

int gcd(int a, int b) {
	while (b) {
		b ^= a ^= b ^= a %= b;
	}
	return a;
}

int gcdx(int a, int b) {
	return gcd(abs(a), abs(b)) * ((a <= 0 && b <= 0) ? -1 : (a > 0 && b < 0) ? -1 : 1);
}

int main() {
	ifstream I("input.txt");
	ofstream O("output.txt");
	int n;
	I >> n;
	vector<pair<int, int>> P(n);
	for (int i = 0; i < n; i++) {
		I >> P[i].first >> P[i].second;
	}
	P.erase(unique(P.begin(), P.end()), P.end());
	n = P.size();
	map<pair<int, int>, int> D;
	map<int, int> diffx, diffy;
	for (int i = 0; i < n; i++) {
		diffx[P[i].first]++;
		diffy[P[i].second]++;
		for (int j = 0; j < i; j++) {
			int dx = P[i].first - P[j].first,
				dy = P[i].second - P[j].second,
				d = gcdx(dx, dy);
			if (dx != 0 && dy != 0) {
				if (d != 1) {
					dx /= d, dy /= d;
				}
				D[make_pair(dx, dy)]++;
			}
		}
	}
	vector<pair<int, pair<double, double>>> vec;
	for (map<pair<int, int>, int>::iterator it = D.begin(); it != D.end(); it++) {
		vec.push_back(make_pair(it->second, make_pair(it->first.first, it->first.second)));
	}
	int ans = min(diffx.size(), diffy.size()), e = min(100, (int)vec.size());
	sort(vec.begin(), vec.end());
	reverse(vec.begin(), vec.end());
	for (int i = 0; i < e; i++) {
		vector<double> F;
		for (int j = 0; j < n; j++) {
			F.push_back(P[j].second - (vec[i].second.second / vec[i].second.first) * P[j].first);
		}
		sort(F.begin(), F.end());
		int cur = 0;
		for (int i = 0; i < n; i++) {
			if (!i || fabs(F[i] - F[i - 1]) > 1e-8) {
				cur++;
			}
		}
		ans = min(ans, cur);
	}
	O << ans;
}