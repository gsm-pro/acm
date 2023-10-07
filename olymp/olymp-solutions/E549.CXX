#include<fstream>
#include<vector>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;
bool sortOrderFlag;

struct thing {
	int start, duration, finish, profit, number;

	bool operator < (const thing& o) const {
		return sortOrderFlag ?
			(number < o.number) :
			(profit != o.profit ? profit > o.profit : number < o.number);
	}
};

vector<thing> z[11][11];
map<__int64, bool> used;
map<thing, vector<int>> G, H;
map<thing, bool> US;
map<int, thing> MT;
int n, ans = 0;

auto hsh(vector<int>& s) {
	auto ans = 0LL;
	for (auto a : s) ans = ans * 20 + a;
	return ans;
}

bool kuhn(thing v) {
	if (US[v]) return false;
	US[v] = true;
	for (auto to : G[v]) {
		if (!MT.count(to) || kuhn(MT[to])) {
			MT[to] = v;
			return true;
		}
	}
	return false;
}

void process(vector<int>& s) {
	int time = 0, counter = 0, w = 0;
	H.clear();
	sortOrderFlag = true;
	for (auto a : s) {
		for (size_t i = 0; i < z[time][time + a].size() && i < (int)s.size(); i++)
			H[z[time][time + a][i]].push_back(counter);
		time += a, counter++;
	}
	G.clear();
	sortOrderFlag = false;
	for (auto th = H.begin(); th != H.end(); th++) G[th->first] = th->second;
	MT.clear();
	for (auto th = G.begin(); th != G.end(); th++) {
		US.clear();
		kuhn(th->first);
	}
	for (auto p = MT.begin(); p != MT.end(); p++) w += p->second.profit;
	ans = max(ans, w);
}

void bfs(vector<int> s) {
	queue<vector<int>> q;
	q.push(s);
	while (!q.empty()) {
		auto r = q.front();
		q.pop();
		process(r);
		for (size_t i = 0; i < r.size() - 1; i++) {
			auto rr = r;
			rr[i] += rr[i + 1];
			rr.erase(rr.begin() + (i + 1));
			auto hash = hsh(rr);
			if (!used.count(hash)) used[hash] = true, q.push(rr);
		}
	}
}

int main() {
	ifstream I("input.txt");
	I >> n;
	for (int i = 1, a, b, c, d; i <= n; i++) {
		I >> a >> b >> c >> d;
		for (int j = a; j <= c - b; j++) z[j][j + b].push_back({ a, b, c, d, i });
	}
	for (int i = 0; i < 11; i++)
		for (int j = i + 1; j < 11; j++)
			if (z[i][j].empty()) z[i][j].push_back({ i, j - i, j, 0, ++n });
			else sort(z[i][j].begin(), z[i][j].end(),
				[](auto& a, auto& b) { return a.profit > b.profit; });
	bfs({ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 });
	ofstream("output.txt") << ans;
}