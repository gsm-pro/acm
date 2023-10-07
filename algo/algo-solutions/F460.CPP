#include<algorithm>
#define ITER(i,s,e) for (int i=(s); i<=(e); i++)
#define QN(i,l) for (int i=(l); i; i=qn[i])
#define N 444444
using namespace std;

struct Solution511 {
	int t, ed, v[N], qd[N], qn[N], l[N], h[N], f[N], d_up[N], d_down[N], T[N][20];
	bool YES;

	void add(int x, int y) {
		qd[++ed] = y, qn[ed] = l[x], l[x] = ed;
	}

	inline int minh(int x, int y) {
		return h[x] < h[y] ? x : y;
	}

	void dfs(int x, int y) {
		h[x] = y;
		v[++t] = x;
		f[x] = t;
		for (int i = l[x]; i; i = qn[i]) if (!f[qd[i]]) {
			dfs(qd[i], y + 1);
			v[++t] = x;
		}
	}

	void init() {
		for (int i = 1; i <= t; i++) {
			T[i][0] = v[i];
		}

		for (int j = 1; (1 << j) <= t; j++) {
			for (int i = 1; i + (1 << j) - 1 <= t; i++) {
				T[i][j] = minh(T[i][j - 1], T[i + (1 << (j - 1))][j - 1]);
			}
		}
	}

	int lca(int x, int y) {
		int t;
		x = f[x], y = f[y];
		if (x > y) {
			swap(x, y);
		}
		for (t = 0; (1 << (t + 1)) <= (y - x + 1); t++);
		return minh(T[x][t], T[y - (1 << t) + 1][t]);
	}

	void process(int x, int y) {
		QN(i, l[x]) {
			if (qd[i] != y) {
				process(qd[i], x);
				d_up[x] += d_up[qd[i]];
				d_down[x] += d_down[qd[i]];
			}
		}
		if (d_up[x] && d_down[x]) {
			YES = false;
		}
	}
} processor;

int n, m, q, x, y, ed, t, C, l[N], qd[N], qn[N], w[N], v[N], col[N];

void emplace(int x, int y) {
	qd[++ed] = y, qn[ed] = l[x], l[x] = ed;
}

void dfs(int x, int y) {
	v[x] = w[x] = ++t;
	for (int i = l[x]; i; i = qn[i]) {
		if (!v[qd[i]]) {
			dfs(qd[i], i ^ 1);
			w[x] = min(w[x], w[qd[i]]);
		}
		else {
			if (i != y) {
				w[x] = min(w[x], v[qd[i]]);
			}
		}
	}
}

void color(int x, int y) {
	col[x] = y;
	QN(i, l[x]) {
		if (!col[qd[i]]) {
			if (w[qd[i]] > v[x]) {
				++C;
				processor.add(y, C), processor.add(C, y);
				color(qd[i], C);
			}
			else {
				color(qd[i], col[x]);
			}
		}
	}
}

int main() {
	ed = 1;
	scanf_s("%d%d%d", &n, &m, &q);
	while (m--) {
		scanf_s("%d%d", &x, &y);
		emplace(x, y), emplace(y, x);
	}
	ITER(i, 1, n) {
		if (!v[i]) {
			dfs(i, -1);
			++C;
			processor.add(0, C);
			processor.add(C, 0);
			color(i, C);
		}
	}
	processor.dfs(0, 0);
	processor.init();
	processor.YES = true;
	while (q--) {
		scanf_s("%d%d", &x, &y);
		if (col[x] == col[y]) {
			continue;
		}
		x = col[x], y = col[y];
		int w = processor.lca(x, y);
		if (w == 0) {
			puts("No");
			return 0;
		}
		processor.d_up[x]++;
		processor.d_down[y]++;
		processor.d_up[w]--;
		processor.d_down[w]--;
	}
	processor.process(0, -1);
	puts(processor.YES ? "Yes" : "No");
}