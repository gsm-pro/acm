#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<vector>
using namespace std;

vector<int> mul(vector<int> &a, vector<int> &b) {
	vector<int> res(a.size());
	for (size_t i = 0; i < a.size(); i++) {
		res[i] = a[b[i]];
	}
	return res;
}

void main() {
	int n, x;
	long long exponent;
	scanf("%d%I64d", &n, &exponent);
	std::vector<int> base(n), res(n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		base[i] = x;
		res[x] = x;
	}
	while (exponent > 0) {
		if (exponent & 1) {
			res = mul(res, base);
		}
		exponent >>= 1LL;
		base = mul(base, base);
	}
	for (int i = 0; i < n; i++) {
		printf("%d ", res[i]);
	}
}