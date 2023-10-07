#include<fstream>
#include<string>
using namespace std;
string A[111111];
int n, nxt;

inline int calc(int i) {
	int res = 0;
	for (int j = 0; j < A[i].size(); j++)
		res = A[i][j] != '?' ? res * 10 + (A[i][j] - '0') : res = res * 10 + 9;
	return res;
}

int main() {
	ifstream I("input.txt");
	ofstream O("output.txt");
	I >> n;
	for (int i = 1; i <= n; i++) I >> A[i];
	for (int i = 1; i <= n; i++) {
		if (calc(i) <= nxt) return O << "NO", 0;
		for (int j = 0; j < A[i].size(); j++) {
			if (A[i][j] != '?')	continue;
			for (int h = 0; h <= 9; h++)
				if (h || j) {
					A[i][j] = h + '0';
					if (calc(i) > nxt) break;
				}
		}
		nxt = calc(i);
	}
	O << "YES" << endl;
	for (int i = 1; i <= n; i++) O << A[i] << endl;
}