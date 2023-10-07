#include<fstream>
using namespace std;
int a[111], n, ans = 0;

int main() {
	ifstream I("input.txt");
	I >> n;
	for (int i = 1; i <= n; i++) I >> a[i];
	for (int i = 1; i <= n; i++)
		ans += ((a[i] == 1) || (a[i] == 0 && a[i + 1] == 1 && a[i - 1] == 1));
	ofstream("output.txt") << ans;
}