#include<iostream>
using namespace std;
#define N 200002
int n, m, cnt = 0, child[N], nxt[N << 1], e[N << 1], flag[N], c_in[N], c_out[N], a[N];
__int64 sum[N << 2];

void dfs(int x) {
	c_in[x] = ++cnt;
	for (int i = child[x]; i; i = nxt[i]) {
		if (!flag[e[i]]) {
			flag[e[i]] = -flag[x];
			dfs(e[i]);
		}
	}
	c_out[x] = ++cnt;
}

int main() {
	scanf_s("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf_s("%d", &a[i]);
	}
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf_s("%d%d", &u, &v);
		nxt[++cnt] = child[u];
		child[u] = cnt;
		e[cnt] = v;
		nxt[++cnt] = child[v];
		child[v] = cnt;
		e[cnt] = u;
	}
	cnt = 0;
	flag[1] = 1;
	dfs(1);
	while (m--) {
		int u, v, type;
		scanf_s("%d%d", &type, &u);
		if (type == 1) {
			scanf_s("%d", &v);
			for (int i = c_in[u]; i <= cnt; i += (i & -i)) {
				sum[i] += flag[u] * v;
			}
			for (int i = c_out[u]; i <= cnt; i += (i & -i)) {
				sum[i] -= flag[u] * v;
			}
		}
		if (type == 2) {
			__int64 ans = 0;
			for (int i = c_in[u]; i >= 1; i -= (i & -i)) {
				ans += flag[u] * sum[i];
			}
			printf("%I64d\n", a[u] + ans);
		}
	}
}