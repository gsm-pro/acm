#include<iostream>
#include<algorithm>
using namespace std;
double a[11111];

int main() {
	int n;
	double k, x, y;
	cin >> n >> k;
	k /= 100.0;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	double l, h, m;
	l = 0;
	h = 1000000.0;
	for (int i = 0; i < 150; i++) {
		m = (l + h) / 2.0;
		x = y = 0;
		for (int i = 0; i < n; i++) {
			if (a[i] > m) {
				x += a[i] - m;
			}
			else {
				y += m - a[i];
			}
		}
		if ((x - x * k) > y) {
			l = m;
		}
		else {
			h = m;
		}
	}
	printf("%.9lf", m);
}