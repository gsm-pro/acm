#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<stack>
using namespace std;
#define INF 77
const int dx[8] = { -1, -1,  1, 1, -1, 1,  0, 0 };
const int dy[8] = { -1,  1, -1, 1,  0, 0, -1, 1 };
int answer = INF, w_moves = 0;
stack<int> w_moves_index;

inline int dist(int x1, int y1, int x2, int y2) {
	return max(abs(x2 - x1), abs(y2 - y1));
}

inline bool check(int x, int y) {
	return x > 0 && y > 0 && x < 9 && y < 9;
}

void play(int xw, int yw, int xb, int yb, int w_move, bool who) {
	if (w_move > w_moves) {
		return;
	}
	if (who) {
		int minDist = INF;
		for (int i = 0; i < 8; i++) {
			if (check(xw + dx[i], yw + dy[i])) {
				if (minDist >= dist(xw + dx[i], yw + dy[i], xb, yb)) {
					minDist = dist(xw + dx[i], yw + dy[i], xb, yb);
				}
			}
		}
		if (minDist == 0) {
			answer = min(answer, w_move);
			return;
		}
		for (int i = 0; i < 8; i++) {
			if (check(xw + dx[i], yw + dy[i]) && dist(xw + dx[i], yw + dy[i], xb, yb) == minDist) {
				w_moves_index.push(i);
				play(xw + dx[i], yw + dy[i], xb, yb, w_move, false);
				w_moves_index.pop();
			}
		}
	}
	else {
		int maxDist = -INF;
		bool sameAsW = false;
		for (int i = 0; i < 8; i++) {
			if (check(xb + dx[i], yb + dy[i])) {
				if (maxDist <= dist(xw, yw, xb + dx[i], yb + dy[i])) {
					maxDist = dist(xw, yw, xb + dx[i], yb + dy[i]);
				}
			}
		}
		if (check(xb + dx[w_moves_index.top()], yb + dy[w_moves_index.top()])) {
			if (maxDist == dist(xw, yw, xb + dx[w_moves_index.top()], yb + dy[w_moves_index.top()])) {
				sameAsW = true;
			}
		}
		if (sameAsW) {
			play(xw, yw, xb + dx[w_moves_index.top()], yb + dy[w_moves_index.top()], w_move + 1, true);
		}
		else {
			for (int i = 0; i < 8; i++) {
				if (check(xb + dx[i], yb + dy[i]) && dist(xw, yw, xb + dx[i], yb + dy[i]) == maxDist) {
					play(xw, yw, xb + dx[i], yb + dy[i], w_move + 1, true);
				}
			}
		}
	}
}

int main() {
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
	char c1, c2, c3, c4;
	cin >> c1 >> c2 >> c3 >> c4;
	int xw = c1 - 'a' + 1, yw = c2 - '0', xb = c3 - 'a' + 1, yb = c4 - '0';
	if (xb < xw && yb < yw) {
		w_moves = dist(xw, yw, 1, 1);
	}
	if (xb < xw && yb > yw) {
		w_moves = dist(xw, yw, 1, 8);
	}
	if (xb == xw && yb < yw) {
		w_moves = max(dist(xw, yw, 1, 1), dist(xw, yw, 8, 1));
	}
	if (xb == xw && yb > yw) {
		w_moves = max(dist(xw, yw, 1, 8), dist(xw, yw, 8, 8));
	}
	if (xb > xw && yb < yw) {
		w_moves = dist(xw, yw, 8, 1);
	}
	if (xb > xw && yb > yw) {
		w_moves = dist(xw, yw, 8, 8);
	}
	if (xb > xw && yb == yw) {
		w_moves = max(dist(xw, yw, 8, 8), dist(xw, yw, 8, 1));
	}
	if (xb < xw && yb == yw) {
		w_moves = max(dist(xw, yw, 1, 8), dist(xw, yw, 1, 1));
	}
	play(xw, yw, xb, yb, 1, true);
	cout << answer;
}