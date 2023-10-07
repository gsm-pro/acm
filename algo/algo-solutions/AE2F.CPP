#include<iostream>
using namespace std;
#define N 300003
const __int64 MOD = 1000000007LL;
int a[N], child[N], nxt[N], depth[N], c_in[N], c_out[N], cnt = 0, n, m;
__int64 sum1[N << 1], sum2[N << 1];

void dfs(int x) {
	c_in[x] = ++cnt;
	for (int i = child[x]; i; i = nxt[i]) {
		depth[i] = depth[x] + 1;
		dfs(i);
	}
	c_out[x] = ++cnt;
}

void U(__int64 *A, int x, __int64 y) {
	for (; x <= cnt; x += (x & -x)) {
		A[x] = (A[x] + y) % MOD;
	}
}

__int64 Q(__int64 *A, int x, int y) {
	__int64 ans = 0;
	for (; x; x -= (x & -x)) {
		ans = (ans + A[x] * y) % MOD;
	}
	return ans;
}

int main() {
	scanf_s("%d", &n);
	for (int i = 2; i <= n; ++i) {
		scanf_s("%d", &a[i]);
		nxt[i] = child[a[i]];
		child[a[i]] = i;
	}
	dfs(1);
	scanf_s("%d", &m);
	while (m--) {
		int type, v, x, k;
		scanf_s("%d%d", &type, &v);
		if (type == 1) {
			scanf_s("%d%d", &x, &k);
			U(sum1, c_in[v], x);
			U(sum1, c_out[v], -x);
			U(sum2, c_in[v], -k);
			U(sum2, c_out[v], k);
			U(sum1, c_in[v], (__int64)depth[v] * k);
			U(sum1, c_out[v], -(__int64)depth[v] * k);
		}
		if (type == 2) {
			printf("%I64d\n", (Q(sum1, c_in[v], 1) + Q(sum2, c_in[v], depth[v]) + (MOD << 3)) % MOD);
		}
	}
}