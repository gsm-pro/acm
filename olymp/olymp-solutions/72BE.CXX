#include<fstream>
#include<cassert>
#include<vector>
#include<map>
#include<set>
using namespace std;
#define MAXV 333
ifstream I("input.txt");
ofstream O("output.txt");

struct Edge {
	int a, b, color;

	Edge(int _a, int _b, int _color) : a(_a), b(_b), color(_color) {}
};

int X, Y, E, Q;
vector<Edge> edges;
vector<int> G[MAXV];
map<int, int> colors[MAXV];
set<int> remain[MAXV];

void doUnColor(int u, int color) {
	if (color == -1) return;
	auto it = colors[u].find(color);
	assert(it != colors[u].end());
	colors[u].erase(it);
	remain[u].insert(color);
	assert((int)(colors[u].size() + remain[u].size()) == Q);
}

void doColor(int u, int color, int ei) {
	assert(colors[u].find(color) == colors[u].end());
	auto it = remain[u].find(color);
	assert(it != remain[u].end());
	colors[u][color] = ei;
	remain[u].erase(it);
	assert((int)(colors[u].size() + remain[u].size()) == Q);
}

int findColor(int a, int ei, int except) {
	int b = (a == edges[ei].a ? edges[ei].b : edges[ei].a);
	for (int c : remain[a])
		if (c != except && remain[b].find(c) != remain[b].end()) return c;
	for (int c : remain[a])
		if (c != except) return c;
	assert(0);
	return -1;
}

void doColorEdge(int u, int ei, int color) {
	Edge& e = edges[ei];
	int pre_color = e.color;
	if (pre_color == color) return;
	edges[ei].color = color;
	doUnColor(u, pre_color);
	doColor(u, color, ei);
	int nxt = (u == e.a ? e.b : e.a);
	doUnColor(nxt, pre_color);
	auto it = colors[nxt].find(color);
	if (it != colors[nxt].end()) doColorEdge(nxt, it->second, pre_color != -1 ? pre_color : findColor(nxt, it->second, color));
	doColor(nxt, color, ei);
}

void doColorVertex(int u) {
	for (int ei : G[u])
		if (edges[ei].color == -1) doColorEdge(u, ei, findColor(u, ei, -1));
}

int main() {
	int n, m;
	I >> n >> m;
	X = Y = n, E = m;
	Y += X;
	for (int i = 0, a, b, host; i < E; i++) {
		I >> a >> b >> host;
		a--, b--, host--;
		if (b == host) swap(a, b);
		b += X;
		edges.emplace_back(a, b, -1);
		G[a].push_back(i);
		G[b].push_back(i);
	}
	Q = 0;
	for (int i = 0; i < Y; i++) Q = max(Q, (int)G[i].size());
	for (int i = 0; i < Y; i++)
		for (int c = 0; c < Q; c++) remain[i].insert(c);
	for (int i = 0; i < Y; i++) doColorVertex(i);
	O << Q << endl;
	assert(E == (int)edges.size());
	for (int i = 0; i < E; i++) O << edges[i].color + 1 << " ";
}