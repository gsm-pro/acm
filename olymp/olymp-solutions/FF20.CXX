#include<fstream>
using namespace std;
ifstream I("input.txt");
int s[200200] = { 0 }, a, i, n, k, $ = -2100000000;

int main() {
	I >> n >> k;
	for (i = 1; i <= n; i++) I >> a, s[i] = s[i - 1] + a;
	for (i = 1; i <= n - k + 1; i++) $ = max($, s[n] - 2 * (s[i + k - 1] - s[i - 1]));
	ofstream("output.txt") << $;
}