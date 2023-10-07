#include <vector>
using namespace std;
vector<int> bit;
const int Z = 1048500;
unsigned int n, ans = 0;

inline int h(int i) {
	return i | (i + 1);
}

inline int f(int i) {
	return i & (i + 1);
}

inline void update(int pos, int val) {
	while (pos <= Z) {
		bit[pos] += val;
		pos = h(pos);
	}
}

inline int sum(int r) {
	int res = 0;
	while (r > 0) {
		res += bit[r];
		r = f(r) - 1;
	}
	return res;
}

inline int sum(int l, int r) {
	return sum(r) - sum(l - 1);
}

int main() {
	scanf_s("%d", &n);
	vector<int> p(n), l(n);
	bit.assign(Z + 2, 0);
	for (int i = 0; i < n; i++) {
		scanf_s("%d", &p[i]);
	}
	for (int i = 0; i < n; i++) {
		p[i]++;
		update(p[i], 1);
		ans += sum(p[i] + 1, Z);
	}
	printf("%d", ans);
}