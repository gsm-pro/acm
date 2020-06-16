#include<fstream>
#include<algorithm>
using namespace std;
typedef __int64 LL;
const LL INF = 1LL << 60;
const int N = 11111;
ifstream I("input.txt");
ofstream O("output.txt");
LL A[N], B[N], X[N], S = 0;
int U[N], DEP[N], n, i;

void dfs(int v) {
	int from = v, to = DEP[v];
	U[from] = 1;
	if (!U[to]) {
		A[to] = A[from] - X[from];
		dfs(to);
	}
}

void pre() {
	for (i = 0; i < n; i++) {
		int nxt = (i + 1) % n, from = (i - 1 + n) % n, to = (i + 2) % n;
		DEP[from] = to;
		X[from] = B[i] - B[nxt];
	}
}

void solve() {
	pre();
	for (i = 0; i < n; i++) {
		if (!U[i]) {
			A[i] = 0;
			dfs(i);
		}
	}
	for (i = 0; i < n; i++) {
		O << A[i] + (B[0] - A[1] - A[0] - A[n - 1]) / 3 << endl;
	}
}

void checkAndOut(LL DX, LL DY, LL DZ) {
	LL D[N];
	for (i = 0; i < n; i++) {
		int q = i % 3;
		if (!q) {
			D[i] = A[i] + DX;
		}
		if (q == 1) {
			D[i] = A[i] + DY;
		}
		if (q == 2) {
			D[i] = A[i] + DZ;
		}
	}
	for (i = 0; i < n; i++) {
		if (D[i] + D[(i + 1) % n] + D[(i - 1 + n) % n] != B[i]) {
			return;
		}
	}
	for (i = 0; i < n; i++) {
		O << D[i] << endl;
	}
	exit(0);
}

void solve3() {
	pre();
	dfs(0);
	dfs(1);
	dfs(2);
	LL min0 = INF, min1 = INF, min2 = INF, S0 = 0;
	for (i = 0; i < n; i++) {
		int q = i % 3;
		if (!q) {
			min0 = min(min0, A[i]);
		}
		if (q == 1) {
			min1 = min(min1, A[i]);
		}
		if (q == 2) {
			min2 = min(min2, A[i]);
		}
	}
	for (i = 0; i < n; i++) {
		int q = i % 3;
		if (!q) {
			A[i] += (-min0 + 1);
		}
		if (q == 1) {
			A[i] += (-min1 + 1);
		}
		if (q == 2) {
			A[i] += (-min2 + 1);
		}
		S0 += A[i];
	}
	LL XYZ = ((S / 3) - S0) / (n / 3);
	checkAndOut(0, 0, XYZ);
	checkAndOut(0, XYZ, 0);
	checkAndOut(XYZ, 0, 0);
	XYZ--;
	checkAndOut(0, 1, XYZ);
	checkAndOut(1, 0, XYZ);
	checkAndOut(1, XYZ, 0);
	checkAndOut(0, XYZ, 1);
	checkAndOut(XYZ, 0, 1);
	checkAndOut(XYZ, 1, 0);
	XYZ--;
	checkAndOut(1, 1, XYZ);
	checkAndOut(1, XYZ, 1);
	checkAndOut(XYZ, 1, 1);
}

int main() {
	I >> n;
	for (i = 0; i < n; i++) {
		I >> B[i];
		S += B[i];
	}
	if (n == 3) {
		return O << 1 << endl << 1 << endl << B[0] - 2, 0;
	}
	if (n % 3) {
		return solve(), 0;
	}
	solve3();
}