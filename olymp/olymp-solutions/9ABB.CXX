#include<iostream>
#include<map>
using namespace std;
int a[200020], b[200020], c[200020], p;
pair<int, int> ans = { -1, -1 }, t;
map<int, int> M;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, m;
	scanf("%d", &n);
	for (int i = 1, x; i <= n; i++) {
		scanf("%d", &x);
		M[x]++;
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) scanf("%d", b + i);
	for (int i = 1; i <= m; i++) scanf("%d", c + i);
	for (int i = 1; i <= m; i++) {
		t = make_pair(M[b[i]], M[c[i]]);
		if (ans < t) ans = t, p = i;
	}
	cout << p;
}