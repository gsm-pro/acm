#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define MAXLEN 1000011
typedef long long LL;
const LL D = 1009LL;
char t[MAXLEN], p[MAXLEN], u[9], v[2 * MAXLEN];
vector<int> ans;
vector<LL> H, H_T, H_P;

vector<int> z_function(char s[MAXLEN]) {
	int n = (int)strlen(s);
	vector<int> z(n);
	for (int i = 1, l = 0, r = 0; i < n; ++i) {
		if (i <= r) {
			z[i] = min(r - i + 1, z[i - l]);
		}
		while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
			++z[i];
		}
		if (i + z[i] - 1 > r) {
			l = i, r = i + z[i] - 1;
		}
	}
	return z;
}

inline LL t_hash(int l, int r) {
	if (l == 0) {
		return H_T[r];
	}
	return H_T[r] - H_T[l - 1] * H[r - l + 1];
}

inline LL p_hash(int l, int r) {
	if (l == 0) {
		return H_P[r];
	}
	return H_P[r] - H_P[l - 1] * H[r - l + 1];
}

int main() {
	gets_s(t);
	int tlen = strlen(t);
	gets_s(p);
	int plen = strlen(p);
	gets_s(u);
	int k = atoi(u);
	if (plen > tlen) {
		puts("0");
		return 0;
	}
	for (int i = 0; i < MAXLEN; i++) {
		if (i) {
			H.push_back(H.back() * D);
		}
		else {
			H.push_back(1LL);
		}
	}
	LL h = 0;
	for (int i = 0; i < tlen; i++) {
		H_T.push_back(h * D + (LL)t[i]);
		h = H_T.back();
	}
	h = 0;
	for (int i = 0; i < plen; i++) {
		H_P.push_back(h * D + (LL)p[i]);
		h = H_P.back();
	}
	strcat(v, p);
	strcat(v, "$");
	strcat(v, t);
	vector<int> zf = z_function(v);
	zf.erase(zf.begin(), zf.begin() + (plen + 1));
	for (int start = 0; start <= (tlen - plen); start++) {
		int pos_to_check_equality_from_in_p = zf[start] + k;
		int pos_to_check_equality_from_in_t = start + pos_to_check_equality_from_in_p;
		int len_to_check = plen - k - zf[start];
		if (len_to_check <= 0) {
			ans.push_back(start + 1);
		}
		else {
			if (t_hash(pos_to_check_equality_from_in_t, pos_to_check_equality_from_in_t + len_to_check - 1) ==
				p_hash(pos_to_check_equality_from_in_p, pos_to_check_equality_from_in_p + len_to_check - 1)) {
				ans.push_back(start + 1);
			}
		}
	}
	printf("%d\n", (int)ans.size());
	for (int i = 0; i < (int)ans.size(); i++) {
		printf("%d ", ans[i]);
	}
}