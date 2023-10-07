#include<bits/stdc++.h>
#define X first
#define Y second
using namespace std;

struct Node {
	Node* l = nullptr, * r = nullptr;
	int col = -1;
} *root = new Node;

void setSegment(int l, int r, int col, Node* c, int cl, int cr) {
	if (cr < l || r < cl) return;
	if (l <= cl && cr <= r) c->col = col; else {
		if (c->l == nullptr) c->l = new Node;
		setSegment(l, r, col, c->l, cl, (cl + cr) / 2);
		if (c->r == nullptr) c->r = new Node;
		setSegment(l, r, col, c->r, (cl + cr) / 2 + 1, cr);
	}
}

pair<int, vector<int>> go(Node* v) {
	if (v->col != -1) return { 0, {v->col} };
	auto dl = go(v->l), dr = go(v->r);
	vector<int> its, uni;
	set_intersection(dl.Y.begin(), dl.Y.end(), dr.Y.begin(), dr.Y.end(),
		back_insert_iterator<vector<int>>(its));
	if (its.empty()) {
		merge(dl.Y.begin(), dl.Y.end(), dr.Y.begin(), dr.Y.end(),
			back_insert_iterator<vector<int>>(uni));
		return { dl.X + dr.X + 1, uni };
	}
	return { dl.X + dr.X, its };
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int k, n, cl = 0, cm;
	scanf("%d%d%d", &k, &n, &cm);
	for (int i = 0, len, c; i < n; ++i) {
		scanf("%d%d", &len, &c);
		setSegment(cl, cl + len - 1, c, root, 0, (1 << k) - 1);
		cl += len;
	}
	auto d = go(root);
	cout << d.X + (d.Y[0] == 0 ? 0 : 1);
}