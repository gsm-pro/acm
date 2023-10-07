#include<fstream>
#include<string>
using namespace std;
string s, part;
int c[60];

int main() {
	ifstream("input.txt") >> s >> part;
	int n = (int)s.size(), m = (int)part.size(), k = 1;
	for (int i = 0; i < n; i++) c[s[i]]++;
	for (int i = 0; i < m; i++) c[part[i]]--;
	if (n < 11) k = n - 1;
	else if (n < 102) k = n - 2;
	else if (n < 1003) k = n - 3;
	else if (n < 10004) k = n - 4;
	else if (n < 100005) k = n - 5;
	else if (n < 1000006) k = n - 6;
	while (k > 0) {
		int r = k % 10;
		c[r + 48]--;
		k = k / 10;
	}
	string ans = "", _ans = part;
	for (int i = '0'; i <= '9'; i++)
		for (int j = 1; j <= c[i]; j++) _ans.push_back(i);
	for (int i = '1'; i <= '9'; i++)
		if (c[i] > 0) {
			ans.push_back(char(i)), c[i]--;
			break;
		}
	for (int i = '0'; i <= '9'; i++) {
		string w = "";
		for (int j = 1; j <= c[i]; j++) w.push_back(i);
		if (part[0] == i) {
			if (part + w < w + part)
				ans += part + w;
			else
				ans += w + part;
		}
		else ans += w;
	}
	if (ans[0] == '0' || (_ans[0] != '0' && _ans < ans)) ans = _ans;
	ofstream("output.txt") << ans;
}