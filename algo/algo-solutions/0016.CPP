#include<cstdio>
#include<bitset>
#define ULL unsigned long long
#define FN 10
#define B 29993970
#define M1 29866219ULL
#define M2 29993969ULL
std::bitset<B> b;
char s[16];
ULL h[FN];
ULL d[FN] = { 31ULL, 37ULL, 53ULL, 67ULL, 89ULL, 103ULL, 127ULL, 137ULL, 139ULL, 1009ULL };
ULL m[FN] = { M1, M2, M1, M2, M1, M2, M1, M2, M1, M2 };

int main() {
	gets_s(s);
	int n = atoi(s);
	while (n--) {
		gets_s(s);
		int len = (int)strlen(s);
		for (int i = 0; i < FN; i++) {
			h[i] = 0ULL;
		}
		for (int j = 1; j < len; j++) {
			ULL c = 1ULL * (s[j] - 'a' + 1);
			for (int i = 0; i < FN; i++) {
				h[i] = (h[i] * d[i] + c) % m[i];
			}
		}
		if (s[0] == '+') {
			for (int i = 0; i < FN; i++) {
				b.set((int)h[i]);
			}
		}
		if (s[0] == '?') {
			bool ans = true;
			for (int i = 0; (i < FN) && ans; i++) {
				ans &= b.test((int)h[i]);
			}
			putchar(ans ? '1' : '0');
		}
	}
}