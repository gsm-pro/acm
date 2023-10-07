#include<fstream>
#include<string>
#include<vector>
using namespace std;
vector<string> ans;
string s;
int i, j, k, n;

void f(string d) {
	for (k = 0; k < 8; k++) {
		s = { d[k] };
		ans.push_back(s + (" " + to_string((d[k] == 'H') ? i : j)));
	}
}

int main() {
	ifstream I("input.txt");
	ofstream O("output.txt");
	I >> n;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++) {
			I >> s;
			if (s[1] == '1')
				if (s[0] == '0') f("HHHVVHVV"); else
					if (s[2] == '0') f("VHHHVHVV"); else
						if (s[3] == '0') f("HVHHHVVV"); else
							if (s[4] == '0') f("HHVHVHVV"); else
								if (s[5] == '0') f("HHHVHVVV"); else
									return O << "NO", 0;
		}
	O << "YES" << endl << (n = (int)ans.size()) << endl;
	for (k = 0; k < n; k++) O << ans[k] << endl;
}