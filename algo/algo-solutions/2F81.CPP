#include<iostream>
#include<set>
#include<algorithm>
using namespace std;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define NMAX 11111
#define MMAX 111111
typedef int ROW[NMAX];
typedef struct LIST {
	int inf;
	int dir;
	LIST * next;
	LIST(int inf = 0, LIST * next = NULL) : inf(inf), next(next) { };
} tlist;

ROW dsu;
ROW dsu_;
ROW tm;
int n = 0, m = 0;
LIST * graph[NMAX];
LIST * tree[NMAX];
LIST * order[NMAX];
int counter;
typedef pair<int, int> ipair;
typedef set<ipair> ipairset;
ipair vtime[NMAX];
int depth[NMAX];
int anc[NMAX];
int visited[NMAX];
int path[NMAX + 1];
ipairset sets[NMAX];
int inverse[NMAX];

int nextInt() {
	char c;
	int t = 0;
	while ((c = getchar()) > 0) {
		if (c == ' ' || c == '\r' || c == '\n') break;
		if (c<'0' || c>'9') continue;
		t *= 10;
		t += c - '0';
	}
	return t;
}

void listAdd(LIST * &l, int inf) {
	LIST * x = new LIST(inf, l);
	x->next = l, l = x;
}

void init(ROW &a, ROW &r, int n) {
	forn(i, n) a[i] = i, r[i] = 0;
}

int leader(ROW &a, int c) {
	if (a[c] != c) a[c] = leader(a, a[c]);
	return a[c];
}

bool unite(ROW &a, ROW &r, int idx1, int idx2) {
	int l1 = leader(a, idx1), l2 = leader(a, idx2);
	if (l1 != l2) {
		if (r[l1] < r[l2]) a[l1] = l2, r[l2] += r[l1]; else a[l2] = l1, r[l1] += r[l2];
		return true;
	}
	return false;
}

void rec(int idx, int d) {
	vtime[idx].first = (++counter);
	depth[idx] = d;
	for (LIST * x = tree[idx]; x != NULL; x = x->next) rec(x->inf, d + 1);
	vtime[idx].second = counter;
}

bool isLike(int idx1, int idx2) {
	return (vtime[idx1].first <= vtime[idx2].first && vtime[idx2].second <= vtime[idx1].second) 
		|| (vtime[idx2].first <= vtime[idx1].first && vtime[idx1].second <= vtime[idx2].second);
}

void lca(int idx) {
	path[++path[0]] = idx;
	counter++;
	visited[idx] = true;
	for (LIST * x = tree[idx]; x != NULL; x = x->next) {
		lca(x->inf);
		unite(dsu, dsu_, idx, x->inf);
		anc[leader(dsu, idx)] = idx;
		sets[idx].insert(make_pair(vtime[x->inf].first, x->inf));
	}
	for (LIST * x = graph[idx]; x != NULL; x = x->next) {
		if (!isLike(idx, x->inf) && visited[x->inf]) {
			int LCA = anc[leader(dsu, x->inf)];
			int LCA_NEXT = path[depth[LCA] + 1 + 1];
			ipairset::iterator it = sets[LCA].lower_bound(make_pair(vtime[x->inf].first, NMAX));
			it--;
			int LCA_NEXT_2 = it->second;
			if (x->dir == 1) listAdd(order[LCA_NEXT_2], LCA_NEXT); else listAdd(order[LCA_NEXT], LCA_NEXT_2);
		}
	}
	path[0]--;
}

void tsort(int idx) {
	if (visited[idx]) return;
	visited[idx] = 1;
	for (LIST * x = order[idx]; x != NULL; x = x->next) tsort(x->inf);
	path[++path[0]] = idx;
}

int main() {
	memset(tree, 0, sizeof(tree));
	memset(graph, 0, sizeof(graph));
	memset(order, 0, sizeof(order));
	ipairset tree_set;
	n = nextInt();
	forn(i, n) {
		if (i > 0) {
			int p = nextInt() - 1;
			listAdd(tree[p], i); 
			tree[p]->dir = +1;
			tree_set.insert(make_pair(p, i));
		}
	}
	forn(i, n) {
		int k = nextInt();
		forn(j, k) {
			int b = nextInt() - 1;
			listAdd(graph[i], b); 
			graph[i]->dir = 1;
			listAdd(graph[b], i); 
			graph[b]->dir = -1;
		}
	}
	init(dsu, dsu_, n);
	counter = 0;
	rec(0, 0);
	path[0] = 0;
	lca(0);
	path[0] = 0;
	memset(visited, 0, sizeof(visited));
	forn(i, n) if (!visited[i]) tsort(i);
	forn(i, n) inverse[path[i + 1]] = i;
	forn(i, n) {
		for (LIST * x = order[i]; x != NULL; x = x->next) {
			if (inverse[i] < inverse[x->inf]) {
				printf("NO");
				return 0;
			}
		}
	}
	printf("YES\n");
	ipair lst[MMAX];
	int c_lst = 0;
	forn(i, n) {
		c_lst = 0;
		for (LIST * x = graph[i]; x != NULL; x = x->next) {
			if (x->dir == 1) {
				lst[c_lst++] = make_pair(NMAX - inverse[x->inf], x->inf);
				if (tree_set.count(make_pair(i, x->inf)) == 0) lst[c_lst - 1].first = 2 * NMAX;
			}
		}
		printf("%d", c_lst);
		sort(lst, lst + c_lst);
		forn(j, c_lst) printf(" %d", lst[j].second + 1);
		printf("\n");
	}
}