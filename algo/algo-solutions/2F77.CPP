#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
#define LD long double
#define X first
#define Y second
#define POINT pair<LD, LD>
#define forn(i,n) for(int i=0;i<(n);i++)
#define forv(i,v) for(int i=0;i<(int)(v).size();i++)
#define all(v) (v).begin(),(v).end()
const LD PI = acos(LD(-1.0));
const LD EPS = 1e-10;
LD R;
POINT XG, XR, X1, Y1, X2, Y2;

int sgn(LD value) {
	if (value < -EPS) return -1;
	if (value > EPS) return 1;
	return 0;
}

LD ABS(LD x) {
	return x < 0 ? -x : x;
}

POINT mult(LD ca, POINT A, LD cb, POINT B) {
	return make_pair(ca * A.X + cb * B.X, ca * A.Y + cb * B.Y);
}

LD prod(POINT A, POINT B) {
	return A.X * B.Y - A.Y * B.X;
}

int crossLineLine(POINT X1, POINT Y1, POINT X2, POINT Y2, vector<POINT> &res) {
	LD A1 = Y1.Y - X1.Y, B1 = X1.X - Y1.X, C1 = -A1 * X1.X - B1 * X1.Y;
	LD A2 = Y2.Y - X2.Y, B2 = X2.X - Y2.X, C2 = -A2 * X2.X - B2 * X2.Y;
	LD D = A1 * B2 - B1 * A2;
	if (ABS(D) > EPS) {
		POINT c;
		c.X = -(C1 * B2 - B1 * C2) / D;
		c.Y = -(A1 * C2 - C1 * A2) / D;
		res.push_back(c);
		return 1;
	}
	return 0;
}

int crossLineCircle(LD R, POINT A, POINT B, vector<POINT> &res) {
	LD x1 = A.X, y1 = A.Y, x2 = B.X, y2 = B.Y;
	LD dx = x2 - x1, dy = y2 - y1;
	LD AA = dx * dx + dy * dy;
	LD BB = 2 * dx * x1 + 2 * dy * y1;
	LD CC = -R * R + x1 * x1 + y1 * y1;
	LD D = BB * BB - 4 * AA * CC;
	if (D < EPS) {
		return 0;
	}
	else {
		LD t1 = (-BB - sqrt(D)) / 2 / AA;
		LD t2 = (-BB + sqrt(D)) / 2 / AA;
		POINT c1 = make_pair(x1 + dx * t1, y1 + t1 * dy);
		POINT c2 = make_pair(x1 + dx * t2, y1 + t2 * dy);
		if (ABS(t1 - t2) > EPS) {
			res.push_back(c1);
			res.push_back(c2);
			return 2;
		}
		else {
			res.push_back(c1);
			return 1;
		}
	}
}

bool good(POINT P) {
	if (P.X * P.X + P.Y * P.Y > R * R + EPS) {
		return false;
	}
	int ca = sgn(prod(mult(1, Y1, -1, X1), mult(1, P, -1, X1))) * sgn(prod(mult(1, Y1, -1, X1), mult(1, XG, -1, X1)));
	int cb = sgn(prod(mult(1, Y2, -1, X2), mult(1, P, -1, X2))) * sgn(prod(mult(1, Y2, -1, X2), mult(1, XR, -1, X2)));
	return ca >= 0 && cb >= 0;
}

LD dist(POINT A, POINT B) {
	return sqrt((A.X - B.X) * (A.X - B.X) + (A.Y - B.Y) * (A.Y - B.Y));
}

bool onLine(POINT M, POINT A, POINT B) {
	LD ca = prod(mult(1, B, -1, A), mult(1, M, -1, A));
	return ABS(ca) < EPS;
}

LD getAreaUnderSegment(POINT A, POINT B) {
	return (B.X - A.X) * (A.Y + B.Y) / 2.0;
}

LD getAreaUnderArc(POINT A, POINT B) {
	LD al = atan2(B.Y, B.X) - atan2(A.Y, A.X);
	while (al < 0) {
		al += 2 * PI;
	}
	while (al > 2 * PI) {
		al -= 2 * PI;
	}
	LD step = al / 1000;
	LD stAl = atan2(A.Y, A.X);
	LD finAl = atan2(B.Y, B.X);
	POINT cur(R * cos(stAl + step), R * sin(stAl + step));
	bool f = false;
	if (!good(cur)) {
		cur = make_pair(R * cos(stAl - step), R * sin(stAl - step));
		if (!good(cur)) {
			return getAreaUnderSegment(A, B);
		}
		f = true;
		swap(stAl, finAl);
	}
	al = stAl - finAl;
	while (al < 0) {
		al += 2 * PI;
	}
	while (al > 2 * PI) {
		al -= 2 * PI;
	}
	LD res = al / 2.0 + (sin(2 * finAl) - sin(2 * stAl)) / 4.0;
	return (f ? PI - res : res - PI) * R * R;
}

LD getAreaUnder(POINT A, POINT B, bool arc = false) {
	if (((onLine(A, X1, Y1) && onLine(B, X1, Y1)) ||
		(onLine(A, X2, Y2) && onLine(B, X2, Y2))) && !arc) {
		return getAreaUnderSegment(A, B);
	}
	else {
		return getAreaUnderArc(A, B);
	}
}

int main() {
	while (cin >> R) {
		cin >> XG.X >> XG.Y >> XR.X >> XR.Y >> X1.X >> X1.Y >> Y1.X >> Y1.Y >> X2.X >> X2.Y >> Y2.X >> Y2.Y;
		if (R > 1000) {
			R /= 100.0;
			XG.X /= 100.0, XG.Y /= 100.0, XR.X /= 100.0, XR.Y /= 100.0;
			X1.X /= 100.0, X1.Y /= 100.0, Y1.X /= 100.0, Y1.Y /= 100.0;
			X2.X /= 100.0, X2.Y /= 100.0, Y2.X /= 100.0, Y2.Y /= 100.0;
		}
		vector<POINT> cross, p;
		crossLineCircle(R, X1, Y1, cross);
		crossLineCircle(R, X2, Y2, cross);
		crossLineLine(X1, Y1, X2, Y2, cross);
		sort(all(cross));
		POINT sum;
		forv(i, cross) {
			if (good(cross[i])) {
				if (i == 0 || (i > 0 && dist(cross[i - 1], cross[i]) > EPS)) {
					sum = mult(1, sum, 1, cross[i]);
					p.push_back(cross[i]);
				}
			}
		}
		if (p.size() > 0) {
			sum.X /= p.size();
			sum.Y /= p.size();
		}
		vector<pair<LD, POINT>> alpha2point;
		if (p.size() > 1) {
			forv(i, p) {
				LD alpha = atan2(p[i].Y - sum.Y, p[i].X - sum.X);
				alpha2point.push_back(make_pair(alpha, p[i]));
			}
		}
		sort(all(alpha2point));
		forv(i, alpha2point) {
			p[i] = alpha2point[i].second;
		}
		int n = p.size();
		if (n > 0) {
			p.push_back(p[0]);
		}
		LD area = 0;
		if (n > 2) {
			forn(i, n) {
				area += getAreaUnder(p[i + 1], p[i]);
			}
		}
		else {
			if (n == 2) {
				area = max(ABS(getAreaUnder(p[0], p[1]) + getAreaUnder(p[1], p[0], true)),
					ABS(getAreaUnder(p[0], p[1], true) + getAreaUnder(p[1], p[0])));
			}
			else {
				if (good(make_pair(0, 0))) {
					area = PI * R * R;
				}
			}
		}
		LD ans = ABS(area) / PI / R / R;
		printf("%.12lf\n", ans);
	}
}