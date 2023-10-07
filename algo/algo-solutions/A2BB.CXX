#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("unroll-loops")
#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
#include<unordered_map>
#include<set>
using namespace std;
#define F first
#define S second
#define mp make_pair
#define pb push_back
typedef double LD;
typedef unsigned int UI;
#define sz(x) (UI)((x).size())
typedef pair<UI, UI> PUIUI;
typedef pair<PUIUI, PUIUI> PPUIUI;
typedef pair<LD, LD> PLD;
typedef pair<PLD, PLD> PPLD;
typedef pair<LD, UI> PLDUI;
typedef vector<bool> VB;
typedef vector<LD> VLD;
typedef vector<UI> VUI;
typedef vector<VUI> VVUI;
typedef vector<VB> VVB;
typedef vector<PUIUI> VPUIUI;
typedef vector<PPUIUI> VPPUIUI;
typedef vector<PLD> VPLD;
typedef vector<PPLD> VPPLD;
typedef vector<PLDUI> VPLDUI;
const LD EPS = 1e-8;

class SegmentHandler {
private:
	unordered_map<UI, unordered_map<UI, UI>> pointNumbers2egdeId;
	VPUIUI pointNumbersEdges;
	set<UI> c;
	VUI t, f;
	VVUI g;
	VB used;
	UI T = 0;

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

	bool eq(LD a, LD b) {
		return fabs(a - b) < EPS;
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

	void dfs(UI v, UI p = 999999) {
		used[v] = true;
		t[v] = f[v] = T++;
		for (auto to : g[v]) {
			if (to == p) continue;
			if (used[to]) f[v] = min(f[v], t[to]); else {
				dfs(to, v);
				f[v] = min(f[v], f[to]);
				if (f[to] > t[v]) c.insert(pointNumbers2egdeId[v][to]);
			}
		}
	}

public:
	VPPLD handle(VPPUIUI Z) {
		vector<Segment> SRC;
		VPLD all;
		for (auto& z : Z) {
			LD x1 = (LD)z.F.F, y1 = (LD)z.F.S, x2 = (LD)z.S.F, y2 = (LD)z.S.S;
			if (eq(x1, x2) && eq(y1, y2)) continue;
			PLD p1 = mp(x1, y1), p2 = mp(x2, y2);
			SRC.pb(Segment(p1, p2));
			all.pb(p1);
			all.pb(p2);
		}
		UI n = sz(SRC);
		for (UI i = 0; i < n; i++)
			for (UI j = 0; j < i; j++) {
				VPLD pts = inter(SRC[i], SRC[j]);
				if (sz(pts) > 0) all.pb(pts[0]);
				if (sz(pts) > 1) all.pb(pts[1]);
			}
		sort(all.begin(), all.end());
		UI ap = sz(all);
		VPLD PTS;
		PTS.pb(all[0]);
		for (UI i = 1; i < ap; i++)
			if (neq(all[i].F, all[i - 1].F) || neq(all[i].S, all[i - 1].S)) PTS.pb(all[i]);
		UI p = sz(PTS);
		for (UI i = 0; i < n; i++) {
			VUI pointNumbersOnLine;
			for (UI j = 0; j < p; j++)
				if (onSegment(PTS[j], SRC[i])) pointNumbersOnLine.push_back(j);
			for (UI j = 0; j < sz(pointNumbersOnLine) - 1; j++) {
				UI x = pointNumbersOnLine[j], y = pointNumbersOnLine[j + 1];
				if (!pointNumbers2egdeId[x].count(y) && !pointNumbers2egdeId[y].count(x)) {
					pointNumbers2egdeId[x][y] = pointNumbers2egdeId[y][x] = sz(pointNumbersEdges);
					pointNumbersEdges.pb(mp(x, y));
				}
			}
		}
		g.resize(p);
		for (auto& r : pointNumbersEdges) {
			g[r.F].pb(r.S);
			g[r.S].pb(r.F);
		}
		used.assign(p, false);
		t.resize(p);
		f.resize(p);
		for (UI i = 0; i < p; i++)
			if (!used[i]) dfs(i);
		VPPLD ans;
		for (auto& r : pointNumbersEdges)
			if (!c.count(pointNumbers2egdeId[r.F][r.S])) ans.pb(mp(PTS[r.F], PTS[r.S]));
		return ans;
	}
} segmentHandler;

class FacetSqCalculator {
private:
	struct Area {
		VUI cyc;
		LD square, fullsquare;
		UI comp;

		Area(VUI _cyc, LD _square, UI _comp) {
			cyc = _cyc;
			square = fullsquare = _square;
			comp = _comp;
		}

		bool operator < (const Area& a) const {
			return square < a.square;
		}

		static bool btw(LD x, LD y, LD x1, LD y1, LD x2, LD y2) {
			if (x1 > x2) swap(x1, x2);
			if (y1 > y2) swap(y1, y2);
			if (x1 <= x && x <= x2 && y1 <= y && y <= y2) return true;
			return false;
		}

		bool insideOf(Area& a, VPLD& PTS) {
			LD xx = PTS[cyc[0]].F, yy = PTS[cyc[0]].S, xa, ya, xb, yb;
			a.cyc.push_back(a.cyc[0]);
			UI cnt = 0;
			for (UI i = 0; i < sz(a.cyc) - 1; i++) {
				if ((xx - (xa = PTS[a.cyc[i]].F)) * ((yb = PTS[a.cyc[i + 1]].S) - (ya = PTS[a.cyc[i]].S)) -
					(yy - ya) * ((xb = PTS[a.cyc[i + 1]].F) - xa) == 0 && btw(xx, yy, xa, ya, xb, yb)) {
					a.cyc.pop_back();
					return true;
				}
				if ((ya - yy - EPS) * (yb - yy - EPS) <= 0) {
					if (ya != yb && xa + (yy + EPS - ya) * (xb - xa) / (yb - ya) > xx - EPS) cnt++;
					if (ya == yb && (xa - xx) * (xb - xx) <= 0) cnt++;
				}
			}
			a.cyc.pop_back();
			return cnt % 2 == 1;
		}
	};

	void paint(VVUI& g, VUI& COLOR, UI v, UI c) {
		COLOR[v] = c;
		for (auto to : g[v])
			if (COLOR[to] == -1) paint(g, COLOR, to, c);
	}

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

public:
	VLD calc(VPPLD Z) {
		UI m = sz(Z);
		VPLD a(m * 2);
		for (UI i = 0; i < m; i++)
			a[i * 2].F = Z[i].F.F, a[i * 2].S = Z[i].F.S,
			a[i * 2 + 1].F = Z[i].S.F, a[i * 2 + 1].S = Z[i].S.S;
		VPLD PTS(a);
		sort(PTS.begin(), PTS.end());
		PTS.erase(unique(PTS.begin(), PTS.end()), PTS.end());
		UI n = sz(PTS), color = 0;
		VVUI g(n);
		for (UI i = 0; i < m; i++) {
			UI id1 = UI(lower_bound(PTS.begin(), PTS.end(), a[i * 2]) - PTS.begin()),
				id2 = UI(lower_bound(PTS.begin(), PTS.end(), a[i * 2 + 1]) - PTS.begin());
			g[id1].pb(id2), g[id2].pb(id1);
		}
		for (UI i = 0; i < n; i++) {
			VPLDUI b(sz(g[i]));
			for (UI j = 0; j < sz(g[i]); j++) {
				UI to = g[i][j];
				b[j] = mp(atan2(.0 + PTS[to].S - PTS[i].S, .0 + PTS[to].F - PTS[i].F), to);
			}
			sort(b.begin(), b.end());
			b.erase(unique(b.begin(), b.end()), b.end());
			g[i].clear();
			for (UI j = 0; j < sz(b); j++) g[i].pb(b[j].S);
		}
		VUI COLOR(n, -1);
		for (UI i = 0; i < n; i++)
			if (COLOR[i] == -1) paint(g, COLOR, i, ++color);
		VVB used(n);
		for (UI i = 0; i < n; i++) used[i].resize(sz(g[i]));
		vector<Area> areas;
		for (UI i = 0; i < n; i++)
			for (UI j = 0; j < sz(g[i]); j++)
				if (!used[i][j]) {
					VUI cyc;
					dfs(g, used, cyc, g[i][j], i);
					LD s = sq(cyc, PTS);
					if (s > 0) areas.push_back(Area(cyc, s, COLOR[cyc[0]]));
				}
		sort(areas.begin(), areas.end());
		for (UI i = 0; i < sz(areas); i++)
			for (UI j = i + 1; j < sz(areas); j++)
				if (areas[i].comp != areas[j].comp && areas[i].insideOf(areas[j], PTS)) {
					areas[j].square -= areas[i].fullsquare;
					break;
				}
		VLD ans;
		for (auto& area : areas) ans.push_back(area.square);
		sort(ans.begin(), ans.end());
		return ans;
	}
} facetSqCalculator;

int main() {
	UI N;
	cin >> N;
	VPPUIUI Z(N);
	for (UI i = 0; i < N; i++) cin >> Z[i].F.F >> Z[i].F.S >> Z[i].S.F >> Z[i].S.S;
	auto $ = facetSqCalculator.calc(segmentHandler.handle(Z));
	cout << sz($) << endl;
	cout.precision(6);
	for (auto $$ : $) cout << fixed << $$ << endl;
}