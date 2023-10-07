#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
vector<vector<int>> g;
vector<pair<int, int>> rib;
map<pair<int, int>, int> point2id;
vector<int> color;
int m, a, b, n = -1;

void paint(int col) {
	vector<pair<int, int>> paint_order;
	for (int i = 0; i < n; i++) {
		if (color[i] == 0) {
			int adjacent_not_painted_cnt = 0;
			for (int j = 0; j < (int)g[i].size(); j++) {
				if (color[g[i][j]] == 0) {
					adjacent_not_painted_cnt++;
				}
			}
			paint_order.push_back(make_pair(adjacent_not_painted_cnt, i));
		}
	}
	if (paint_order.size() == 0) {
		return;
	}
	sort(paint_order.begin(), paint_order.end());
	reverse(paint_order.begin(), paint_order.end());
	for (int i = 0; i < (int)paint_order.size(); i++) {
		int v = paint_order[i].second;
		bool can_paint = true;
		for (int j = 0; j < (int)g[v].size(); j++) {
			int adjacent = g[v][j];
			if (color[adjacent] == col) {
				can_paint = false;
			}
		}
		if (can_paint) {
			color[v] = col;
		}
	}
}

int main() {
	cin >> m;
	while (m--) {
		cin >> a >> b;
		if (point2id.count(make_pair(a, b)) == 0) {
			n++;
			point2id[make_pair(a, b)] = n;
		}
		int u = point2id[make_pair(a, b)];
		cin >> a >> b;
		if (point2id.count(make_pair(a, b)) == 0) {
			n++;
			point2id[make_pair(a, b)] = n;
		}
		int v = point2id[make_pair(a, b)];
		rib.push_back(make_pair(u, v));
	}
	n++;
	g.resize(n);
	color.resize(n);
	for (int i = 0; i < (int)rib.size(); i++) {
		g[rib[i].first].push_back(rib[i].second);
		g[rib[i].second].push_back(rib[i].first);
	}
	paint(1);
	paint(2);
	paint(3);
	paint(4);
	paint(5);
	for (map<pair<int, int>, int>::iterator it = point2id.begin(); it != point2id.end(); it++) {
		cout << it->first.first << " " << it->first.second << " " << color[it->second] << endl;
	}
}