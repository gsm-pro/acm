#include<iostream>
using namespace std;
typedef long long int LL;
const int B = 21;
struct node
{
	int pres[30], upd;
	LL sum;
} st[555555];

int N, M, A[111111], L, R, X, T;

void build(int a, int b, int index) {
	if (a == b) {
		st[index].upd = 0;
		int temp = A[a];
		for (int i = 0; i < B; i++) {
			if ((1LL << i) & temp) {
				st[index].pres[i] = 1;
			}
		}
		st[index].sum = A[a];
	}
	else {
		build(a, (a + b) >> 1, index << 1);
		build(((a + b) >> 1) + 1, b, (index << 1) + 1);
		st[index].upd = 0;
		for (int i = 0; i < B; i++) {
			st[index].pres[i] = st[index << 1].pres[i] + st[(index << 1) + 1].pres[i];
		}
		st[index].sum = st[index << 1].sum + st[(index << 1) + 1].sum;
	}
}

void update(int a, int b, int l, int r, int index, int x) {
	if (a > r || b < l) {
		return;
	}
	if (l <= a && b <= r) {
		int num = b - a + 1;
		st[index].sum = 0;
		for (int i = 0; i < B; i++) {
			if ((1LL << i) & x) {
				st[index].pres[i] = num - st[index].pres[i];
			}
			st[index].sum += (1LL << i) * (st[index].pres[i]);
		}
		st[index].upd = st[index].upd ^ x;
	}
	else {
		if (st[index].upd > 0) {
			update(a, (a + b) >> 1, a, (a + b) >> 1, index << 1, st[index].upd);
			update(((a + b) >> 1) + 1, b, ((a + b) >> 1) + 1, b, (index << 1) + 1, st[index].upd);
			for (int i = 0; i < B; i++) {
				st[index].pres[i] = st[index << 1].pres[i] + st[(index << 1) + 1].pres[i];
			}
			st[index].sum = st[index << 1].sum + st[(index << 1) + 1].sum;
			st[index].upd = 0;
		}
		update(a, (a + b) >> 1, l, r, index << 1, x);
		update(((a + b) >> 1) + 1, b, l, r, (index << 1) + 1, x);
		for (int i = 0; i < B; i++) {
			st[index].pres[i] = st[index << 1].pres[i] + st[(index << 1) + 1].pres[i];
		}
		st[index].sum = st[index << 1].sum + st[(index << 1) + 1].sum;
	}
}

LL query(int a, int b, int l, int r, int index) {
	if (a > r || b < l) {
		return 0LL;
	}
	if (l <= a && b <= r) {
		return st[index].sum;
	}
	else {
		if (st[index].upd > 0) {
			update(a, (a + b) >> 1, a, (a + b) >> 1, index << 1, st[index].upd);
			update(((a + b) >> 1) + 1, b, ((a + b) >> 1) + 1, b, (index << 1) + 1, st[index].upd);
			for (int i = 0; i < B; i++) {
				st[index].pres[i] = st[index << 1].pres[i] + st[(index << 1) + 1].pres[i];
			}
			st[index].sum = st[index << 1].sum + st[(index << 1) + 1].sum;
			st[index].upd = 0;
		}
		return query(a, (a + b) >> 1, l, r, index << 1) + query(((a + b) >> 1) + 1, b, l, r, (index << 1) + 1);
	}
}

int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> A[i];
	}
	build(1, N, 1);
	cin >> M;
	while (M--) {
		cin >> T >> L >> R;
		if (T == 1) {
			LL ans = query(1, N, L, R, 1);
			cout << ans << endl;
		}
		else {
			cin >> X;
			update(1, N, L, R, 1, X);
		}
	}
}