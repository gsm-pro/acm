#include<iostream>
#include<algorithm>
using namespace std;
int a[110011], b[110011], n;

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		scanf_s("%d", &a[i]);
	}
	for (int i = 0; i < n; i++) {
		scanf_s("%d", &b[i]);
	}
	sort(a, a + n);
	sort(b, b + n);
	__int64 u = 0, v = 0;
	for (int i = 0; i < n; i++) {
		u += abs(a[i] - b[i]);
		v += abs(a[i] - b[n - i - 1]);
	}
	cout << u << " " << v;
}