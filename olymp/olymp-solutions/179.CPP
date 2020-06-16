#define _CRT_SECURE_NO_DEPRECATE
#include<cstdio>
using namespace std;
const int MAXL = 10001;
const int MAXM = 26 * 10000 + 3;

class DSU {
private:
	int ff[MAXM];

	int findRoot(int k) {
		int r = k, t;
		while (ff[r] > 0) {
			r = ff[r];
		}
		while (ff[k] > 0) {
			t = ff[k];
			ff[k] = r;
			k = t;
		}
		return r;
	}

public:
	void clear() {
		for (int i = 0; i < MAXM; i++) {
			ff[i] = -i;
		}
	}

	void unite(int a, int b) {
		ff[findRoot(a)] = findRoot(b);
	}

	bool check(int a, int b) {
		return ff[findRoot(a)] == ff[findRoot(b)];
	}

	int getRoot(int k) {
		return -ff[findRoot(k)];
	}
};

template<int LIM, int MAX> class SOL_TEMPLATE {
private:
	int s[MAX], s_cnt;

public:
	SOL_TEMPLATE() {
		s_cnt = 1;
		s[0] = 0;
	}

	void copy(int A) {
		s_cnt = 0;
		while (A) {
			s[s_cnt++] = A % LIM;
			A /= LIM;
		}
	}

	void print() {
		printf("%d", s[s_cnt - 1]);
		for (int i = s_cnt - 2; i >= 0; i--) {
			int k = LIM / 10;
			while (s[i] < k) {
				printf("0");
				k /= 10;
			}
			if (s[i]) {
				printf("%d", s[i]);
			}
		}
	}

	void multiply(int p) {
		if (p == 0) {
			s_cnt = 1;
			s[0] = 0;
			return;
		}
		int sc = s_cnt, cr = 0;
		for (int i = 0; i < sc; i++) {
			if (i >= s_cnt) {
				s[i] = 0;
			}
			s[i] = s[i] * p + cr;
			cr = s[i] / LIM;
			s[i] %= LIM;
		}
		s_cnt = sc;
		if (cr) {
			s[s_cnt++] = cr;
		}
	}
};

typedef SOL_TEMPLATE<100000000, 1000> SOLUTION;
int TESTS, N, M[2], R, L[27], LEN[2], Q[2][MAXL];
char E[2][MAXL];
bool hsh[MAXM];
DSU dsu;

inline int getId(char c) {
	if (c == '1') {
		return 26 * 10000 + 1;
	}
	if (c == '0') {
		return 26 * 10000 + 2;
	}
	return (c - 'a') * 10000;
}

bool read() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &L[i]);
	}
	for (int k = 0; k <= 1; k++) {
		scanf("%d", &LEN[k]);
		scanf("%s", &E[k]);
		M[k] = 0;
		for (int i = 0; i < LEN[k]; i++) {
			int d = getId(E[k][i]);
			if (E[k][i] == '0' || E[k][i] == '1') {
				Q[k][++M[k]] = d;
			}
			else {
				for (int j = 1; j <= L[E[k][i] - 'a' + 1]; j++) {
					Q[k][++M[k]] = d + j;
				}
			}
		}
	}
	return (R = M[0]) == M[1];
}

int process() {
	int cnt = 0;
	dsu.clear();
	for (int i = 0; i < MAXM; i++) {
		hsh[i] = 0;
	}
	for (int i = 1; i <= R; i++) {
		if (!dsu.check(Q[0][i], Q[1][i])) {
			dsu.unite(Q[0][i], Q[1][i]);
		}
	}
	int L0 = dsu.getRoot(26 * 10000 + 2), L1 = dsu.getRoot(26 * 10000 + 1);
	if (L0 == L1) {
		return -1;
	}
	hsh[L0] = hsh[L1] = true;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= L[i]; j++) {
			int d = dsu.getRoot((i - 1) * 10000 + j);
			if (!hsh[d]) {
				hsh[d] = true;
				cnt++;
			}
		}
	}
	return cnt;
}

void solve() {
	SOLUTION ANS;
	scanf_s("%d", &TESTS);
	for (int q = 1; q <= TESTS; q++) {
		if (read()) {
			ANS.copy(1);
			int A = process();
			if (A == -1) {
				printf("0");
			}
			else {
				for (int j = 1; j <= A; j++) {
					ANS.multiply(2);
				}
				ANS.print();
			}
		}
		else {
			printf("0");
		}
		printf("\n");
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	solve();
}