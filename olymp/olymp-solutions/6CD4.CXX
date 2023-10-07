#include<fstream>
#include<vector>
using namespace std;
string S[3];
int n, k, q;

int main() {
	ifstream I("input.txt");
	ofstream O("output.txt");
	I >> q;
	while (q--) {
		I >> n >> k >> S[0] >> S[1] >> S[2];
		bool p[3];
		for (int i = 0; i < 3; i++) {
			S[i].push_back('.');
			S[i].push_back('.');
			S[i].push_back('.');
			S[i].push_back('.');
			p[i] = (S[i][0] == 's');
			if (S[i][1] != '.') p[i] = false;
		}
		int j = 1;
		while (j < n) {
			bool pp[3] = { false, false, false };
			for (int i = 0; i < 3; i++)
				if ((i != 0 && p[i - 1]) || p[i] || (i != 2 && p[i + 1])) {
					pp[i] = true;
					for (int x = j; x <= j + 3; x++)
						if (S[i][x] != '.') pp[i] = false;
				}
			copy(pp, pp + 3, p);
			j += 3;
		}
		O << (p[0] || p[1] || p[2] ? "YES" : "NO") << endl;
	}
}