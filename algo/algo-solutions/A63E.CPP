#include <vector>
using namespace std;
#define LL long long
vector<LL> bit;
const int Z = 111111;
int n, m, t, x, y;
LL v;

inline int h(int i) {
	return i | (i + 1);
}

inline int f(int i) {
	return i & (i + 1);
}

inline void update(int pos, LL val) {
	while (pos <= Z) {
		bit[pos] += val;
		pos = h(pos);
	}
}

inline LL sum(int r) {
	LL res = 0LL;
	while (r > 0) {
		res += bit[r];
		r = f(r) - 1;
	}
	return res;
}

inline LL sum(int l, int r) {
	if (r < l) {
		return 0LL;
	}
	return sum(r) - sum(l - 1);
}

int main() {
	scanf_s("%d%d", &n, &m);
	bit.assign(Z, 0);
	for (int i = 1; i <= n; i++) {
		scanf_s("%d", &y);
		update(i, y);
	}
	for (int i = 0; i < m; i++) {
		scanf_s("%d", &t);
		if (t == 0) {
			scanf_s("%d%d", &x, &y);
			printf("%I64d\n", sum(x, y));
		}
		if (t == 1) {
			scanf_s("%d%I64d", &x, &v);
			LL xval = sum(x, x);
			update(x, v - xval);
		}
	}
}