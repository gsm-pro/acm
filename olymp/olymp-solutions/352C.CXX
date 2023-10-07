#include<fstream>
using namespace std;
unsigned D[2][2000002], L[2][2000002], $$$, i, j, cur, pre, a, b, c, dd, ll;
string $, $$;

signed main() {
	ifstream("input.txt") >> $ >> $$ >> $$$;
	while (++i <= $$.size()) {
		D[cur = i & 1][0] = i, L[cur][0] = 0;
		for (j = 1; j <= $.size(); j++) {
			if ((c = D[pre][j - 1] + ($[j - 1] != $$[i - 1])) <= min(a = D[pre = cur ^ 1][j], b = D[cur][j - 1]) + 1)
				dd = c, ll = L[pre][j - 1] + 1;
			else if (b <= a)
				dd = b + 1, ll = L[cur][j - 1] + 1;
			else
				dd = a + 1, ll = L[pre][j];
			D[cur][j] = dd, L[cur][j] = ll;
		}
	}
	for (i = 1; i <= $.size(); i++)
		if (D[cur][i] <= $$$) return ofstream("output.txt") << i - L[cur][i] << " " << L[cur][i], 0;
}