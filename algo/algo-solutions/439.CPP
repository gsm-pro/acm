#include<vector>
#include<iostream>
#include<queue>
#include<functional>
using namespace std;
#define MAXN 111111
#define forn(i, n) for (int i = 0; i < (int)(n); i++)
pair<int, int> edge[MAXN];
int beard = -1, n;

struct Node {
	vector<int> edge;
	int number, lvl;
	Node() : number(-1), lvl(-1) {}

	bool isBeard() const {
		return edge.size() > 2;
	}

	bool isLeaf() const {
		return edge.size() == 1;
	}
} g[MAXN];

struct Fenwick {
	vector<int> t;

	void setSize(int n) {
		t.resize(n, 0);
	}

	void add(int pos, int val) {
		for (; pos < (int)t.size(); pos |= pos + 1) {
			t[pos] += val;
		}
	}

	int sum(int r) {
		int res = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1) {
			res += t[r];
		}
		return res;
	}

	int sum(int l, int r) {
		return sum(r) - sum(l - 1);
	}
} FT[MAXN];

void findBeard() {
	Node *p = find_if(g + 1, g + n + 1, mem_fun_ref(&Node::isBeard));
	if (p == g + n + 1) {
		p = find_if(g + 1, g + n + 1, mem_fun_ref(&Node::isLeaf));
	}
	beard = p - g;
}

void createBeard() {
	queue<pair<int, int>> Q;
	g[beard].lvl = 0;
	forn(i, g[beard].edge.size()) {
		int u = g[beard].edge[i];
		g[u].number = i;
		g[u].lvl = 1;
		Q.push(make_pair(u, i));
	}
	while (!Q.empty()) {
		int u = Q.front().first;
		int number = Q.front().second;
		Q.pop();
		forn(i, g[u].edge.size()) {
			int v = g[u].edge[i];
			if (g[v].number < 0 && v != beard) {
				g[v].number = number;
				g[v].lvl = g[u].lvl + 1;
				Q.push(make_pair(v, number));
			}
		}
	}
}

void initFenwick() {
	for (int u = 0; u <= n; ++u) {
		if (g[u].isLeaf() && u != beard) {
			FT[g[u].number].setSize(g[u].lvl + 1);
		}
	}
}

void init() {
	cin >> n;
	forn(i, n - 1) {
		int u, v;
		scanf_s("%d%d", &u, &v);
		edge[i + 1] = make_pair(min(u, v), max(u, v));
		g[u].edge.push_back(v);
		g[v].edge.push_back(u);
	}
	findBeard();
	createBeard();
	initFenwick();
}

bool eq(int a, int b) {
	return (g[a].number < 0 || g[b].number < 0) || (g[a].number == g[b].number);
}

int main() {
	init();
	int m, type, id, a, b;
	cin >> m;
	while (m--) {
		scanf_s("%d", &type);
		if (type == 1 || type == 2) {
			scanf_s("%d", &id);
			int num = max(g[edge[id].first].number, g[edge[id].second].number),
				u = min(g[edge[id].first].lvl, g[edge[id].second].lvl);
			FT[num].add(u, (type == 1 ? 1 : -1));
			continue;
		}
		scanf_s("%d%d", &a, &b);
		if (eq(a, b)) {
			int num = max(g[a].number, g[b].number),
				minlvl = min(g[a].lvl, g[b].lvl),
				maxlvl = max(g[a].lvl, g[b].lvl);
			if (FT[num].sum(minlvl, maxlvl - 1) == 0) {
				printf("%d", maxlvl - minlvl);
			}
			else {
				printf("-1");
			}
		}
		else {
			int aLvl = g[a].lvl, aNum = g[a].number,
				bLvl = g[b].lvl, bNum = g[b].number;
			if (FT[aNum].sum(0, aLvl - 1) || FT[bNum].sum(0, bLvl - 1)) {
				printf("-1");
			}
			else {
				printf("%d", aLvl + bLvl);
			}
		}
		puts("");
	}
}