#include<fstream>
#include<algorithm>
#include<string>
#include<vector>
#define LL long long
using namespace std;
ifstream I("input.txt");
ofstream O("output.txt");
int MOD = 1000000007;
vector<LL> X, H;
string s;

bool check(int l1, int l2, int l3) {
	if (max(l1, l2) > l3) return false;
	int p1 = l1 + l2 + l3 - 1, p2 = l2 + l3 - 1, p3 = l3 - 1;
	if ((s[p3] == '0' && l3 > 1) || (s[p2] == '0' && l2 > 1)) return false;
	if ((H[p3] * X[p2 + 1]) % MOD == (((H[p2] - H[p3] + MOD) * X[p2 - p3]) % MOD + H[p1] - H[p2] + MOD) % MOD) {
		reverse(s.begin(), s.end());
		for (int i = 0; i < l1; i++) O << s[i];
		O << '+';
		for (int i = l1; i < l1 + l2; i++) O << s[i];
		O << '=';
		for (int i = l1 + l2; i < l1 + l2 + l3; i++) O << s[i];
		return true;
	}
	return false;
}

int main() {
	I >> s;
	reverse(s.begin(), s.end());
	int n = s.size();
	X.resize(n, 1);
	H.resize(n, s[0] - '0');
	for (int i = 1; i < n; i++) X[i] = (X[i - 1] * 10) % MOD, H[i] = (H[i - 1] + X[i] * (s[i] - '0')) % MOD;
	for (int l3 = 1; l3 < n; l3++) {
		if (check(l3, n - 2 * l3, l3)) break;
		if (check(l3 - 1, n - 2 * l3 + 1, l3)) break;
		if (check(n - 2 * l3, l3, l3)) break;
		if (check(n - 2 * l3 + 1, l3 - 1, l3)) break;
	}
}