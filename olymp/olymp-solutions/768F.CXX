#include<fstream>
#include<vector>
#include<string>
using namespace std;
vector<int> pi;
string s;
int n, i, kk, j;
__int64 M = 1000000007L, k, ans, x;

int main() {
	ifstream("input.txt") >> k >> s;
	s = s + s;
	pi.assign(n = (int)s.length(), 0);
	for (i = 1; i < n; i++, j = pi[i - 1]) {
		while (j > 0 && s[i] != s[j]) j = pi[j - 1];
		if (s[i] == s[j]) j++;
		pi[i] = j;
	}
	n >>= 1;
	if (n % (kk = n - pi[n - 1]) == 0) k = k * (n / kk), n = kk;
	for (i = 0; i < n; i++) ans += pi[i];
	if (k > 1) for (i = n; i < 2 * n; i++) ans += (pi[i] - i + n - 1);
	x = (k - 1) * n % M;
	x = x * (x + 1) / 2 % M;
	ofstream("output.txt") << (ans % M + x) % M;
}