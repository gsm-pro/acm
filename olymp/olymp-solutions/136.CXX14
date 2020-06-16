#include<bits/stdc++.h>
using namespace std;
vector<int> vt[20022];
int n, m, x, y, sel[20022], st[20022], top;

int dfs(int x) {
	if (sel[x ^ 1]) {
		return 0;
	}
	if (sel[x]) {
		return 1;
	}
	sel[x] = 1;
	st[top++] = x;
	for (size_t i = 0; i < vt[x].size(); i++) {
		if (!dfs(vt[x][i])) {
			return 0;
		}
	}
	return 1;
}

int solve() {
	for (int i = 0; i < 2 * n; i += 2) {
		if (!sel[i] && !sel[i + 1]) {
			top = 0;
			if (!dfs(i)) {
				while (top) {
					sel[st[--top]] = 0;
				}
				if (!dfs(i + 1)) {
					return 0;
				}
			}
		}
	}
	return 1;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &x, &y);
		--x, --y;
		vt[x].push_back(y ^ 1);
		vt[y].push_back(x ^ 1);
	}
	if (!solve()) {
		return puts("NO"), 0;
	}
	for (int i = 0; i < 2 * n; i++) {
		if (sel[i]) {
			printf("%d\n", i + 1);
		}
	}
}