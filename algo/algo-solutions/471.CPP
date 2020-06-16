#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#define LSOne(S) (S & (-S))
typedef long long ll;
using namespace std;
ll B1[3333333], B2[3333333];
int N;

ll query(ll* FT, int b) {
	ll sum = 0;
	for (; b; b -= LSOne(b)) sum += FT[b];
	return sum;
}

ll query(int b) {
	return query(B1, b) * b - query(B2, b);
}

ll range_query(int i, int j) {
	return query(j) - query(i - 1);
}

void update(ll* FT, int k, int v) {
	for (; k <= N; k += LSOne(k)) FT[k] += v;
}

void range_update(int i, int j, int v) {
	update(B1, i, v);
	update(B1, j + 1, -v);
	update(B2, i, v * (i - 1));
	update(B2, j + 1, -v * j);
}

int main() {
	int Q, l, r, val, type;
	scanf("%d %d", &N, &Q);
	memset(B1, 0, sizeof B1);
	memset(B2, 0, sizeof B2);
	while (Q--) {
		scanf("%d", &type);
		if (type == 1) {
			scanf("%d%d%d", &l, &r, &val);
			range_update(l, r, val);
		}
		if (type == 2) {
			scanf("%d%d", &l, &r);
			printf("%lld\n", range_query(l, r));
		}
	}
}