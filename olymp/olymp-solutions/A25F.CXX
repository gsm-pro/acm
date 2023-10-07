#include<fstream>
#include<set>
using namespace std;
ifstream I("input.txt");
ofstream O("output.txt");
int maxv[200002], curv[200002];
set<int> partials;
int n, q, type, num, add;

int main() {
	I >> n;
	for (int i = 1; i <= n; i++) {
		partials.insert(i);
		I >> maxv[i];
	}
	I >> q;
	while (q--) {
		I >> type;
		if (type == 1) {
			I >> num >> add;
			auto it = partials.lower_bound(num);
			while (it != partials.end()) {
				curv[*it] += add;
				if (curv[*it] < maxv[*it]) break;
				if (curv[*it] == maxv[*it]) {
					partials.erase(it);
					break;
				}
				add = curv[*it] - maxv[*it];
				curv[*it] = maxv[*it];
				partials.erase(it);
				it = partials.lower_bound(num);
			}
		}
		else {
			I >> num;
			O << curv[num] << "\n";
		}
	}
}