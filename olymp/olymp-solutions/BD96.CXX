#include<fstream>
#include<vector>
using namespace std;
vector<int> v;
long long a[4444][4];

int main() {
	ifstream I("input.txt");
	ofstream O("output.txt");
	int n, i, j;
	long long x, y;
	I >> n;
	for (i = 0; i < n; i++)	I >> a[i][0] >> a[i][1] >> a[i][2];
	for (i = 0; i < n; i++)
		if (a[i][3] == 0LL) {
			x = a[i][0], y = 0;
			for (j = i + 1; j < n; j++) {
				if (a[j][3] != 0LL) continue;
				a[j][2] -= y, a[j][2] -= x, x--;
				if (a[j][2] < 0) a[j][3] = 1LL, y += a[j][1];
				x = max(x, 0LL);
			}
		}
	for (i = 0; i < n; i++)
		if (a[i][3] == 0) v.push_back(i + 1);
	O << v.size() << endl;
	for (auto l : v) O << l << " ";
}