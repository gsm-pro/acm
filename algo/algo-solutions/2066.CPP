#define _CRT_SECURE_NO_DEPRECATE
#include<cstdio>
#include<cstring>
#define MAXN 9999
#define MAXM 999999
using namespace std;
int n, m, a, b, c, num, flag, head[MAXN], scc[MAXN], vis[MAXN], st1[MAXN], st2[MAXN];
struct edge
{
	int v, next;
}g[MAXM];

void init() {
	memset(head, 0, sizeof head);
	memset(vis, 0, sizeof vis);
	memset(scc, 0, sizeof scc);
	st1[0] = st2[0] = num = 0;
	flag = 1;
}

void addEdge(int u, int v) {
	num++;
	g[num].v = v;
	g[num].next = head[u];
	head[u] = num;
}

void dfs(int cur, int &sig, int &cnt) {
	if (!flag) {
		return;
	}
	vis[cur] = ++sig;
	st1[++st1[0]] = cur;
	st2[++st2[0]] = cur;
	for (int i = head[cur]; i; i = g[i].next) {
		if (!vis[g[i].v]) {
			dfs(g[i].v, sig, cnt);
		}
		else {
			if (!scc[g[i].v]) {
				while (vis[st2[st2[0]]] > vis[g[i].v]) {
					st2[0] --;
				}
			}
		}
	}
	if (st2[st2[0]] == cur) {
		st2[0] --;
		++cnt;
		do {
			scc[st1[st1[0]]] = cnt;
			int tmp = st1[st1[0]];
			if ((tmp >= n && scc[tmp - n] == cnt) || (tmp < n && scc[tmp + n] == cnt)) {
				flag = 0;
				return;
			}
		} while (st1[st1[0] --] != cur);
	}
}

void twoSat() {
	int sig = 0, cnt = 0;
	for (int i = 0; (i < n + n) && flag; i++) {
		if (!vis[i]) {
			dfs(i, sig, cnt);
		}
	}
}

int main() {
	char s[10];
	scanf("%d%d", &n, &m);
	init();
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d%s", &a, &b, &c, s);
		if (s[0] == 'A') {
			if (c) {
				addEdge(a, a + n);
				addEdge(b, b + n);
			}
			else {
				addEdge(a + n, b);
				addEdge(b + n, a);
			}
		}
		if (s[0] == 'O') {
			if (c) {
				addEdge(a, b + n);
				addEdge(b, a + n);
			}
			else {
				addEdge(a + n, a);
				addEdge(b + n, b);
			}
		}
		if (s[0] == 'X') {
			if (c) {
				addEdge(a, b + n);
				addEdge(b + n, a);
				addEdge(b, a + n);
				addEdge(a + n, b);
			}
			else {
				addEdge(a, b);
				addEdge(b, a);
				addEdge(a + n, b + n);
				addEdge(b + n, a + n);
			}
		}
	}
	twoSat();
	puts(flag ? "YES" : "NO");
}