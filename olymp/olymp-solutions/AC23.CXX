#include<fstream>
#include<algorithm>
#include<cmath>
#include<vector>
#include<map>
#include<unordered_map>
#include<cassert>
using namespace std;
#define pi 3.14159265358979323846L
#define F first
#define S second
#define mp make_pair
#define pb push_back
typedef long long LL;
typedef long double LD;
typedef unsigned int UI;
#define sz(x) UI((x).size())
typedef pair<UI, UI> PUIUI;
typedef pair<LL, LL> PLL;
typedef pair<LD, LD> PLD;
typedef pair<PLD, PLD> PPLD;
typedef pair<LD, UI> PLDUI;
typedef vector<bool> VB;
typedef vector<LL> VLL;
typedef vector<LD> VLD;
typedef vector<UI> VUI;
typedef vector<VUI> VVUI;
typedef vector<VB> VVB;
typedef vector<PUIUI> VPUIUI;
typedef vector<PLD> VPLD;
typedef vector<PPLD> VPPLD;
typedef vector<PLDUI> VPLDUI;
ifstream I("input.txt");
ofstream O("output.txt");
const LD EPS = .1L;
unordered_map<UI, unordered_map<UI, PLL>> DP;
vector<pair<LD, PLD>> pts;
map<PLD, LD> pts2polar;
LD R, A, B, C, COEF, SQCOEF, LLCOEF = 1048576.L, SQ;
VPPLD Z;
VLL $;
UI N, PIECES;

LD polar(PLD p) {
	return atan2(p.S, p.F) * 180. / pi + (p.S < 0) * 360.;
}

LD roundTo10(LD x) {
	return round(x * 10000000000.L) / 10000000000.L;
}

PLD roundTo10(PLD x) {
	return mp(roundTo10(x.F), roundTo10(x.S));
}

bool eq(LD a, LD b) {
	return fabsl(a - b) < EPS;
}

bool neq(LD a, LD b) {
	return !eq(a, b);
}

bool gr(LD a, LD b) {
	return a - EPS > b;
}

bool greq(LD a, LD b) {
	return gr(a, b) || eq(a, b);
}

bool le(LD a, LD b) {
	return b - EPS > a;
}

bool leeq(LD a, LD b) {
	return le(a, b) || eq(a, b);
}

bool eq(PLD a, PLD b) {
	return eq(a.F, b.F) && eq(a.S, b.S);
}

bool eq(PPLD a, PPLD b) {
	return (eq(a.F, b.F) && eq(a.S, b.S)) || (eq(a.F, b.S) && eq(a.S, b.F));
}

class SegmentHandler {
private:
	map<UI, map<UI, UI>> pointNumbers2egdeId;
	VPUIUI pointNumbersEdges;

	struct Segment {
		LD a, b, c, ax, ay, bx, by, minx, maxx, miny, maxy;

		Segment(PLD z1, PLD z2) {
			LD _ax, _ay, _bx, _by;
			ax = _ax = z1.F, ay = _ay = z1.S, bx = _bx = z2.F, by = _by = z2.S;
			a = _by - _ay, b = _ax - _bx, c = -a * _ax - b * _ay;
			if (_ax > _bx) swap(_ax, _bx);
			if (_ay > _by) swap(_ay, _by);
			minx = _ax, maxx = _bx, miny = _ay, maxy = _by;
		}
	};

	bool onSegment(PLD z, Segment a) {
		return eq((z.F - a.ax) * (a.by - a.ay), (z.S - a.ay) * (a.bx - a.ax))
			&& greq((z.F - a.ax) * (a.bx - a.ax) + (z.S - a.ay) * (a.by - a.ay), .0)
			&& greq((z.F - a.bx) * (a.ax - a.bx) + (z.S - a.by) * (a.ay - a.by), .0);
	}

	LD det(LD ax, LD ay, LD bx, LD by) {
		return ax * by - ay * bx;
	}

	VPLD inter(Segment A, Segment B) {
		LD d = det(A.a, A.b, B.a, B.b);
		VPLD pts;
		if (eq(d, .0)) {
			if (neq(A.a * B.ax + A.b * B.ay + A.c, .0)
				|| neq(B.a * A.ax + B.b * A.ay + B.c, .0)) return pts;
			if (le(A.maxx, B.minx) || gr(A.minx, B.maxx)
				|| le(A.maxy, B.miny) || gr(A.miny, B.maxy)) return pts;
			LD xx1 = max(A.minx, B.minx), xx2 = min(A.maxx, B.maxx),
				yy1 = max(A.miny, B.miny), yy2 = min(A.maxy, B.maxy);
			if (neq(A.a * xx1 + A.b * yy1 + A.c, .0)) swap(yy1, yy2);
			pts.pb(mp(xx1, yy1));
			if (neq(xx1, xx2) || neq(yy1, yy2)) pts.pb(mp(xx2, yy2));
		}
		else {
			LD x = -det(A.c, A.b, B.c, B.b) / d, y = -det(A.a, A.c, B.a, B.c) / d;
			if (le(x, A.minx) || gr(x, A.maxx) || le(y, A.miny) || gr(y, A.maxy)) return pts;
			if (le(x, B.minx) || gr(x, B.maxx) || le(y, B.miny) || gr(y, B.maxy)) return pts;
			pts.pb(mp(x, y));
		}
		return pts;
	}

public:
	VPPLD handle(VPPLD Z) {
		vector<Segment> SRC;
		VPLD all;
		for (auto& z : Z) {
			LD x1 = z.F.F, y1 = z.F.S, x2 = z.S.F, y2 = z.S.S;
			if (eq(x1, x2) && eq(y1, y2)) continue;
			PLD p1 = roundTo10(mp(x1, y1)), p2 = roundTo10(mp(x2, y2));
			SRC.pb(Segment(p1, p2));
			all.pb(p1);
			all.pb(p2);
		}
		for (UI i = 0; i < sz(SRC); i++)
			for (UI j = 0; j < i; j++) {
				VPLD pts = inter(SRC[i], SRC[j]);
				if (sz(pts) > 0) all.pb(roundTo10(pts[0]));
				if (sz(pts) > 1) all.pb(roundTo10(pts[1]));
			}
		sort(all.begin(), all.end());
		VPLD PTS;
		PTS.pb(all[0]);
		for (UI i = 1; i < sz(all); i++)
			if (neq(all[i].F, all[i - 1].F) || neq(all[i].S, all[i - 1].S)) PTS.pb(all[i]);
		for (UI i = 0; i < sz(SRC); i++) {
			VUI pointNumbersOnLine;
			for (UI j = 0; j < sz(PTS); j++)
				if (onSegment(PTS[j], SRC[i])) pointNumbersOnLine.push_back(j);
			for (UI j = 0; j < sz(pointNumbersOnLine) - 1; j++) {
				UI x = pointNumbersOnLine[j], y = pointNumbersOnLine[j + 1];
				if (!pointNumbers2egdeId[x].count(y) && !pointNumbers2egdeId[y].count(x)) {
					pointNumbers2egdeId[x][y] = pointNumbers2egdeId[y][x] = sz(pointNumbersEdges);
					pointNumbersEdges.pb(mp(x, y));
				}
			}
		}
		VPPLD ans;
		for (auto& r : pointNumbersEdges) ans.pb(mp(PTS[r.F], PTS[r.S]));
		return ans;
	}
} segmentHandler;

class FacetSqCalculator {
private:
	void dfs(VVUI& g, VVB& used, VUI& c, UI v, UI w) {
		for (UI i = 0; i < sz(g[v]); i++)
			if (g[v][i] == w) {
				if (++i == sz(g[v])) i = 0;
				if (!used[v][i]) {
					used[v][i] = true;
					c.pb(v);
					dfs(g, used, c, g[v][i], v);
				}
				break;
			}
	}

	LD sq(VUI& c, VPLD& PTS) {
		if (sz(c) < 3) return .0;
		c.pb(c[0]);
		LD ans = .0;
		for (UI i = 0; i < sz(c) - 1; i++)
			ans += (PTS[c[i + 1]].F - PTS[c[i]].F) * (PTS[c[i + 1]].S + PTS[c[i]].S);
		c.pop_back();
		return ans / 2.;
	}

	VLD addSegmentsSq(LD s, VUI& c, VPLD& PTS) {
		VLD ss;
		c.pb(c[0]);
		for (UI i = 0; i < sz(c) - 1; i++) {
			PLD c0 = PTS[c[i]], c1 = PTS[c[i + 1]];
			if (pts2polar.count(c0) && pts2polar.count(c1)) {
				bool neigh = false;
				for (UI j = N; j < sz(Z); j++)
					if (eq(Z[j], mp(c0, c1))) neigh = true;
				if (!neigh) continue;
				bool outer = false;
				for (UI j = 0; j < N; j++)
					if (eq(Z[j], mp(c0, c1))) outer = true;
				LD p0 = pts2polar[c0], p1 = pts2polar[c1];
				swap(p0, p1);
				if (p0 > p1) p1 += 360.;
				LD arcLen = 2 * pi * R * (p1 - p0) / 360.,
					sss = .5 * R * R * (arcLen / R - sin(arcLen / R));
				if (outer) ss.pb(sss); else s += sss;
			}
		}
		c.pop_back();
		ss.pb(s);
		return ss;
	}

public:
	VLL calc(VPPLD Z) {
		UI m = sz(Z);
		VPLD a(m * 2);
		for (UI i = 0; i < m; i++)
			a[i * 2].F = Z[i].F.F, a[i * 2].S = Z[i].F.S,
			a[i * 2 + 1].F = Z[i].S.F, a[i * 2 + 1].S = Z[i].S.S;
		VPLD PTS(a);
		sort(PTS.begin(), PTS.end());
		PTS.erase(unique(PTS.begin(), PTS.end()), PTS.end());
		UI n = sz(PTS);
		VVUI g(n);
		for (UI i = 0, id1, id2; i < m; i++)
			g[id1 = UI(lower_bound(PTS.begin(), PTS.end(), a[i * 2]) - PTS.begin())]
			.pb(id2 = UI(lower_bound(PTS.begin(), PTS.end(), a[i * 2 + 1]) - PTS.begin())), g[id2].pb(id1);
		for (UI i = 0; i < n; i++) {
			VPLDUI b(sz(g[i]));
			for (UI j = 0, to; j < sz(g[i]); j++)
				to = g[i][j], b[j] = mp(atan2(.0 + PTS[to].S - PTS[i].S, .0 + PTS[to].F - PTS[i].F), to);
			sort(b.begin(), b.end());
			b.erase(unique(b.begin(), b.end()), b.end());
			g[i].clear();
			for (UI j = 0; j < sz(b); j++) g[i].pb(b[j].S);
		}
		VVB used(n);
		for (UI i = 0; i < n; i++) used[i].resize(sz(g[i]));
		VLL areas;
		for (UI i = 0; i < n; i++)
			for (UI j = 0; j < sz(g[i]); j++)
				if (!used[i][j]) {
					VUI cyc;
					dfs(g, used, cyc, g[i][j], i);
					LD s = sq(cyc, PTS);
					if (greq(s, .0)) {
						auto ar = addSegmentsSq(s, cyc, PTS);
						for (auto x : ar) areas.push_back(LL(x * LLCOEF));
					}
				}
		return areas;
	}
} facetSqCalculator;

VPLD interc(LD r, LD a, LD b, LD c) {
	VPLD res;
	LD z = a * a + b * b, x0 = -a * c / z, y0 = -b * c / z;
	if (c * c - r * r * z > EPS) return res;
	if (fabsl(c * c - r * r * z) < EPS) res.pb(mp(x0, y0)); else {
		LD m = sqrt((r * r - c * c / z) / z);
		res.pb(mp(x0 + b * m, y0 - a * m));
		res.pb(mp(x0 - b * m, y0 + a * m));
	}
	return res;
}

PLL rec(UI mask1, UI mask2) {
	PLL res = mp(0, 0);
	UI mask = mask1 | mask2;
	if (mask + 1 == (1U << PIECES)) return res;
	if (DP[mask1].count(mask2)) return DP[mask1][mask2];
	LL x1 = 0, x2 = 0;
	for (UI i = 0; i < PIECES; i++) x1 += ((mask1 >> i) & 1) * $[i], x2 += ((mask2 >> i) & 1) * $[i];
	if (x2 < x1)
		for (UI i = 0; i < PIECES; i++) {
			if (!((mask >> i) & 1)) {
				auto cur = rec(mask1, mask2 | (1 << i));
				cur.S += $[i];
				if (cur.S >= res.S) res = cur;
			}
		}
	else
		for (UI i = 0; i < PIECES; i++) {
			if (!((mask >> i) & 1)) {
				auto cur = rec(mask1 | (1 << i), mask2);
				cur.F += $[i];
				if (cur.F >= res.F) res = cur;
			}
		}
	return DP[mask1][mask2] = res;
}

signed main() {
	O.precision(10);
	I >> N >> R;
	COEF = 100000. / R, SQCOEF = COEF * COEF, R = 100000., SQ = pi * R * R;
	while (I >> A >> B >> C) {
		C *= COEF;
		auto f = interc(R, A, B, C);
		assert(f.size() == 2);
		auto i0 = roundTo10(f[0]), i1 = roundTo10(f[1]);
		pts.pb(mp(polar(i0), i0));
		pts2polar[i0] = pts.back().F;
		pts.pb(mp(polar(i1), i1));
		pts2polar[i1] = pts.back().F;
		Z.pb(mp(i0, i1));
	}
	if (N == 1) {
		LD p0 = pts2polar[Z.back().F], p1 = pts2polar[Z.back().S];
		if (p0 > p1) p1 += 360.;
		LD arcLen = 2 * pi * R * (p1 - p0) / 360.,
			sss = .5 * R * R * (arcLen / R - sin(arcLen / R));
		$.pb(LL(max(SQ - sss, sss) * LLCOEF));
		$.pb(LL(min(SQ - sss, sss) * LLCOEF));
	}
	else {
		sort(pts.begin(), pts.end());
		pts.pb(pts[0]);
		for (UI i = 0; i < sz(pts) - 1; i++) Z.pb(mp(pts[i].S, pts[i + 1].S));
		$ = facetSqCalculator.calc(segmentHandler.handle(Z));
	}
	PIECES = sz($);
	auto portionsLL = rec(0, 0);
	auto portions = mp(portionsLL.F / LLCOEF, portionsLL.S / LLCOEF);
	assert(fabsl(portions.F + portions.S - SQ) < EPS);
	O << fixed << portions.F / SQCOEF << " " << portions.S / SQCOEF;
}