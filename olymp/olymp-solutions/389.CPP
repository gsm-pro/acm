#include<fstream>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;
typedef pair<int, int> PII;
typedef pair<PII, int> PIII;
typedef pair<PII, PII> PPII;
#define MP make_pair
#define MPP(a,b,c,d) MP(MP(a,b),MP(c,d))
ifstream I("input.txt");
ofstream O("output.txt");
set<PIII> hCut, vCut;
map<PPII, int> rect2Id;
vector<vector<int>> g;
int ans = 0;

int dfs(int v) {
	if (g[v].size() == 0) {
		return 1;
	}
	int res = 0;
	for (size_t i = 0; i < g[v].size(); i++) {
		int to = g[v][i];
		res += dfs(to);
	}
	ans += res;
	return res;
}

int main() {
	int W, H, N, x1, y1, x2, y2;
	I >> N >> W >> H;
	vector<PPII> rects;
	rects.push_back(MPP(0, 0, W, H));
	rect2Id[MPP(0, 0, W, H)] = 0;
	hCut.insert(MP(MP(0, W), 0));
	hCut.insert(MP(MP(0, W), H));
	vCut.insert(MP(MP(0, H), 0));
	vCut.insert(MP(MP(0, H), W));
	g.resize(2 * N + 1);
	for (int i = 1; i <= N; i++) {
		I >> x1 >> y1 >> x2 >> y2;
		if (x1 == x2 && y1 == y2) {
			continue;
		}
		int indexFrom = -1, x_left = -1, x_right = -1, y_bottom = -1, y_top = -1;
		if (x1 == x2) {
			if (y2 < y1) {
				swap(y1, y2);
			}
			y_bottom = y1, y_top = y2;
			for (int x = x1 - 1; x >= 0; x--) {
				PIII p = MP(MP(y_bottom, y_top), x);
				if (vCut.count(p)) {
					x_left = x;
					break;
				}
			}
			for (int x = x1 + 1; x <= W; x++) {
				PIII p = MP(MP(y_bottom, y_top), x);
				if (vCut.count(p)) {
					x_right = x;
					break;
				}
			}
			hCut.insert(MP(MP(x_left, x1), y_bottom));
			hCut.insert(MP(MP(x1, x_right), y_bottom));
			hCut.insert(MP(MP(x_left, x1), y_top));
			hCut.insert(MP(MP(x1, x_right), y_top));
			vCut.insert(MP(MP(y_bottom, y_top), x1));
		}
		if (y1 == y2) {
			if (x2 < x1) {
				swap(x1, x2);
			}
			x_left = x1, x_right = x2;
			for (int y = y1 - 1; y >= 0; y--) {
				PIII p = MP(MP(x_left, x_right), y);
				if (hCut.count(p)) {
					y_bottom = y;
					break;
				}
			}
			for (int y = y1 + 1; y <= H; y++) {
				PIII p = MP(MP(x_left, x_right), y);
				if (hCut.count(p)) {
					y_top = y;
					break;
				}
			}
			vCut.insert(MP(MP(y_bottom, y1), x_left));
			vCut.insert(MP(MP(y1, y_top), x_left));
			vCut.insert(MP(MP(y_bottom, y1), x_right));
			vCut.insert(MP(MP(y1, y_top), x_right));
			hCut.insert(MP(MP(x_left, x_right), y1));
		}
		if (x_left == -1 || x_right == -1 || y_bottom == -1 || y_top == -1) {
			throw;
		}
		indexFrom = rect2Id[MPP(x_left, y_bottom, x_right, y_top)];
		rects.push_back(MPP(x_left, y_bottom, x2, y2));
		int indexTo1 = rects.size() - 1;
		rect2Id[MPP(x_left, y_bottom, x2, y2)] = indexTo1;
		rects.push_back(MPP(x1, y1, x_right, y_top));
		int indexTo2 = rects.size() - 1;
		rect2Id[MPP(x1, y1, x_right, y_top)] = indexTo2;
		g[indexFrom].push_back(indexTo1);
		g[indexFrom].push_back(indexTo2);
	}
	dfs(0);
	O << ans;
}