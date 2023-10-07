#include<fstream>
#include<vector>
#include<set>
#include<algorithm>
#include<chrono>
#include<random>
#include<cassert>
using namespace std;
vector<vector<int>> g;
vector<int> root_candidates;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int n, m, k = 0, paths_counter;

int dfs(int p, int cur, int prev = -1) {
	if (g[cur].size() == 1 && prev != -1) return 1;
	multiset<int> children, unpaired;
	for (int nxt : g[cur])
		if (nxt != prev) children.insert(dfs(p, nxt, cur));
	if (children.count(p)) {
		paths_counter += children.count(p);
		children.erase(p);
	}
	if (children.empty()) return prev != -1;
	auto ptrR = --children.end();
	while (children.size() >= 2) {
		int rValue = *ptrR, lValue = p - rValue;
		children.erase(ptrR);
		auto ptrL = children.lower_bound(lValue);
		if (!children.count(lValue))
			if (ptrL == children.end() || ptrL != children.begin()) ptrL--;
		if (*ptrL + rValue <= p)
			paths_counter++, children.erase(ptrL);
		else
			unpaired.insert(rValue);
		if (children.size()) ptrR = --children.end();
	}
	if (children.size()) unpaired.insert(*children.begin());
	if (!unpaired.size()) return prev != -1;
	if (prev != -1) paths_counter += (unpaired.size() - 1);
	return *unpaired.begin() + (prev != -1);
}

int run_dfs(int p) {
	paths_counter = 0;
	int root_path_piece = dfs(p, root_candidates[rng() % root_candidates.size()]);
	if (root_path_piece > 0) paths_counter++;
	assert(paths_counter >= k);
	return paths_counter == k;
}

using f_type = int(*)(int);
template<f_type F>
struct f_iter {
	using iterator_category = forward_iterator_tag;
	using difference_type = size_t;
	using value_type = int;
	using pointer = int*;
	using reference = int&;
	int index;
	f_iter(int index) : index(index) {}

	f_iter& operator ++ () {
		++index;
		return *this;
	}

	int operator * () {
		return F(index);
	}

	bool operator != (const f_iter& other) {
		return index != other.index;
	}

	bool operator == (const f_iter& other) {
		return index == other.index;
	}

	bool operator < (const f_iter& other) {
		return index < other.index;
	}
};

template<f_type F>
pair<f_iter<F>, f_iter<F>> f_range(int begin, int end) {
	return { {begin}, {end} };
}

int main() {
	ifstream I("input.txt");
	I >> n >> m;
	g.resize(n);
	for (int i = 0, u, v; i < m; i++) {
		I >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 0; i < n; i++) {
		if (g[i].size() & 1) k++;
		if (g[i].size() == 1) root_candidates.push_back(i);
	}
	k /= 2;
	auto x = f_range<run_dfs>(m / k, n - 1);
	ofstream("output.txt") << n * k + lower_bound(x.first, x.second, 1).index;
}