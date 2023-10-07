#include<iostream>
#include<cstdio>
#include<algorithm>
#define F(x) tree[x].fa
#define LC(x) tree[x].childL
#define RC(x) tree[x].childR
#define REV(x) tree[x].rev
#define Size 4000004
#define oo (1 << 25)
#define MAXLEN 7
using namespace std;
int TEN[MAXLEN] = { 1, 10, 100, 1000, 10000, 100000, 1000000 };

inline int read() {
	int number = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		number = number * 10 + c - '0';
		c = getchar();
	}
	return number;
}

inline void write(int number) {
	bool out = false;
	for (int i = MAXLEN - 1; i >= 0; i--) {
		int digit = number / TEN[i];
		if (out) {
			putchar('0' + digit);
		}
		if (digit > 0 && !out) {
			out = true;
			putchar('0' + digit);
		}
		number %= TEN[i];
	}
	putchar(' ');
}

struct lct {
	int fa, childL, childR, rev, v, MAX;
}tree[Size];

struct link_cut_tree {
	inline bool isRoot(int x) {
		return LC(F(x)) != x && RC(F(x)) != x;
	}

	inline void increase(int x, int val) {
		tree[x].v += val;
		tree[x].MAX += val;
	}

	inline void _PushUp(int x) {
		tree[x].MAX = max(tree[LC(x)].MAX, tree[RC(x)].MAX);
		tree[x].MAX = max(tree[x].MAX, tree[x].v);
	}

	inline void _PushDown(int x) {
		if (REV(x)) {
			REV(x) ^= 1;
			REV(LC(x)) ^= 1;
			REV(RC(x)) ^= 1;
			swap(LC(x), RC(x));
		}
	}

	void pushDown(int x) {
		if (!isRoot(x)) {
			pushDown(F(x));
		}
		_PushDown(x);
	}

	inline void rotate(int x) {
		int A = F(x), B = F(A);
		bool w = (RC(A) == x);
		if (!isRoot(A)) {
			if (LC(B) == A) {
				LC(B) = x;
			}
			else {
				if (RC(B) == A) {
					RC(B) = x;
				}
			}
		}
		F(w ? LC(x) : RC(x)) = A;
		F(A) = x;
		F(x) = B;
		if (w) {
			RC(A) = LC(x);
			LC(x) = A;
		}
		else {
			LC(A) = RC(x);
			RC(x) = A;
		}
		_PushUp(A);
		_PushUp(x);
	}

	inline void splay(int x) {
		pushDown(x);
		while (!isRoot(x)) {
			if (!isRoot(F(x))) {
				rotate(x);
			}
			rotate(x);
		}
	}

	inline void access(int x) {
		for (int i = 0; x; i = x, x = F(x)) {
			splay(x);
			RC(x) = i;
			_PushUp(x);
		}
	}

	inline int findRoot(int x) {
		access(x);
		splay(x);
		while (LC(x)) {
			x = LC(x);
		}
		return x;
	}

	inline void reverse(int x) {
		access(x);
		splay(x);
		REV(x) ^= 1;
	}

	inline void link(int x, int y) {
		reverse(x);
		F(x) = y;
	}

	inline void cut(int x, int y) {
		reverse(x);
		access(y);
		splay(y);
		F(LC(y)) = 0;
		LC(y) = 0;
		_PushUp(y);
	}

	inline void add(int x, int val) {
		splay(x);
		increase(x, val);
		_PushUp(x);
	}

	inline int query(int x, int y) {
		reverse(x);
		access(y);
		splay(y);
		return tree[y].MAX;
	}
}LCT;

int main() {
	int n = read();
	int nn = n + 1;
	for (int i = 1; i <= n - 1; i++) {
		int x = read(), y = read(), w = read();
		LCT.link(x, nn);
		LCT.link(nn, y);
		LCT.add(nn, oo - w);
		nn++;
	}
	int m = read();
	while (m--) {
		write(oo - LCT.query(read(), read()));
	}
}