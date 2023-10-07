#include<fstream>
using namespace std;
int n, i, len = 0, ans = 0;
bool f = true;
string s;

int main() {
	ifstream("input.txt") >> n >> s;
	s += s;
	for (i = 0; i < 2 * n; i++) {
		if (i < n && s[i] == '0') f = false;
		if (s[i] == '1') len++, ans = max(ans, len); else len = 0;
	}
	ofstream("output.txt") << (f ? n : ans);
}