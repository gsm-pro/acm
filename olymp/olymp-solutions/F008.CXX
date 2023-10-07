#include<fstream>
#include<vector>
using namespace std;
vector<vector<pair<int, bool>>> $;
vector<pair<int, int>> $$;
ofstream O("output.txt");
int v, e, f, c = 1;

void q() {
	O << "No solution";
	exit(0);
}

int main() {
	ifstream("input.txt") >> v >> e;
	if ((f = e - v + 1) <= 0) q();
	$.resize(f);
	for (int i = 1; i <= f - 1; i++, c++, v--) {
		$[i - 1].push_back(make_pair(c, false));
		$[i].push_back(make_pair(c, false));
	}
	e -= ((f == 1) ? 0 : (f == 2) ? 2 : (f - 1) * 2);
	for (int i = 0; i < f; i++) {
		int sz = (int)$[i].size();
		for (int j = sz + 1; j <= 3; j++, c++, v--, e--)
			$[i].push_back(make_pair(c, true));
	}
	if (v < 0 || e < 0 || e != v) q();
	int w = v, i = 0;
	while (true) {
		if ($[i].size() == 10 || w < 2) break;
		$[i].push_back(make_pair(c, false));
		$$.push_back(make_pair(c, c + 1));
		c += 2, w -= 2, i = (i + 1) % f;
	}
	while (true) {
		if ($[i].size() == 10 || w < 1) break;
		$[i].push_back(make_pair(c, false));
		c++, w--, i = (i + 1) % f;
	}
	if (w > 0) {
		for (int i = 0; i < f && w>0; i++)
			for (size_t j = 0; j < $[i].size() && w>0; j++)
				if ($[i][j].second) {
					$[i][j].second = false, w--;
					$$.push_back(make_pair($[i][j].first, c++));
				}
	}
	if (w != 0) q();
	O << f << "\n";
	for (int i = 0; i < f; i++) {
		O << $[i].size() << " ";
		for (size_t j = 0; j < $[i].size(); j++)
			O << $[i][j].first << " ";
		O << "\n";
	}
	O << $$.size() << "\n";
	for (size_t i = 0; i < $$.size(); i++)
		O << $$[i].first << " " << $$[i].second << "\n";
}