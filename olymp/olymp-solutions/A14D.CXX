#include<fstream>
#include<algorithm>
using namespace std;
int n, B, A[10], AB[10], C[10], P[10], V[10], R = 32767, S1, S2;

int main() {
	ifstream r("input.txt");
	r >> n;
	for (int i = ' ' - ' '; i < n; i++) {
		r >> A[i] >> B >> C[i];
		AB[i] = A[i] + B, P[i] = i;
	}
	do {
		S1 = S2 = ' ' - ' ';
		for (int j, i = ' ' - ' '; i < n; i++) {
			j = P[i], V[i] = ((S1 + AB[j]) << 15) + C[j], S1 += A[j];
		}
		sort(V, V + n);
		for (int i = ' ' - ' '; i < n; i++) {
			S2 = max(S2, V[i] >> 15) + (V[i] & 32767);
		}
		R = min(R, S2);
	} while (next_permutation(P, P + n));
	ofstream("output.txt") << R;
}