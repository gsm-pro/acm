#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<iomanip>
using namespace std;
typedef long double LD;
typedef pair<LD, LD> PLD;
typedef pair<int, int> PII;
typedef vector<PLD> VPLD;
const LD EPS = 1e-8;
vector<PII> rib;
map<PII, int> rib2id;
vector<vector<int>> g;
vector<int> t, f, c;
vector<char> used;
int timer = 0, n, ap, p;

struct Segment {
	LD a, b, c, ax, ay, bx, by, minx, maxx, miny, maxy;

	Segment(PLD z1, PLD z2) {
		LD _ax, _ay, _bx, _by;
		ax = _ax = z1.first, ay = _ay = z1.second, bx = _bx = z2.first, by = _by = z2.second;
		a = _by - _ay, b = _ax - _bx, c = -(a * _ax + b * _ay);
		if (_ax > _bx) {
			swap(_ax, _bx);
		}
		if (_ay > _by) {
			swap(_ay, _by);
		}
		minx = _ax, maxx = _bx, miny = _ay, maxy = _by;
	}
};

bool eq(LD a, LD b) {
	return fabsl(a - b) < EPS;
}

bool neq(LD a, LD b) {
	return !eq(a, b);
}

bool gr(LD a, LD b) {
	return a - EPS > b;
}

bool le(LD a, LD b) {
	return b - EPS > a;
}

bool onSegment(PLD z, Segment a) {
	return eq((z.first - a.ax) * (a.by - a.ay), (z.second - a.ay) * (a.bx - a.ax)) &&
		gr((z.first - a.ax) * (a.bx - a.ax) + (z.second - a.ay) * (a.by - a.ay), .0) &&
		gr((z.first - a.bx) * (a.ax - a.bx) + (z.second - a.by) * (a.ay - a.by), .0);
}

LD det2(LD ax, LD ay, LD bx, LD by) {
	return ax * by - ay * bx;
}

bool incl(VPLD z, Segment a) {
	if (z.size() == 2) {
		for (int i = 0; i <= 1; i++) {
			if (eq(a.ax, z[i].first)
				&& eq(a.ay, z[i].second)
				&& eq(a.bx, z[1 - i].first)
				&& eq(a.by, z[1 - i].second)) {
				return true;
			}
		}
	}
	return false;
}

LD dist(PLD z1, PLD z2) {
	return sqrtl(powl(z1.first - z2.first, 2) + powl(z1.second - z2.second, 2));
}

VPLD inter(Segment A, Segment B) {
	LD d = det2(A.a, A.b, B.a, B.b);
	VPLD pts;
	if (eq(d, .0)) {
		if (neq(A.a * B.ax + A.b * B.ay + A.c, .0) || neq(B.a * A.ax + B.b * A.ay + B.c, .0)) {
			return pts;
		}
		if (le(A.maxx, B.minx) || gr(A.minx, B.maxx) || le(A.maxy, B.miny) || gr(A.miny, B.maxy)) {
			return pts;
		}
		LD xx1 = max(A.minx, B.minx), xx2 = min(A.maxx, B.maxx), yy1 = max(A.miny, B.miny), yy2 = min(A.maxy, B.maxy);
		if (neq(A.a * xx1 + A.b * yy1 + A.c, .0)) {
			swap(yy1, yy2);
		}
		pts.push_back(make_pair(LD(xx1), LD(yy1)));
		if (neq(xx1, xx2) || neq(yy1, yy2)) {
			pts.push_back(make_pair(LD(xx2), LD(yy2)));
		}
	}
	else {
		LD x = -det2(A.c, A.b, B.c, B.b) / d, y = -det2(A.a, A.c, B.a, B.c) / d;
		if (le(x, A.minx) || gr(x, A.maxx) || le(y, A.miny) || gr(y, A.maxy)) {
			return pts;
		}
		if (le(x, B.minx) || gr(x, B.maxx) || le(y, B.miny) || gr(y, B.maxy)) {
			return pts;
		}
		pts.push_back(make_pair(x, y));
	}
	return pts;
}

void dfs(int v, int p = -1) {
	used[v] = true;
	t[v] = f[v] = timer++;
	for (size_t i = 0; i < g[v].size(); i++) {
		int to = g[v][i];
		if (to == p) {
			continue;
		}
		if (used[to]) {
			f[v] = min(f[v], t[to]);
		}
		else {
			dfs(to, v);
			f[v] = min(f[v], f[to]);
			if (f[to] > t[v]) {
				c.push_back(rib2id[make_pair(v, to)]);
			}
		}
	}
}

int main() {
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
	vector<Segment> sourceSegm;
	VPLD allpoints;
	cin >> n;
	while (n--) {
		LD x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		if (eq(x1, x2) && eq(y1, y2)) {
			continue;
		}
		PLD p1 = make_pair(x1, y1), p2 = make_pair(x2, y2);
		sourceSegm.push_back(Segment(p1, p2));
		allpoints.push_back(p1);
		allpoints.push_back(p2);
	}
	n = (int)sourceSegm.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			VPLD pts = inter(sourceSegm[i], sourceSegm[j]);
			if (pts.size() > 0) {
				allpoints.push_back(pts[0]);
			}
			if (pts.size() > 1) {
				allpoints.push_back(pts[1]);
			}
		}
	}
	sort(allpoints.begin(), allpoints.end());
	ap = (int)allpoints.size();
	VPLD points;
	points.push_back(allpoints[0]);
	for (int i = 1; i < ap; i++) {
		if (neq(allpoints[i].first, allpoints[i - 1].first) ||
			neq(allpoints[i].second, allpoints[i - 1].second)) {
			points.push_back(allpoints[i]);
		}
	}
	p = (int)points.size();
	for (int i = 0; i < p; i++) {
		for (int j = 0; j < i; j++) {
			if (i != j) {
				Segment ijSegm = Segment(points[i], points[j]);
				bool ok = false;
				for (int k = 0; k < n; k++) {
					if (incl(inter(sourceSegm[k], ijSegm), ijSegm)) {
						ok = true;
						break;
					}
				}
				if (!ok) {
					continue;
				}
				ok = true;
				for (int k = 0; k < p; k++) {
					if (k != i && k != j) {
						if (onSegment(points[k], ijSegm)) {
							ok = false;
							break;
						}
					}
				}
				if (ok) {
					PII w1 = make_pair(i, j), w2 = make_pair(j, i);
					rib2id[w1] = rib2id[w2] = rib.size();
					rib.push_back(w1);
				}
			}
		}
	}
	g.resize(p);
	for (size_t i = 0; i < rib.size(); i++) {
		g[rib[i].first].push_back(rib[i].second);
		g[rib[i].second].push_back(rib[i].first);
	}
	used.assign(p, false);
	t.resize(p);
	f.resize(p);
	for (int i = 0; i < p; i++) {
		if (!used[i]) {
			dfs(i);
		}
	}
	LD ans = 0;
	for (size_t i = 0; i < c.size(); i++) {
		ans += dist(points[rib[c[i]].first], points[rib[c[i]].second]);
	}
	cout << fixed << setprecision(8) << ans;
}