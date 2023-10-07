#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#define forn(i,x) for(i=0;i<x;i++)
#define clr(x,y) memset(x,y,sizeof(x))

struct Node {
	int v, next;
};

const int N = 21;
Node edges[N * N * 2];
int head[N * N], e, g[N][N], a[N][N], d[N * N], visit[N * N], color[N * N], p[N * N], n;
char link[N * N][N * N];

int encode(int i, int j) {
	return i * n + j;
}

int get(int t) {
	return g[t / n][t % n];
}

int ok(int x) {
	return x >= 0 && x < n;
}

void init(int x, int y) {
	clr(a, -1);
	int i, j;
	forn(i, n) forn(j, n) {
		if (ok(i + x) && ok(j + y)) {
			a[i + x][j + y] = encode(i, j);
		}
	}
}

void rotate(int a[][N]) {
	int i, j, b[N][N];
	forn(i, n) forn(j, n) {
		b[i][j] = a[i][j];
	}
	forn(i, n) forn(j, n) {
		a[i][j] = b[n - 1 - j][i];
	}
}


void add(int u, int v) {
	edges[e].v = v;
	edges[e].next = head[u];
	head[u] = e++;
	edges[e].v = u;
	edges[e].next = head[v];
	head[v] = e++;
	link[u][v] = 1;
	link[v][u] = 2;
	d[u]++; d[v]++;
}

void match() {
	int i, j;
	for (i = 1; i <= p[0]; i++) {
		j = i + 1;
		if (j > p[0]) {
			j = 1;
		}
		if (link[p[i]][p[j]] == 1) {
			break;
		}
	}
	color[p[i]] = 1;
	for (j = i + 1; j <= p[0]; j++) {
		color[p[j]] = color[p[j - 1]] ^ 1;
	}
	for (j = i - 1; j >= 1; j--) {
		color[p[j]] = color[p[j + 1]] ^ 1;
	}
}

int dfs(int u, int pre) {
	p[++p[0]] = u;
	visit[u] = 1;
	int i, v;
	for (i = head[u]; i != -1; i = edges[i].next) {
		v = edges[i].v;
		if (v == pre || visit[v]) {
			continue;
		}
		return dfs(v, u);
	}
	if (p[0] & 1) {
		return 0;
	}
	match();
	return 1;
}

int ok(int a[][N]) {
	clr(head, -1);
	clr(color, 0);
	clr(visit, 0);
	clr(d, 0);
	e = 0;
	int i, j;
	forn(i, n) forn(j, n) {
		if (a[i][j] != -1 && g[i][j] && get(a[i][j])) {
			add(a[i][j], encode(i, j));
		}
	}
	int sum = 0, x;
	forn(i, n) forn(j, n) {
		if (g[i][j]) {
			sum++;
			x = encode(i, j);
			if (visit[x]) {
				continue;
			}
			if (!d[x]) {
				return 0;
			}
			p[0] = 0;
			if (!dfs(x, 0)) {
				return 0;
			}
		}
	}
	int cnt = 0;
	forn(i, n) forn(j, n) {
		cnt += color[encode(i, j)];
	}
	return cnt * 2 == sum;
}

void print() {
	puts("YES");
	int i, j;
	forn(i, n) {
		forn(j, n) {
			printf("%d", color[encode(i, j)]);
		}
		puts("");
	}
}

int main() {
	int i, j, k;
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
	scanf("%d", &n);
	forn(i, n) forn(j, n) {
		scanf("%1d", &g[i][j]);
	}
	for (i = -n; i <= n; i++) {
		for (j = -n; j <= n; j++) {
			init(i, j);
			forn(k, 4) {
				if (ok(a)) {
					return print(), 0;
				}
				rotate(a);
			}
		}
	}
	puts("NO");
}