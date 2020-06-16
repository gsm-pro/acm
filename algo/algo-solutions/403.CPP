#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct point {
	int x, y;
};

struct angle {
	int a, b;
};

bool operator < (const angle &p, const angle &q) {
	if (p.b == 0 && q.b == 0) return p.a < q.a;
	return p.a * 1LL * q.b < p.b * 1LL * q.a;
}

long long sq(point &a, point &b, point &c) {
	return a.x * 1LL * (b.y - c.y) + b.x * 1LL * (c.y - a.y) + c.x * 1LL * (a.y - b.y);
}

bool oriented(vector<point> p) {
	int n = (int)p.size();
	p.push_back(p[0]);
	long long ans = 0;
	for (int i = 0; i < n; ++i) ans += 1LL * (p[i + 1].x - p[i].x) * (p[i + 1].y + p[i].y);
	return ans <= 0;
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	vector<point> p(n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &p[i].x, &p[i].y);
	}
	if (!oriented(p)) {
		reverse(p.begin(), p.end());
	}
	int index0 = 0;
	for (int i = 0; i < n; i++) {
		if (p[i].x < p[index0].x || p[i].x == p[index0].x && p[i].y < p[index0].y) {
			index0 = i;
		}
	}
	point zero = p[index0];
	rotate(p.begin(), p.begin() + index0, p.end());
	p.erase(p.begin());
	n--;
	vector<angle> a(n);
	for (int i = 0; i < n; i++) {
		a[i].a = p[i].y - zero.y;
		a[i].b = p[i].x - zero.x;
		if (a[i].a == 0) {
			a[i].b = a[i].b < 0 ? -1 : 1;
		}
	}
	for (int i = 0; i < m; i++) {
		point q;
		scanf("%d%d", &q.x, &q.y);
		bool inside = false;
		bool boundary = false;
		if (q.x >= zero.x) {
			if (q.x == zero.x && q.y == zero.y)
				boundary = true;
			else {
				angle ang = { q.y - zero.y,q.x - zero.x };
				if (ang.a == 0) ang.b = ang.b < 0 ? -1 : 1;
				vector<angle>::iterator it = upper_bound(a.begin(), a.end(), ang);
				if (it == a.end() && ang.a == a[n - 1].a && ang.b == a[n - 1].b) it = a.end() - 1;
				if (it != a.end() && it != a.begin()) {
					int pp = int(it - a.begin());
					long long w = sq(p[pp], p[pp - 1], q);
					if (w == 0) {
						boundary = true;
					}
					if (w < 0) {
						inside = true;
					}
				}
			}
		}
		puts(inside ? "YES" : boundary ? "YES" : "NO");
	}
}