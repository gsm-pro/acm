#include<iostream>
#include<map>
#include<algorithm>
using namespace std;
#define NMAX 111111
#define BS 2500
#define NA -1000000000
int n, q, a[NMAX], pos, l, r, x;
map<int, int> SQD[NMAX / BS];

pair<int, bool> search_segm(int L, int R, int X) {
	bool found = false;
	int ans = NA;
	for (int num = L; num <= R; num++) {
		if (a[num] >= X) {
			found = true;
			if (ans == NA || abs(a[num] - X) < abs(ans - X)) {
				ans = a[num];
			}
		}
	}
	return make_pair(ans, found);
}

pair<int, bool> search_block(int B1, int B2, int X) {
	bool found = false;
	int ans = NA;
	for (int B = B1; B <= B2; B++) {
		map<int, int>::iterator it = SQD[B].lower_bound(X);
		if (it != SQD[B].end()) {
			int num = it->first;
			found = true;
			if (ans == NA || abs(num - X) < abs(ans - X)) {
				ans = num;
			}
		}
	}
	return make_pair(ans, found);
}

int getBlock(int pos) {
	return (pos / BS) + (pos % BS == 0 ? 0 : 1);
}

int main() {
	scanf_s("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) {
		scanf_s("%d", &a[i]);
		SQD[getBlock(i)][a[i]]++;
	}
	while (q--) {
		scanf_s("%d", &x);
		if (x == 1) {
			scanf_s("%d%d", &pos, &x);
			if (a[pos] != x) {
				int block = getBlock(pos), old = a[pos];
				SQD[block][old]--;
				if (SQD[block][old] == 0) {
					SQD[block].erase(old);
				}
				a[pos] = x;
				SQD[block][x]++;
			}
		}
		else {
			scanf_s("%d%d%d", &l, &r, &x);
			int block1 = getBlock(l), block2 = getBlock(r);
			if (block2 - block1 <= 1) {
				pair<int, bool> p = search_segm(l, r, x);
				if (!p.second) {
					puts("?");
				}
				else {
					printf("%d\n", p.first);
				}
			}
			else {
				pair<int, bool> p1 = search_segm(l, block1 * BS, x),
					p2 = search_segm((block2 - 1) * BS + 1, r, x),
					p3 = search_block(block1 + 1, block2 - 1, x);
				int ans = -NA;
				if (p1.second) {
					ans = min(ans, p1.first);
				}
				if (p2.second) {
					ans = min(ans, p2.first);
				}
				if (p3.second) {
					ans = min(ans, p3.first);
				}
				if (ans == -NA) {
					puts("?");
				}
				else {
					printf("%d\n", ans);
				}
			}
		}
	}
}