#include<iostream>
#include<cmath>
#include<vector>
#include<ctime>
using namespace std;
#define LD long double
const LD eps = 1e-8;
int N;

struct Point {
	LD x, y;
	Point() {};
	Point(LD _x, LD _y) { x = _x; y = _y; }
};

struct Circle {
	Point c;
	LD r;
	Circle() {};
	Circle(Point _c, LD _r) { c = _c; r = _r; }
};

bool eq(LD x, LD y) {
	return (fabs(x - y) < eps);
}

LD hyp(LD a, LD b) {
	return sqrt(a * a + b * b);
}

LD dist(Point& p1, Point& p2) {
	return hyp(p1.x - p2.x, p1.y - p2.y);
}

bool getCircle(Point p1, Point p2, Point p3, Circle& c) {
	if (eq(p2.x, p1.x)) {
		swap(p1, p3);
	}
	c.c.y = ((p3.x - p2.x) * (p2.x * p2.x - p1.x * p1.x + p2.y * p2.y - p1.y * p1.y) -
		(p2.x - p1.x) * (p3.x * p3.x - p2.x * p2.x + p3.y * p3.y - p2.y * p2.y)) / (2 *
			((p3.x - p2.x) * (p2.y - p1.y) - (p2.x - p1.x) * (p3.y - p2.y)));
	c.c.x = (p2.x * p2.x - p1.x * p1.x + p2.y * p2.y - p1.y * p1.y - 2 * c.c.y * (p2.y - p1.y)) / (2 * (p2.x - p1.x));
	c.r = dist(c.c, p1);
	return isfinite(c.c.x) && isfinite(c.c.y);
}

bool onCircle(Point p, Circle c) {
	return eq(hyp(p.x - c.c.x, p.y - c.c.y), c.r);
}

int getRandom(int f1, int f2) {
	for (;;) {
		int r = rand() % N;
		if (r != f1 && r != f2) {
			return r;
		}
	}
}

void out(vector<int> ans1, vector<int> ans2) {
	for (size_t i = 0; i < ans1.size(); i++) {
		cout << ans1[i] + 1 << " ";
	}
	cout << endl;
	for (size_t i = 0; i < ans2.size(); i++) {
		cout << ans2[i] + 1 << " ";
	}
	exit(0);
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	srand(time(NULL));
	LD x, y;
	cin >> N;
	vector<Point> points;
	for (int i = 0; i < N; i++) {
		cin >> x >> y;
		points.push_back(Point(x, y));
	}
	if (N == 2) {
		out({ 0 }, { 1 });
	}
	if (N == 3) {
		out({ 0, 1 }, { 2 });
	}
	if (N == 4) {
		out({ 0, 1 }, { 2, 3 });
	}
onemore:
	Circle c;
	int i1 = getRandom(-1, -1), i2 = getRandom(i1, -1), i3 = getRandom(i1, i2);
	if (!getCircle(points[i1], points[i2], points[i3], c)) {
		goto onemore;
	}
	vector<int> ans1, ans2;
	for (int i = 0; i < N; i++) {
		if (onCircle(points[i], c)) {
			ans1.push_back(i);
		}
		else {
			ans2.push_back(i);
		}
	}
	if (ans2.size() == 0) {
		ans2.push_back(ans1.back());
	}
	if (ans2.size() == 1 || ans2.size() == 2) {
		out(ans1, ans2);
	}
	if (!getCircle(points[ans2[0]], points[ans2[1]], points[ans2[2]], c)) {
		goto onemore;
	}
	for (size_t i = 0; i < ans2.size(); i++) {
		if (!onCircle(points[ans2[i]], c)) {
			goto onemore;
		}
	}
	for (size_t i = 0; i < ans1.size(); i++) {
		if (onCircle(points[ans1[i]], c)) {
			ans2.push_back(ans1[i]);
		}
	}
	out(ans1, ans2);
}