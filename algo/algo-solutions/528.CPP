#include<iostream>
#include<string>
#define forn(i, n) for(int i=0;i<int(n);i++)
#define NMAX 16400
using namespace std;
int n, m, c[NMAX << 1], ans = 0, x, y, cur, nxt;
string s, s_hex;

inline int leader(int idx) {
	if (c[idx] != idx) c[idx] = leader(c[idx]);
	return c[idx];
}

inline void unite(int a, int b) {
	a = leader(a), b = leader(b), c[b] = a;
}

int main() {
	memset(c, -1, sizeof c);
	cin >> n >> m;
	forn(i, n + 1) {
		cur = i & 1;
		nxt = cur ^ 1;
		if (i < n) {
			cin >> s_hex;
			s = "";
			for (int j = 0; j < (int)s_hex.size(); j++) {
				if (s_hex[j] == '0') s += "0000";
				if (s_hex[j] == '1') s += "0001";
				if (s_hex[j] == '2') s += "0010";
				if (s_hex[j] == '3') s += "0011";
				if (s_hex[j] == '4') s += "0100";
				if (s_hex[j] == '5') s += "0101";
				if (s_hex[j] == '6') s += "0110";
				if (s_hex[j] == '7') s += "0111";
				if (s_hex[j] == '8') s += "1000";
				if (s_hex[j] == '9') s += "1001";
				if (s_hex[j] == 'A') s += "1010";
				if (s_hex[j] == 'B') s += "1011";
				if (s_hex[j] == 'C') s += "1100";
				if (s_hex[j] == 'D') s += "1101";
				if (s_hex[j] == 'E') s += "1110";
				if (s_hex[j] == 'F') s += "1111";
			}
		}
		forn(j, m) {
			x = cur * m + j, y = nxt * m + j;
			c[x] = -1;
			if (i < n && s[j] == '1') {
				c[x] = x;
				if (j != 0 && c[x - 1] != -1) unite(x - 1, x);
				if (i != 0 && c[y] != -1) unite(x, y);
			}
		}
		forn(j, m) {
			x = cur * m + j;
			if (c[x] != -1) {
				leader(x);
			}
		}
		forn(j, m) {
			y = nxt * m + j;
			if (c[y] != -1 && leader(y) == y) {
				ans++;
			}
		}
	}
	cout << ans;
}