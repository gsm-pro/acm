#include<cstdio>
int v[100001], i = 0, n, a;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	while (i < 2 * n && scanf("%d", &a))
		i++ < n ? v[a % n] = i : printf("%d ", v[a % n]);
}