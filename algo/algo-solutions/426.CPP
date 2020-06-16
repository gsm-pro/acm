#include<iostream>
#define N 300003
using namespace std;
pair<int, int> parent[N];

void make_set(int v) {
	parent[v] = make_pair(v, 0);
}

pair<int, int> find_set(int v) {
	if (v != parent[v].first) {
		int len = parent[v].second;
		parent[v] = find_set(parent[v].first);
		parent[v].second += len;
	}
	return parent[v];
}

void unite_sets(int a, int b) {
	a = find_set(a).first;
	b = find_set(b).first;
	if (a != b) {
		parent[b] = make_pair(a, 1);
	}
}

int main() {
	int n, m, t, a, b, c;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		make_set(i);
	}
	while (m--) {
		cin >> t;
		if (t == 1) {
			cin >> a >> b;
			unite_sets(b, a);
		}
		if (t == 2) {
			cin >> c;
			cout << find_set(c).second << endl;
		}
	}
}