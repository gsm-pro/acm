#include<iostream>
#include<cmath>
#include<algorithm>
#define INF 1e10
#define EPS 1e-12
#define NMAX 55
#define REFL_MAX 11
using namespace std;

struct Sphere {
	double x, y, z, r;
} g[NMAX];

int h[NMAX], tmpos, n;
double times[NMAX], xx, zz, xxx, zzz, yy, yyy;

int cmp(double x) {
	if (x > -EPS && x < EPS) {
		return 0;
	}
	if (x > 0) {
		return 1;
	}
	return -1;
}

void get(int x) {
	if (x == tmpos) {
		h[x] = 0;
		return;
	}
	double xc = g[x].x, yc = g[x].y, zc = g[x].z, 
		a = xxx * xxx + yyy * yyy + zzz * zzz, 
		b = 2 * (xx * xxx + yy * yyy + zz * zzz - xxx * xc - yyy * yc - zzz * zc), 
		c = pow(xx - xc, 2) + pow(yy - yc, 2) + pow(zz - zc, 2) - pow(g[x].r, 2);
	int dbl = cmp(pow(b, 2) - 4 * a * c);
	if (dbl == -1) {
		h[x] = 0;
		return;
	}
	if (dbl == 0) {
		h[x] = 1;
		times[x] = -b / (2 * a);
		if (times[x] < 0) {
			h[x] = 0;
		}
		return;
	}
	h[x] = 1;
	times[x] = (-b - sqrt(pow(b, 2) - 4 * a * c)) / 2 / a;
	if (times[x] < 0) {
		h[x] = 0;
	}
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> g[i].x >> g[i].y >> g[i].z >> g[i].r;
	}
	cin >> xx >> yy >> zz >> xxx >> yyy >> zzz;
	xxx -= xx, yyy -= yy, zzz -= zz;
	for (int t = 1; t <= REFL_MAX; t++) {
		int pos = 0;
		double tmp = -1, minDist = INF;
		for (int i = 1; i <= n; i++) {
			get(i);
		}
		for (int i = 1; i <= n; i++) {
			if (h[i]) {
				if (times[i] < minDist || pos == 0) {
					minDist = times[i];
					pos = i;
				}
			}
		}
		if (pos == 0) {
			break;
		}
		tmpos = pos;
		if (t == 1) {
			cout << pos;
		}
		else {
			if (t == REFL_MAX) {
				cout << " etc.";
			}
			else {
				cout << " " << pos;
			}
		}
		xx += minDist * xxx, yy += minDist * yyy, zz += minDist * zzz;
		double vx = xx - g[pos].x, vy = yy - g[pos].y, vz = zz - g[pos].z, tt;
		xxx = -xxx, yyy = -yyy, zzz = -zzz;
		double alpha = vx * vx + vy * vy + vz * vz, beta = -2 * (xxx * vx + yyy * vy + zzz * vz);
		if (alpha == 0) {
			tt = 0;
		}
		else {
			tt = -beta / alpha;
		}
		xxx = vx * tt - xxx, yyy = vy * tt - yyy, zzz = vz * tt - zzz;
	}
}