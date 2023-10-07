#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;

const int MAXN = 111;
const double EPS = 1e-10;
const double INF = 1e20;
const double PI = acos((double)(-1.0));

int sgn(double a) {
	return fabs(a) < EPS ? 0 : (a < 0 ? -1 : 1);
}

struct Point {
	double x, y;
	void read() {
		cin >> x >> y;
	}
	Point(double x = 0, double y = 0) : x(x), y(y) {}
	bool operator < (const Point& b) const {
		return sgn(x - b.x) == -1 || (sgn(x - b.x) == 0 && sgn(y - b.y) == -1);
	}
	bool operator == (const Point& b) const {
		return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
	}
};

typedef Point Vector;
typedef vector<Point> Polygon;

Vector operator + (Vector a, Vector b) {
	return Vector(a.x + b.x, a.y + b.y);
}
Vector operator - (Vector a, Vector b) {
	return Vector(a.x - b.x, a.y - b.y);
}
Vector operator * (Vector a, double b) {
	return Vector(a.x * b, a.y * b);
}
Vector operator / (Vector a, double b) {
	return Vector(a.x / b, a.y / b);
}
Vector Rotate(Vector a, double rad) {
	return Vector(a.x * cos(rad) - a.y * sin(rad), a.x * sin(rad) + a.y * cos(rad));
}
double Dot(Vector a, Vector b) {
	return a.x * b.x + a.y * b.y;
}
double Cross(Vector a, Vector b) {
	return a.x * b.y - a.y * b.x;
}
double Length(Vector a) {
	return sqrt(Dot(a, a));
}
double Angle(Vector a) {
	return atan2(a.y, a.x);
}
double Angle(Vector a, Vector b) {
	return atan2(Cross(a, b), Dot(a, b));
}
double TurnAngle(Vector a, Vector b) {
	return sgn(Dot(a, b)) == 1 ? Angle(a, b) : PI + Angle(a, b);
}

Point ch[MAXN];

int convexHull(Polygon& p) {
	sort(p.begin(), p.end());
	p.erase(unique(p.begin(), p.end()), p.end());
	int n = p.size();
	int m = 0;
	for (int i = 0; i < n; i++) {
		while (m > 1 && sgn(Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2])) < 0) m--;
		ch[m++] = p[i];
	}
	int k = m;
	for (int i = n - 2; i >= 0; i--) {
		while (m > k && sgn(Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2])) < 0) m--;
		ch[m++] = p[i];
	}
	if (n > 1) m--;
	return m;
}

double distanceOfPointsAndLine(Point a, Point b, Point c) {
	return fabs(Cross(b - a, c - a) / Length(b - c));
}

double Area(int a, int b, int c, int d, Vector ab, Vector cd) {
	double h1 = distanceOfPointsAndLine(ch[a], ch[b], ch[b] + ab);
	double h2 = distanceOfPointsAndLine(ch[c], ch[d], ch[d] + cd);
	return h1 * h2;
}

int main() {
	int n, casenum = 0;
	while (cin >> n && n) {
		Point curr;
		Polygon poly;
		for (int i = 0; i < n; i++)	{
			curr.read();
			poly.push_back(curr);
		}
		int m = convexHull(poly);
		ch[m] = ch[0];
		double MinSquare = INF, MaxSquare = -INF;
		double Minx = ch[0].x, Miny = ch[0].y, Maxx = ch[0].x, Maxy = ch[0].y;
		int p1 = 0, p2 = 0, p3 = 0, p4 = 0;
		Vector v1, v2, s;
		s = v1 = Vector(1, 0);
		v2 = Vector(0, 1);
		for (int i = 1; i < m; i++) {
			if (sgn(Minx - ch[i].x) == 1) Minx = ch[i].x, p3 = i;
			if (sgn(Maxx - ch[i].x) == -1) Maxx = ch[i].x, p4 = i;
			if (sgn(Miny - ch[i].y) == 1) Miny = ch[i].y, p1 = i;
			if (sgn(Maxy - ch[i].y) == -1) Maxy = ch[i].y, p2 = i;
		}
		while (sgn(Cross(s, v1)) >= 0) {
			double minRad = INF;
			minRad = min(minRad, TurnAngle(v1, ch[p1 + 1] - ch[p1]));
			minRad = min(minRad, TurnAngle(v1 * (-1), ch[p2 + 1] - ch[p2]));
			minRad = min(minRad, TurnAngle(v2 * (-1), ch[p3 + 1] - ch[p3]));
			minRad = min(minRad, TurnAngle(v2, ch[p4 + 1] - ch[p4]));
			double l = 0, r = minRad;
			MinSquare = min(MinSquare, Area(p1, p2, p3, p4, Rotate(v1, l), Rotate(v2, l)));
			while (sgn(l - r)) {
				double len = (r - l) / 3;
				double midl = l + len;
				double midr = r - len;
				if (sgn(Area(p1, p2, p3, p4, Rotate(v1, midl), Rotate(v2, midl)) -
					    Area(p1, p2, p3, p4, Rotate(v1, midr), Rotate(v2, midr))) == 1) {
					r = midr;
				}
				else {
					l = midl;
				}
			}
			MaxSquare = max(MaxSquare, Area(p1, p2, p3, p4, Rotate(v1, l), Rotate(v2, l)));
			v1 = Rotate(v1, minRad);
			v2 = Rotate(v2, minRad);
			if (sgn(Angle(v1, ch[p1 + 1] - ch[p1])) == 0) p1 = (p1 + 1) % m;
			if (sgn(Angle(v1 * (-1), ch[p2 + 1] - ch[p2])) == 0) p2 = (p2 + 1) % m;
			if (sgn(Angle(v2 * (-1), ch[p3 + 1] - ch[p3])) == 0) p3 = (p3 + 1) % m;
			if (sgn(Angle(v2, ch[p4 + 1] - ch[p4])) == 0) p4 = (p4 + 1) % m;
		}
		printf("Gift %d\nMinimum area = %.3lf\nMaximum area = %.3lf\n\n", ++casenum, MinSquare, MaxSquare);
	}
}