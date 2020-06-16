#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
using namespace std;
int n, p1, q1, p2, q2, p3, q3;

bool ins(int x, int y1, int y2, int x3, int x4, int y3, int y4) {
	if (x <= x4 &&x >= x3 && ((y1 <= y3 && y2 >= y3) || (y1 <= y4 && y2 >= y4))) {
		return true;
	}
	if (x == x3 || x == x4) {
		if (max(y1, y3) <= min(y2, y4)) {
			return true;
		}
	}
	return false;
}

int pos(int x) {
	if (x < 1) {
		return 1;
	}
	if (x > n) {
		return n;
	}
	return x;
}

int calc() {
	int sumstep = abs(p1 - p2);
	int maxstep = abs(p1 - p2) / 2 - 1;
	if (maxstep <= 0) {
		return -1;
	}
	int x1 = p2 == p1 ? 0 : (p2 - p1) / abs(p2 - p1);
	int xx, ymax, ymin;
	for (int i = 1; i <= maxstep; i++) {
		xx = p1 + x1 * i;
		ymin = max(pos(q1 - i), pos(q2 - sumstep + i));
		ymax = min(pos(q1 + i), pos(q2 + sumstep - i));
		if (ins(xx, ymin, ymax, p3 - i, p3 + i, q3 - i, q3 + i)) {
			return i;
		}
		xx = p2 - x1 * i;
		ymin = max(pos(q2 - i), pos(q1 - sumstep + i));
		ymax = min(pos(q2 + i), pos(q1 + sumstep - i));
		if (ins(xx, ymin, ymax, p3 - i, p3 + i, q3 - i, q3 + i)) {
			return i;
		}
	}
	return -1;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d%d%d%d%d%d", &n, &p1, &q1, &p2, &q2, &p3, &q3);
	if ((p1 == p3 && q1 == q3) || (p2 == p3 && q2 == q3)) {
		puts("YES\n0");
		return 0;
	}
	if (abs(p1 - p2) < abs(q1 - q2)) {
		swap(p1, q1);
		swap(p2, q2);
		swap(p3, q3);
	}
	int ans = calc();
	if (ans == -1) {
		printf("NO\n%d", abs(p1 - p2) - 1);
		return 0;
	}
	printf("YES\n%d", ans);
}