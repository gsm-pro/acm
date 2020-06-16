#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<bitset>
using namespace std;
typedef pair<int, pair<int, int>> PPII;
const int MAXN = 30003;
const int MAXM = 110011;
const int MAXNLOG = 18;
priority_queue<PPII, vector<PPII>, greater<PPII>> PQ;
vector<PPII> H[MAXN];
vector<int> G[MAXN];
bitset<MAXM> R;
int dsu[MAXN], tin[MAXN], tout[MAXN], P[MAXN][MAXNLOG], MXP[MAXN][MAXNLOG];
int timer, MSTW;
bool U1[MAXN], U2[MAXN], U3[MAXN];

struct Edge {
	int a, b, w, id;
	Edge() {}
	Edge(int a, int b, int w, int id) : a(a), b(b), w(w), id(id) {}
};

vector<Edge> V, E1, E2, F[MAXN];

int dsuGet(int i) {
	return i == dsu[i] ? i : dsu[i] = dsuGet(dsu[i]);
}

void dsuUnite(int a, int b) {
	a = dsuGet(a);
	b = dsuGet(b);
	if (rand() & 1) {
		dsu[a] = b;
	}
	else {
		dsu[b] = a;
	}
}

bool cmp(Edge &a, Edge &b) {
	return a.w < b.w;
}

void kruskal() {
	for (int i = 0; i < MAXN; i++) {
		dsu[i] = i;
	}
	sort(V.begin(), V.end(), cmp);
	for (int i = 0; i < (int)(V.size()); i++) {
		if (dsuGet(V[i].a) != dsuGet(V[i].b)) {
			dsuUnite(V[i].a, V[i].b);
			F[V[i].a].push_back(V[i]);
			F[V[i].b].push_back(V[i]);
			MSTW += V[i].w;
		}
	}
}

void buildLca(int v, int pr, Edge from) {
	U1[v] = true;
	P[v][0] = pr;
	tin[v] = ++timer;
	MXP[v][0] = from.w;
	for (int i = 1; i < MAXNLOG; i++) {
		P[v][i] = P[P[v][i - 1]][i - 1];
		MXP[v][i] = max(MXP[v][i - 1], MXP[P[v][i - 1]][i - 1]);
	}
	for (size_t i = 0; i < F[v].size(); i++) {
		int to = (F[v][i].a == v ? F[v][i].b : F[v][i].a);
		if (!U1[to]) {
			buildLca(to, v, F[v][i]);
		}
	}
	tout[v] = ++timer;
}

bool isParent(int a, int b) {
	return (tin[a] <= tin[b] && tout[a] >= tout[b]);
}

int maxUp(int a, int r, int ans = 0) {
	for (int i = MAXNLOG - 1; i >= 0; i--) {
		if (!isParent(P[a][i], r)) {
			ans = max(ans, MXP[a][i]);
			a = P[a][i];
		}
	}
	return max(ans, MXP[a][0]);
}

int lca(int a, int b, int ans = 0) {
	if (isParent(a, b)) {
		return maxUp(b, a);
	}
	if (isParent(b, a)) {
		return maxUp(a, b);
	}
	for (int i = MAXNLOG - 1; i >= 0; i--) {
		if (!isParent(P[a][i], b)) {
			ans = max(ans, MXP[a][i]);
			a = P[a][i];
		}
	}
	ans = max(ans, MXP[a][0]);
	a = P[a][0];
	return max(ans, maxUp(b, a));
}

void init(vector<Edge> E) {
	for (size_t i = 0; i < MAXN; i++) {
		F[i].clear();
	}
	V = E;
	memset(dsu, 0, sizeof dsu);
	memset(tin, 0, sizeof tin);
	memset(tout, 0, sizeof tout);
	memset(P, 0, sizeof P);
	memset(MXP, 0, sizeof MXP);
	memset(U1, false, sizeof U1);
	MSTW = 0;
	timer = 0;
}

vector<int> solveWith(int m, vector<Edge> E) {
	init(E);
	kruskal();
	buildLca(0, 0, Edge(0, 0, 0, -1));
	vector<int> ans;
	ans.assign(m, 0);
	for (int i = 0; i < m; i++) {
		ans[V[i].id] = MSTW - lca(V[i].a, V[i].b) + V[i].w;
	}
	return ans;
}

void process(int idx) {
	U2[idx] = true;
	for (size_t i = 0; i < H[idx].size(); i++) {
		PPII v = H[idx][i];
		if (!U2[v.first]) {
			PQ.push(make_pair(v.second.first, make_pair(v.second.second, v.first)));
		}
	}
}

void prim(int idx) {
	process(idx);
	while (!PQ.empty()) {
		PPII v = PQ.top();
		PQ.pop();
		int to = v.second.second, index = v.second.first;
		if (!U2[to]) {
			R.set(index);
			process(to);
		}
	}
}

void calc(int selectedId, vector<Edge> E) {
	for (size_t i = 0; i < E.size(); i++) {
		H[E[i].a].push_back(make_pair(E[i].b,
			make_pair(selectedId == E[i].id ? -1 : E[i].w, E[i].id)));
		H[E[i].b].push_back(make_pair(E[i].a,
			make_pair(selectedId == E[i].id ? -1 : E[i].w, E[i].id)));
	}
	memset(U2, 0, sizeof U2);
	prim(E[selectedId].a);
	for (int i = 0; i < MAXM; i++) {
		if (R[i]) {
			printf("%d ", i + 1);
		}
	}
}

void dfs(int v) {
	U3[v] = true;
	for (size_t i = 0; i < G[v].size(); i++) {
		int to = G[v][i];
		if (!U3[to]) {
			dfs(to);
		}
	}
}

int main() {
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
	int n, m, a, b, w;
	scanf_s("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf_s("%d%d%d", &a, &b, &w);
		--a, --b;
		G[a].push_back(b);
		G[b].push_back(a);
		if (w == 1) {
			E1.push_back(Edge(a, b, 0, i));
			E2.push_back(Edge(a, b, 2, i));
		}
		if (w == 2) {
			E1.push_back(Edge(a, b, 1, i));
			E2.push_back(Edge(a, b, 1, i));
		}
	}
	memset(U3, false, sizeof U3);
	dfs(0);
	vector<int> ansE1, ansE2;
	for (int i = 0; i < n; i++) {
		if (!U3[i]) {
			goto quit;
		}
	}
	ansE1 = solveWith(m, E1);
	for (size_t i = 0; i < ansE1.size(); i++) {
		if (!(ansE1[i] & 1)) {
			calc(i, E1);
			return 0;
		}
	}
	ansE2 = solveWith(m, E2);
	for (size_t i = 0; i < ansE2.size(); i++) {
		if (!(ansE2[i] & 1)) {
			calc(i, E2);
			return 0;
		}
	}
quit:
	puts("-1");
}