#include<fstream>
#include<vector>
using namespace std;
int x[1010], z[1010][2], n, ans = 0;

inline int f(int p, int q) {
	return p == 0 ? 0 : q == 0 ? 2000000001 : x[p] < x[q] ? x[q] - x[p] : x[p] - x[q];
}

int main() {
	ifstream I("input.txt");
	I >> n;
	int pre = n & 1, cur = pre ^ 1;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) z[j][cur] = f(-1, 0);
		if (i > 0) I >> x[i];
		if (i > 1) ans += f(i, i - 1);
	}
	for (int j = 0; j < n; j++) z[j][pre] = f(n, j);
	for (int i = n; i >= 1; i--) {
		cur ^= pre ^= cur ^= pre;
		for (int j = 0; j <= n; j++) z[j][pre] = f(-1, 0);
		for (int j = i - 1; j >= 0; j--) {
			if (j == i - 1)
				for (int k = 0; k <= max(j - 1, 0); k++)
					z[k][pre] = min(z[k][pre], z[j][cur] + f(k, i));
			else z[j][pre] = min(z[j][pre], z[j][cur] + f(i - 1, i));
		}
	}
	ofstream("output.txt") << min(ans, z[0][pre]);
}