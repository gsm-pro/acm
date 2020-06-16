#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef int* pint;
#define NMAX 333333
int N, M, ans[NMAX], dsuParent[NMAX], dsuSZ[NMAX], oddCnt;
vector<pair<pint, int>> events;

struct TNode {
	int u, v, len, clck;
	TNode() {}
	TNode(int _u, int _v, int _len, int _clck) {
		u = _u, v = _v, len = _len, clck = _clck;
	}

	bool operator < (const TNode &other) const {
		return len != other.len ? len < other.len : clck < other.clck;
	}
} A[NMAX], A_sorted[NMAX];

void pushEvent(int &a, int b) {
	events.push_back(make_pair(&a, a));
	a = b;
}

void popEvent(int h) {
	while ((int)events.size() > h) {
		*events.back().first = events.back().second;
		events.pop_back();
	}
}

int dsuFind(int x) {
	while (x != dsuParent[x]) {
		x = dsuParent[x];
	}
	return x;
}

void dsuMerge(int a, int b) {
	a = dsuFind(a), b = dsuFind(b);
	if (a != b) {
		if (dsuSZ[a] < dsuSZ[b]) {
			swap(a, b);
		}
		if ((dsuSZ[a] & 1) && (dsuSZ[b] & 1)) {
			pushEvent(oddCnt, oddCnt - 2);
		}
		pushEvent(dsuSZ[a], dsuSZ[a] + dsuSZ[b]);
		pushEvent(dsuParent[b], a);
	}
}

void solve(int lf, int rg, int x) {
	if (lf > rg) {
		return;
	}
	int mid = (lf + rg) >> 1, h = events.size();
	for (int i = lf; i <= mid; i++) {
		if (A[i] < A_sorted[x]) {
			dsuMerge(A[i].u, A[i].v);
		}
	}
	solve(mid + 1, rg, x);
	int q = x;
	for (; q < M; q++) {
		if (A_sorted[q].clck <= mid) {
			dsuMerge(A_sorted[q].u, A_sorted[q].v);
		}
		if (oddCnt == 0) {
			break;
		}
	}
	ans[mid] = oddCnt == 0 ? A_sorted[q].len : -1;
	popEvent(h);
	for (int i = x; i < q; i++) {
		if (A_sorted[i].clck < lf) {
			dsuMerge(A_sorted[i].u, A_sorted[i].v);
		}
	}
	solve(lf, mid - 1, q);
	popEvent(h);
}

int main() {
	scanf_s("%d%d", &N, &M);
	for (int i = 0; i < M; i++) {
		int u, v, l;
		scanf_s("%d%d%d", &u, &v, &l);
		A[i] = A_sorted[i] = TNode(u - 1, v - 1, l, i);
	}
	sort(A_sorted, A_sorted + M);
	for (int i = 0; i < N; i++) {
		dsuParent[i] = i, dsuSZ[i] = 1;
	}
	oddCnt = N;
	solve(0, M - 1, 0);
	for (int i = 0; i < M; i++) {
		printf("%d\n", ans[i]);
	}
}