#include<iostream>
#include<queue>
using namespace std;
int used[24][60] = { 0 };
queue<pair<int, pair<int, int>>> q;

int addm(int x, int y) {
	return (x + y) % 60;
}

int addh(int x, int y) {
	return (x + y) % 24;
}

int main() {
	int a1, b1, a2, b2, h1, m1, h2, m2;
	cin >> a1 >> b1 >> a2 >> b2 >> h1 >> m1 >> h2 >> m2;
	q.push(make_pair(0, make_pair(h1, m1)));
	while (!q.empty()) {
		pair<int, pair<int, int>> p = q.front();
		q.pop();
		int h = p.second.first, m = p.second.second, c = p.first;
		if (h == h2 && m == m2) {
			cout << c;
			return 0;
		}
		if (!used[addh(h, a1)][addm(m, b1)]) {
			used[addh(h, a1)][addm(m, b1)] = 1;
			q.push(make_pair(c + 1, make_pair(addh(h, a1), addm(m, b1))));
		}
		if (!used[addh(h, a2)][addm(m, b2)]) {
			used[addh(h, a2)][addm(m, b2)] = 1;
			q.push(make_pair(c + 1, make_pair(addh(h, a2), addm(m, b2))));
		}
	}
	cout << -1;
}