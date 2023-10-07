#include<iostream>
#define MAXN 333
#define MAXM 14444
#define INF (1 << 28);
using namespace std;
int start, finish, hl, n, m, z, hp[MAXN];

struct junction {
	int c, rc, t[2];
} junc[MAXN];

struct theap {
	int v, d, p;
} heap[MAXN];

struct tnode {
	tnode *next;
	int v, w;
};

tnode *g[MAXN];

inline void push(int u, int v, int w) {
	tnode *x = new tnode;
	x->v = v;
	x->w = w;
	x->next = g[u];
	g[u] = x;
}

void read() {
	char c;
	cin >> start >> finish >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> c >> junc[i].rc >> junc[i].t[0] >> junc[i].t[1];
		junc[i].c = (c == 'B') ? 0 : 1;
	}
	memset(g, 0, sizeof g);
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		push(u, v, w);
		push(v, u, w);
	}
}

void swap(int a, int b) {
	heap[0] = heap[a];
	heap[a] = heap[b];
	heap[b] = heap[0];
	hp[heap[a].v] = a;
	hp[heap[b].v] = b;
}

void heapUp(int i) {
	while (i != 1 && heap[i].d < heap[i >> 1].d) {
		swap(i, i >> 1);
		i >>= 1;
	}
}

void heapDown() {
	int i = 2;
	while (i <= hl) {
		if (i < hl && heap[i + 1].d < heap[i].d) {
			i++;
		}
		if (heap[i].d < heap[i >> 1].d) {
			swap(i, i >> 1);
			i <<= 1;
		}
		else {
			break;
		}
	}
}

void relax(int u, int v, int w) {
	int tmp = heap[hp[u]].d, time = 0,
		t1 = junc[u].c, t2 = junc[v].c, t3 = junc[u].rc, t4 = junc[v].rc;
	tmp %= (junc[u].t[0] + junc[u].t[1]);
	while (tmp >= junc[u].rc) {
		tmp -= junc[u].rc;
		junc[u].c ^= 1;
		junc[u].rc = junc[u].t[junc[u].c];
	}
	junc[u].rc -= tmp;
	tmp = heap[hp[u]].d;
	tmp %= (junc[v].t[0] + junc[v].t[1]);
	while (tmp >= junc[v].rc) {
		tmp -= junc[v].rc;
		junc[v].c ^= 1;
		junc[v].rc = junc[v].t[junc[v].c];
	}
	junc[v].rc -= tmp;
	z = 0;
	while (junc[u].c != junc[v].c) {
		z++;
		if (z > 3) {
			break;
		}
		if (junc[u].rc > junc[v].rc) {
			junc[u].rc -= junc[v].rc;
			time += junc[v].rc;
			junc[v].c ^= 1;
			junc[v].rc = junc[v].t[junc[v].c];
		}
		else {
			if (junc[u].rc < junc[v].rc) {
				junc[v].rc -= junc[u].rc;
				time += junc[u].rc;
				junc[u].c ^= 1;
				junc[u].rc = junc[u].t[junc[u].c];
			}
			else {
				time += junc[u].rc;
				junc[v].c ^= 1;
				junc[v].rc = junc[v].t[junc[v].c];
				junc[u].c ^= 1;
				junc[u].rc = junc[u].t[junc[u].c];
			}
		}
	}
	if (z <= 3 && time + w + heap[hp[u]].d < heap[hp[v]].d) {
		heap[hp[v]].p = u;
		heap[hp[v]].d = time + w + heap[hp[u]].d;
		heapUp(hp[v]);
	}
	junc[u].c = t1;
	junc[v].c = t2;
	junc[u].rc = t3;
	junc[v].rc = t4;
}

void dijkstra() {
	for (int u = 1; u <= n; u++) {
		heap[u].v = u;
		heap[u].d = INF;
		hp[u] = u;
	}
	heap[start].d = 0;
	heap[start].p = start;
	swap(1, start);
	hl = n;
	tnode *p = 0;
	while (hl > 0) {
		int u = heap[1].v;
		swap(1, hl);
		hl--;
		heapDown();
		p = g[u];
		while (p != 0) {
			if (hp[p->v] <= hl) {
				relax(u, p->v, p->w);
			}
			p = p->next;
		}
	}
}

void dfs(int x) {
	if (x == 0) {
		return;
	}
	if (heap[hp[x]].p != start) {
		dfs(heap[hp[x]].p);
	}
	cout << " " << x;
}

void write() {
	if (heap[hp[finish]].p == 0) {
		cout << 0 << endl;
		return;
	}
	cout << heap[hp[finish]].d << endl;
	cout << start;
	dfs(finish);
}

int main() {
	read();
	dijkstra();
	write();
}