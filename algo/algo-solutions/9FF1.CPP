#include<vector>
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
typedef pair<int, int> PII;
#define MAXN 222222
#define NINF -(1 << 30)
#define FOR(i, a, b) for (int i = (a); i < (b); i++) 
#define REP(i, n) FOR(i, 0, n) 
#define SEUN(v) sort((v).begin(), (v).end()), v.erase(unique(v.begin(), v.end()), v.end())
int x[MAXN], y[MAXN], type[MAXN], n;
vector<PII> p;
vector<int> m;
string s;

void add(int x, int y) {
	int z = lower_bound(p.begin(), p.end(), PII(x, y)) - p.begin();
	z += p.size();
	while (z) {
		m[z] = max(m[z], y), z >>= 1;
	}
}

void remove(int x, int y) {
	int z = lower_bound(p.begin(), p.end(), PII(x, y)) - p.begin(), ps = (int)p.size();
	z += ps;
	while (z) {
		m[z] = NINF;
		if ((z << 1) < (ps << 1)) {
			m[z] = max(m[z], m[z << 1]);
		}
		if (((z << 1) | 1) < (ps << 1)) {
			m[z] = max(m[z], m[(z << 1) | 1]);
		}
		z >>= 1;
	}
}

int get(int p1, int p2) {
	int val = NINF;
	while (p1 <= p2) {
		val = max(val, m[p1]);
		val = max(val, m[p2]);
		p1 = (p1 + 1) >> 1;
		p2 = (p2 - 1) >> 1;
	}
	return val;
}

PII calc(int x, int y) {
	int pos = lower_bound(p.begin(), p.end(), PII(x + 1, y + 1)) - p.begin(), fin = p.size() - 1;
	pos += p.size(), fin += p.size();
	if (get(pos, fin) <= y) {
		return PII(-1, -1);
	}
	int best = -1;
	while (pos <= fin) {
		int s = (pos + fin) >> 1;
		if (get(pos, s) > y) {
			best = s, fin = s - 1;
		}
		else {
			pos = s + 1;
		}
	}
	return p[pos - p.size()];
}

int main() {
	cin >> n;
	REP(i, n) {
		cin >> s >> x[i] >> y[i];
		type[i] = (s[0] == 'a' ? 1 : s[0] == 'r' ? 2 : 3);
	}
	REP(i, n) {
		if (type[i] != 3) {
			p.push_back(PII(x[i], y[i]));
		}
	}
	SEUN(p);
	m.resize((p.size()) << 1, NINF);
	REP(i, n) {
		if (type[i] == 1) {
			add(x[i], y[i]);
		}
		if (type[i] == 2) {
			remove(x[i], y[i]);
		}
		if (type[i] == 3) {
			PII res = calc(x[i], y[i]);
			if (res.first < 0) {
				cout << -1;
			}
			else {
				cout << res.first << " " << res.second;
			}
			cout << "\n";
		}
	}
}