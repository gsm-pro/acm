#include<fstream>
using namespace std;
#define P 1000000007
int i, j, x, n, m, p[500050] = { 1 }, a[10000010], f[10000010];
__int64 ans = 0, y;

int main() {
	ifstream I("input.txt");
	I >> n;
	for (i = 1; i <= n; i++) p[i] = (p[i - 1] << 1) % P;
	for (i = 1; i <= n; i++) {
		I >> x;
		m = max(m, x);
		a[x]++;
	}
	for (i = m; i > 1; i--) {
		x = a[i], y = 0;
		for (j = i + i; j <= m; j += i) y += f[j], x += a[j];
		f[i] = ((p[x] - 1LL) * (n - x) - y) % P;
		ans += f[i] += f[i] >> 31 & P;
	}
	ofstream("output.txt") << ans % P;
}