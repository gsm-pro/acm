#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#define LSOne(S) (S & (-S))
using namespace std;
int FT[1111111];
int N;

int query(int b) {
	int sum = 0;
	for (; b; b -= LSOne(b)) sum += FT[b];
	return sum;
}

void update(int k, int v) {
	for (; k <= N; k += LSOne(k)) FT[k] += v;
}

void range_update(int i, int j, int v) {
	update(i, v);
	update(j + 1, -v);
}

int main() {
	int Q, l, r, val, type;
	scanf("%d %d", &N, &Q);
	memset(FT, 0, sizeof FT);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &val);
		range_update(i, i, val);
	}
	while (Q--) {
		scanf("%d", &type);
		if (type == 1) {
			scanf("%d%d%d", &l, &r, &val);
			range_update(l, r, val);
		}
		if (type == 2) {
			scanf("%d", &val);
			printf("%d\n", query(val));
		}
	}
}