#include<fstream>
#include<algorithm>
#include<vector>
#include<map>
#include<iomanip>
#include<cmath>
using namespace std;
#define F first
#define S second
typedef double LD;
typedef pair<LD, LD> PLD;
typedef pair<int, int> PII;
typedef vector<PLD> VPLD;
typedef pair<PII, PII> PPII;
typedef vector<PPII> VPPII;
const LD EPS = 1e-8;

class SegmentHandler {
private:
	vector<PII> rib;
	map<PII, size_t> rib2id;
	vector<vector<int>> g;
	vector<size_t> t, f, c;
	vector<bool> used;
	int timer = 0;

	struct Segment {
		LD a, b, c, ax, ay, bx, by, minx, maxx, miny, maxy;

		Segment(PLD z1, PLD z2) {
			LD _ax, _ay, _bx, _by;
			ax = _ax = z1.F, ay = _ay = z1.S, bx = _bx = z2.F, by = _by = z2.S;
			a = _by - _ay, b = _ax - _bx, c = -(a * _ax + b * _ay);
			if (_ax > _bx) swap(_ax, _bx);
			if (_ay > _by) swap(_ay, _by);
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
		return eq((z.F - a.ax) * (a.by - a.ay), (z.S - a.ay) * (a.bx - a.ax))
			&& gr((z.F - a.ax) * (a.bx - a.ax) + (z.S - a.ay) * (a.by - a.ay), .0)
			&& gr((z.F - a.bx) * (a.ax - a.bx) + (z.S - a.by) * (a.ay - a.by), .0);
	}

	LD det2(LD ax, LD ay, LD bx, LD by) {
		return ax * by - ay * bx;
	}

	bool incl(VPLD z, Segment a) {
		if (z.size() == 2)
			for (int i = 0; i <= 1; i++)
				if (eq(a.ax, z[i].F) && eq(a.ay, z[i].S)
					&& eq(a.bx, z[1 - i].F) && eq(a.by, z[1 - i].S)) return true;
		return false;
	}

	LD dist(PLD z1, PLD z2) {
		return sqrtl(powl(z1.F - z2.F, 2) + powl(z1.S - z2.S, 2));
	}

	VPLD inter(Segment A, Segment B) {
		LD d = det2(A.a, A.b, B.a, B.b);
		VPLD pts;
		if (eq(d, .0)) {
			if (neq(A.a * B.ax + A.b * B.ay + A.c, .0)
				|| neq(B.a * A.ax + B.b * A.ay + B.c, .0)) return pts;
			if (le(A.maxx, B.minx) || gr(A.minx, B.maxx)
				|| le(A.maxy, B.miny) || gr(A.miny, B.maxy)) return pts;
			LD xx1 = max(A.minx, B.minx), xx2 = min(A.maxx, B.maxx),
				yy1 = max(A.miny, B.miny), yy2 = min(A.maxy, B.maxy);
			if (neq(A.a * xx1 + A.b * yy1 + A.c, .0)) swap(yy1, yy2);
			pts.push_back(make_pair(LD(xx1), LD(yy1)));
			if (neq(xx1, xx2) || neq(yy1, yy2)) pts.push_back(make_pair(LD(xx2), LD(yy2)));
		}
		else {
			LD x = -det2(A.c, A.b, B.c, B.b) / d, y = -det2(A.a, A.c, B.a, B.c) / d;
			if (le(x, A.minx) || gr(x, A.maxx) || le(y, A.miny) || gr(y, A.maxy)) return pts;
			if (le(x, B.minx) || gr(x, B.maxx) || le(y, B.miny) || gr(y, B.maxy)) return pts;
			pts.push_back(make_pair(x, y));
		}
		return pts;
	}

	void dfs(int v, int p = -1) {
		used[v] = true;
		t[v] = f[v] = timer++;
		for (size_t i = 0; i < g[v].size(); i++) {
			int to = g[v][i];
			if (to == p) continue;
			if (used[to]) f[v] = min(f[v], t[to]); else {
				dfs(to, v);
				f[v] = min(f[v], f[to]);
				if (f[to] > t[v]) c.push_back(rib2id[make_pair(v, to)]);
			}
		}
	}

public:
	LD solve(VPPII Z) {
		vector<Segment> sourceSegm;
		VPLD allp;
		for (size_t i = 0; i < Z.size(); i++) {
			LD x1 = Z[i].F.F, y1 = Z[i].F.S, x2 = Z[i].S.F, y2 = Z[i].S.S;
			if (eq(x1, x2) && eq(y1, y2)) continue;
			PLD p1 = make_pair(x1, y1), p2 = make_pair(x2, y2);
			sourceSegm.push_back(Segment(p1, p2));
			allp.push_back(p1);
			allp.push_back(p2);
		}
		size_t n = sourceSegm.size();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < i; j++) {
				VPLD pts = inter(sourceSegm[i], sourceSegm[j]);
				if (pts.size() > 0) allp.push_back(pts[0]);
				if (pts.size() > 1) allp.push_back(pts[1]);
			}
		sort(allp.begin(), allp.end());
		size_t ap = allp.size();
		VPLD points;
		points.push_back(allp[0]);
		for (int i = 1; i < ap; i++)
			if (neq(allp[i].F, allp[i - 1].F)
				|| neq(allp[i].S, allp[i - 1].S)) points.push_back(allp[i]);
		size_t p = points.size();
		for (int i = 0; i < p; i++) {
			for (int j = 0; j < i; j++) {
				Segment ijSegm = Segment(points[i], points[j]);
				bool ok = false;
				for (int k = 0; k < n; k++)
					if (incl(inter(sourceSegm[k], ijSegm), ijSegm)) {
						ok = true;
						break;
					}
				if (!ok) continue;
				ok = true;
				for (int k = 0; k < p; k++)
					if (k != i && k != j)
						if (onSegment(points[k], ijSegm)) {
							ok = false;
							break;
						}
				if (ok) {
					PII w1 = make_pair(i, j), w2 = make_pair(j, i);
					rib2id[w1] = rib2id[w2] = rib.size();
					rib.push_back(w1);
				}
			}
		}
		g.resize(p);
		for (size_t i = 0; i < rib.size(); i++) {
			g[rib[i].F].push_back(rib[i].S);
			g[rib[i].S].push_back(rib[i].F);
		}
		used.assign(p, false);
		t.resize(p);
		f.resize(p);
		for (int i = 0; i < p; i++)
			if (!used[i]) dfs(i);
		LD ans = 0;
		for (size_t i = 0; i < c.size(); i++)
			ans += dist(points[rib[c[i]].F], points[rib[c[i]].S]);
		return ans;
	}
} segmentHandler;

int main() {
	ifstream I("input.txt");
	int n;
	I >> n;
	VPPII Z(n);
	for (int i = 0; i < n; i++) I >> Z[i].F.F >> Z[i].F.S >> Z[i].S.F >> Z[i].S.S;
	ofstream("output.txt") << fixed << setprecision(8) << segmentHandler.solve(Z);
}