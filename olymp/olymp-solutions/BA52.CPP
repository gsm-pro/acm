#include<fstream>
#include<string>
#include<algorithm>
#define QMAX 500
#define INF 99999999
using namespace std;

struct Edge {
	int t, next;
} edge[QMAX];
int head[QMAX], total;

class CssRulesTask {
private:
	int col[QMAX], tag[QMAX], du[QMAX], dp[QMAX][8][8][8];

	void addEdge(int a, int b) {
		edge[total].t = b;
		edge[total].next = head[a];
		head[a] = total++;
	}

	int dfs(int id, int U, int I, int B) {
		if (head[id] == -1) {
			if (tag[id] == 1) {
				return U != col[id];
			}
			if (tag[id] == 2) {
				return I != col[id];
			}
			if (tag[id] == 3) {
				return B != col[id];
			}
		}
		if (dp[id][U][I][B] != -1) {
			return dp[id][U][I][B];
		}
		int ret = 0, add = INF;
		if (tag[id] == 1) {
			ret = (U != col[id]);
		}
		if (tag[id] == 2) {
			ret = (I != col[id]);
		}
		if (tag[id] == 3) {
			ret = (B != col[id]);
		}
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				for (int k = 0; k < 8; k++) {
					if ((U && !i) || (I && !j) || (B && !k)) {
						continue;
					}
					int cnt = (U != i) + (I != j) + (B != k);
					for (int l = head[id]; l != -1; l = edge[l].next) {
						cnt += dfs(edge[l].t, i, j, k);
					}
					add = min(cnt, add);
				}
			}
		}
		return dp[id][U][I][B] = ret + add;
	}

public:
	int getMinimalCssRulesCount(string x) {
		total = 0;
		memset(head, -1, sizeof head);
		memset(du, 0, sizeof du);
		memset(dp, -1, sizeof dp);
		int last[QMAX] = { 0 }, top = 0, id = 0, k = x.length();
		for (int i = 0; i < k; i++) {
			if (x[i] == '<' && x[i + 1] != '/') {
				id++;
				if (top != 0) {
					addEdge(last[top], id), du[id]++;
				}
				last[++top] = id;
				if (x[i + 1] == 'u') {
					tag[id] = 1;
				}
				if (x[i + 1] == 'i') {
					tag[id] = 2;
				}
				if (x[i + 1] == 'b') {
					tag[id] = 3;
				}
			}
			else {
				if (x[i] == '<' && x[i + 1] == '/') {
					top--;
				}
				else {
					if (x[i] == ':') {
						if (x[i + 1] == 'r') {
							col[id] = 1;
						}
						else {
							if (x[i + 1] == 'w') {
								col[id] = 2;
							}
							else {
								if (x[i + 1] == 'y') {
									col[id] = 3;
								}
								else {
									if (x[i + 1] == 'b' && x[i + 3] == 'a') {
										col[id] = 4;
									}
									else {
										if (x[i + 1] == 'b' && x[i + 3] == 'u') {
											col[id] = 5;
										}
										else {
											if (x[i + 1] == 'g' && x[i + 3] == 'a') {
												col[id] = 6;
											}
											else {
												col[id] = 7;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		int ans = 0;
		for (int i = 1; i <= id; i++) {
			if (du[i] == 0) {
				int mn = INF;
				for (int j = 0; j < 8; j++) {
					for (int k = 0; k < 8; k++) {
						for (int l = 0; l < 8; l++) {
							int add = (l != 0) + (j != 0) + (k != 0) + 1;
							for (int m = head[i]; m != -1; m = edge[m].next) {
								add += dfs(edge[m].t, j, k, l);
							}
							mn = min(mn, add);
						}
					}
				}
				ans += mn;
			}
		}
		return ans;
	}
};

int main() {
	CssRulesTask css;
	string s = "";
	ifstream r("input.txt");
	for (string str; getline(r, str);) {
		s += move(str);
	}
	ofstream("output.txt") << css.getMinimalCssRulesCount(s);
}