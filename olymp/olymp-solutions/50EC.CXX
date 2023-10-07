#include<fstream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
map<char, vector<int>> let;
string s, ans = "|";

int main() {
	ifstream("input.txt") >> s;
	int n = (int)s.length();
	for (int i = 0; i < n; i++) let[s[i]].push_back(i);
	int k = (int)let.size(), minlength = 200;
	for (int start = 0; start < n; start++) {
		auto it = let.begin();
		vector<int> index;
		for (int c = 0, cur = start; c < k; c++) {
			auto it2 = lower_bound(it->second.begin(), it->second.end(), cur);
			if (it2 == it->second.end()) break;
			index.push_back(cur = *it2);
			it++;
		}
		if (index.size() == k) {
			int pos = index.back();
			if (pos - start <= minlength) {
				minlength = pos - start;
				index.clear();
				auto it2 = --let.end();
				while (index.size() < k) {
					if (it2->first == s[pos]) index.push_back(pos), it2--;
					pos--;
				}
				string t = s;
				for (int i = 0; i < n; i++)
					if (find(index.begin(), index.end(), i) == index.end()) t[i] = '.';
				ans = min(ans, t);
			}
		}
	}
	ofstream("output.txt") << (ans == "|" ? "-" : ans);
}