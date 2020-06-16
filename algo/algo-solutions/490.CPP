#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
#define NMAX 8
string s;
int field[NMAX][NMAX], n, m, bestAns = (1 << 7);
vector<pair<pair<int, int>, pair<int, int>>> allowedRects[NMAX][NMAX], addedRects, EMPTY;

inline bool cmp(const pair<pair<int, int>, pair<int, int>> &p1, const pair<pair<int, int>, pair<int, int>> &p2) {
	int sq1 = (p1.second.first - p1.first.first + 1) * (p1.second.second - p1.first.second + 1);
	int sq2 = (p2.second.first - p2.first.first + 1) * (p2.second.second - p2.first.second + 1);
	return sq1 > sq2;
}

inline bool isRectCoveredByRect(pair<pair<int, int>, pair<int, int>> &r, pair<pair<int, int>, pair<int, int>> &rect) {
	return !(r.first.first > rect.second.first ||
		r.second.first < rect.first.first ||
		r.first.second > rect.second.second ||
		r.second.second < rect.first.second);
}

inline bool isRectCoveredByRects(pair<pair<int, int>, pair<int, int>> &r) {
	for (int i = 0; i < (int)addedRects.size(); i++) {
		pair<pair<int, int>, pair<int, int>> rect = addedRects[i];
		if (isRectCoveredByRect(r, rect)) {
			return true;
		}
	}
	return false;
}

inline bool isPointCoveredByRect(pair<int, int> &p, pair<pair<int, int>, pair<int, int>> &rect) {
	return (p.first >= rect.first.first && p.first <= rect.second.first &&
		p.second >= rect.first.second && p.second <= rect.second.second);
}

inline bool isPointCoveredByRects(pair<int, int> &p) {
	for (int i = 0; i < (int)addedRects.size(); i++) {
		pair<pair<int, int>, pair<int, int>> rect = addedRects[i];
		if (isPointCoveredByRect(p, rect)) {
			return true;
		}
	}
	return false;
}

inline bool forbidden(pair<int, int> &p) {
	if (p.first > n) {
		return false;
	}
	if (field[p.first][p.second] == 1) {
		return true;
	}
	return isPointCoveredByRects(p);
}

inline pair<int, int> nxt(pair<int, int> &p) {
	int x = p.first, y = p.second;
	y++;
	if (y > m) {
		x++;
		y = 1;
	}
	return make_pair(x, y);
}

void rec(pair<int, int> p) {
	if ((int)addedRects.size() >= bestAns) {
		return;
	}
	pair<int, int> next = nxt(p);
	while (forbidden(next)) {
		next = nxt(next);
	}
	if (next.first > n) {
		bestAns = min(bestAns, (int)addedRects.size());
		return;
	}
	for (int q = 0; q < (int)allowedRects[next.first][next.second].size(); q++) {
		pair<pair<int, int>, pair<int, int>> rect = allowedRects[next.first][next.second][q];
		if (!isRectCoveredByRects(rect)) {
			addedRects.push_back(rect);
			rec(next);
			addedRects.pop_back();
		}
	}
}

int main() {
	cin >> n >> m;
	memset(field, 1, sizeof field);
	for (int i = 1; i <= n; i++) {
		cin >> s;
		for (int j = 1; j <= m; j++) {
			field[i][j] = (s[j - 1] == '.' ? 0 : 1);
		}
	}
	for (int top = 1; top <= n; top++) {
		for (int left = 1; left <= m; left++) {
			if (field[top][left] == 1) {
				allowedRects[top][left] = EMPTY;
				continue;
			}
			for (int bottom = top; bottom <= n; bottom++) {
				for (int right = left; right <= m; right++) {
					int forbidden = 0;
					for (int z1 = top; z1 <= bottom; z1++) {
						for (int z2 = left; z2 <= right; z2++) {
							forbidden += field[z1][z2];
						}
					}
					if (forbidden == 0) {
						allowedRects[top][left].push_back(make_pair(make_pair(top, left), make_pair(bottom, right)));
					}
				}
			}
		}
	}
	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= m; y++) {
			if (allowedRects[x][y].size() > 1) {
				sort(allowedRects[x][y].begin(), allowedRects[x][y].end(), cmp);
			}
		}
	}
	rec(make_pair(1, 0));
	cout << bestAns;
}