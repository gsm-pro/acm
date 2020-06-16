#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
using namespace std;
#define iter(i, a, b) for (int i = (a); i < (b); i++)
#define forn(i, n) iter(i, 0, n)
const int oo = 10000;
const int NMAX = 7505;

struct Edge {
	short x, y, xx, yy, w;

	Edge(short a = 0, short b = 0, short c = 0) {
		x = a, y = b, w = c, xx = x, yy = y;
	}
};

vector<Edge> E;
vector<short> result[NMAX];

void addEdge(pair<short, short> e) {
	result[e.second].clear();
	result[e.second].push_back(e.first);
}

int directedMST(int N, int M, int root) {
	short back[NMAX], label[NMAX], bio[NMAX], cost[NMAX];
	Edge edge[NMAX];
	int mstCost = 0;
	for (;;) {
		forn(i, N) {
			cost[i] = oo;
		}
		forn(i, M) {
			Edge e = E[i];
			if (e.x == e.y) {
				continue;
			}
			if (e.w < cost[e.y]) {
				cost[e.y] = e.w;
				back[e.y] = e.x;
				edge[e.y] = e;
			}
		}
		cost[root] = 0;
		forn(i, N) {
			if (cost[i] == oo) {
				return -1;
			}
		}
		forn(i, N) {
			mstCost += cost[i];
			if (i != root) {
				addEdge(make_pair(edge[i].xx, edge[i].yy));
			}
		}
		forn(i, N) {
			label[i] = bio[i] = -1;
		}
		int K = 0;
		forn(i, N) {
			int x = i;
			for (; x != root && bio[x] == -1; x = back[x]) {
				bio[x] = i;
			}
			if (x != root && bio[x] == i) {
				for (; label[x] == -1; x = back[x]) {
					label[x] = K;
				}
				K++;
			}
		}
		if (K == 0) {
			break;
		}
		forn(i, N) {
			if (label[i] == -1) {
				label[i] = K++;
			}
		}
		forn(i, M) {
			int xx = label[E[i].x], yy = label[E[i].y];
			if (xx != yy) {
				E[i].w -= cost[E[i].y];
			}
			E[i].x = xx;
			E[i].y = yy;
		}
		root = label[root];
		N = K;
	}
	return mstCost;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, A, P, Y;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> A >> P;
		if (A != 0) {
			E.push_back(Edge(0, i, A));
		}
		for (int j = 0; j < P; j++) {
			cin >> Y;
			E.push_back(Edge(i, Y, 0));
		}
	}
	int ans = directedMST(N + 1, E.size(), 0);
	if (ans == -1) {
		return puts("-1"), 0;
	}
	cout << ans << endl;
	int cnt = 0;
	for (int j = 0; j < NMAX; j++) {
		for (size_t i = 0; i < result[j].size(); i++) {
			if (!result[j][i]) {
				cnt++;
				break;
			}
		}
	}
	cout << cnt << endl;
	for (int j = 0; j < NMAX; j++) {
		for (size_t i = 0; i < result[j].size(); i++) {
			if (!result[j][i]) {
				cout << j << " ";
				break;
			}
		}
	}
}