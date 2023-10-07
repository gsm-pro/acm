#include<fstream>
#include<algorithm>
using namespace std;
int Q, N, X[110], Z[110];

int R(int A) {
	if (A == N) return 0;
	if (Z[A] != -10000000) return Z[A];
	return Z[A] = max(X[A] + R(A + 1), A + 1 < N ? X[A] * X[A + 1] + R(A + 2) : -10000000);
}

int main() {
	ifstream I("input.txt");
	I >> N;
	for (int Q = 0; Q < N; Q++) I >> X[Q];
	sort(X, X + N);
	fill(Z, Z + N, -10000000);
	ofstream("output.txt") << R(0);
}