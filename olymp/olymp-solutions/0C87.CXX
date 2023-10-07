#include<fstream>
#include<vector>
#include<map>
#include<set>
#include<ctime>
using namespace std;
vector<int> X, Z, NEXT;
map<int, set<int>> num2pos;
int N, H, D, INF = 777777;

struct Node {
	int p, v, c;
	Node* l, * r;
	int mx;
	Node(int value) {
		v = mx = value;
		p = rand();
		c = 1;
		l = r = NULL;
	}
};

Node* t = 0;

int get_c(Node* t) {
	return t ? t->c : 0;
}

int get_mx(Node* t) {
	return t ? t->mx : -INF;
}

void update(Node* t) {
	if (!t) return;
	t->c = get_c(t->l) + get_c(t->r) + 1;
	t->mx = max(t->v, max(get_mx(t->l), get_mx(t->r)));
}

void push(Node* t) {
	if (!t) return;
}

Node* merge(Node* a, Node* b) {
	push(a);
	push(b);
	if (!a || !b) return a ? a : b;
	else if (a->p > b->p) {
		a->r = merge(a->r, b);
		update(a);
		return a;
	}
	else {
		b->l = merge(a, b->l);
		update(b);
		return b;
	}
}

void split(Node* t, int k, Node*& a, Node*& b) {
	push(t);
	if (!t) a = b = 0;
	else if (get_c(t->l) < k) {
		split(t->r, k - get_c(t->l) - 1, t->r, b);
		a = t;
		update(a);
	}
	else {
		split(t->l, k, a, t->l);
		b = t;
		update(b);
	}
}

void insert(int k, int v) {
	Node* t1, * t2, * tn = new Node(v);
	split(t, k, t1, t2);
	t1 = merge(t1, tn);
	t = merge(t1, t2);
}

int upper_bound(Node* t, int v, int add = 0) {
	if (!t) return 0;
	if (t->r && get_mx(t->r) > v)
		return upper_bound(t->r, v, add + get_c(t->l) + 1);
	if (t->v > v)
		return t->v;
	if (t->l && get_mx(t->l) > v)
		return upper_bound(t->l, v, add);
	return 0;
}

int main() {
	srand(int(time(NULL)));
	ifstream I("input.txt");
	I >> N >> H >> D;
	X.resize(N);
	NEXT.resize(N);
	for (int i = 0; i < N; i++) {
		I >> X[i];
		num2pos[X[i]].insert(i);
	}
	for (int i = N - 1; i >= 0; i--) {
		NEXT[i] = upper_bound(t, X[i] + H);
		insert(N - 1 - i, X[i]);
	}
	Z.assign(N, INF);
	Z[0] = 0;
	for (int i = 0; i < N - 1; i++) {
		int maxleap = min(i + D, N - 1);
		if (NEXT[i] != 0) maxleap = min(maxleap, *num2pos[NEXT[i]].lower_bound(i) - 1);
		for (int j = maxleap;; j--)
			if (Z[j] > Z[i] + 1) Z[j] = Z[i] + 1;
			else break;
	}
	ofstream("output.txt") << (Z[N - 1] == INF ? -1 : Z[N - 1]);
}