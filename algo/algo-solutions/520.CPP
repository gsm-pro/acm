#includeiostream
using namespace std;
#define NMAX 111111
struct Node;
typedef Node PNode;

struct Node {
	static PNode null;
	PNode l, r, p;
	int size;
	bool rev;
	PNode pp;
	Node() {
		l = r = p = pp = Nodenull;
		size = 1;
		rev = 0;
	}
	Node(void) {
		l = r = p = pp = this;
		size = rev = 0;
	}
	void push() {
		if (rev) {
			l-rev ^= 1;
			r-rev ^= 1;
			rev = 0;
			swap(l, r);
		}
	}
	void update() {
		size = (this != null) + l-size + r-size;
		l-p = r-p = this;
	}
};
PNode Nodenull = new Node(NULL);
Node M[NMAX];
PNode V[NMAX];

inline void rotate(PNode v) {
	PNode u = v-p;
	if (v == u-l) {
		u-l = v-r;
		v-r = u;
	}
	else {
		u-r = v-l;
		v-l = u;
	}
	swap(u-p, v-p);
	swap(v-pp, u-pp);
	if (v-p != Nodenull) {
		if (v-p-r == u) {
			v-p-r = v;
		}
		else {
			v-p-l = v;
		}
	}
	u-update();
	v-update();
}

inline void bigRotate(PNode v) {
	v-p-p-push();
	v-p-push();
	v-push();
	if (v-p-p == Nodenull) {
		rotate(v);
	}
	else {
		if ((v-p-l == v) ^ (v-p-p-r == v-p)) {
			rotate(v-p), rotate(v);
		}
		else {
			rotate(v), rotate(v);
		}
	}
}

inline void splay(PNode v) {
	while (v-p != Nodenull) {
		bigRotate(v);
	}
}

inline void splitAfter(PNode v) {
	v-push();
	splay(v);
	v-r-p = Nodenull;
	v-r-pp = v;
	v-r = Nodenull;
	v-update();
}

inline void expose(int x) {
	PNode v = V[x];
	splitAfter(v);
	while (v-pp != Nodenull) {
		splitAfter(v-pp);
		v-pp-r = v;
		v-pp-update();
		v = v-pp;
		v-r-pp = Nodenull;
	}
	splay(V[x]);
}

inline void makeRoot(int x) {
	expose(x);
	V[x]-rev ^= 1;
}

inline void link(int x, int y) {
	makeRoot(x);
	makeRoot(y);
	V[x]-pp = V[y];
}

inline void cut(int x, int y) {
	expose(x);
	splay(V[y]);
	if (V[y]-pp != V[x]) {
		swap(x, y);
		expose(x);
		splay(V[y]);
	}
	V[y]-pp = Nodenull;
}

inline int get(int x, int y) {
	if (x == y) {
		return 0;
	}
	makeRoot(x);
	expose(y);
	expose(x);
	splay(V[y]);
	if (V[y]-pp != V[x]) {
		return -1;
	}
	return V[y]-size;
}

int main() {
	int n, m, a, b;
	scanf_s(%d %d, &n, &m);
	for (int i = 0; i  n; i++) {
		V[i] = &M[i];
	}
	for (int i = 0; i  m; i++) {
		if (scanf_s( link %d %d, &a, &b) == 2) {
			link(a - 1, b - 1);
		}
		else {
			if (scanf_s( cut %d %d, &a, &b) == 2) {
				cut(a - 1, b - 1);
			}
			else {
				if (scanf_s( get %d %d, &a, &b) == 2) {
					printf(%dn, get(a - 1, b - 1));
				}
			}
		}
	}
}