#include<iostream>
#include<sstream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
#define forn(i,n) for(int i=0;i<int(n);++i) 
#define X first
#define Y second
#define INF 1 << 20
#define SZ 55
typedef pair<int, int> pt;
int n, m;
int z[SZ][SZ] = { 0 }, dst[SZ][SZ] = { 0 };
pt p[SZ][SZ];
int dx[8] = { 1, 1, 0, -1, -1, -1,  0,  1 };
int dy[8] = { 0, 1, 1,  1,  0, -1, -1, -1 };
string names[8] = { "S", "SE", "E", "NE", "N", "NW", "W", "SW" };
vector<string> path;

bool checks(int x, int y) {
	if (0 <= x && x < n && 0 <= y && y < m && z[x][y] != -1) return true;
	return false;
}

int bfs(pt st, pt fin) {
	forn(i, SZ) forn(j, SZ) dst[i][j] = INF;
	dst[st.X][st.Y] = 0;
	p[st.X][st.Y] = make_pair(-1, -1);
	queue<pt> q;
	q.push(st);
	while (!q.empty()) {
		pt w = q.front();
		q.pop();
		int x = w.X;
		int y = w.Y;
		forn(i, 8) {
			int x1 = x + dx[i];
			int y1 = y + dy[i];
			if (checks(x1, y1)) {
				if (dst[x][y] + z[x1][y1] < dst[x1][y1]) {
					dst[x1][y1] = dst[x][y] + z[x1][y1];
					p[x1][y1] = w;
					q.push(make_pair(x1, y1));
				}
			}
		}
	}
	return dst[fin.X][fin.Y];
}

void way(pt v) {
	int x = v.X;
	int y = v.Y;
	pt w = p[x][y];
	forn(i, 8) {
		if (checks(v.X - dx[i], v.Y - dy[i])) {
			if (w.X + dx[i] == v.X && w.Y + dy[i] == v.Y) {
				path.push_back(names[i]);
				break;
			}
		}
	}
	if (w != make_pair(-1, -1)) way(w);
}

int main()
{
	string s;
	pt start, finish;
	cin >> n >> m;
	forn(i, n) {
		cin >> s;
		forn(j, m) {
			if (s[j] == '#') z[i][j] = -1;
			if (s[j] == '.') z[i][j] = 1;
			if (s[j] == 'S') start.X = i, start.Y = j, z[i][j] = 1;
			if (s[j] == 'F') finish.X = i, finish.Y = j, z[i][j] = 1;
		}
	}
	int ans = bfs(start, finish);
	if (ans > INF / 2) {
		cout << -1;
		return 0;
	}
	cout << ans << endl;
	way(finish);
	reverse(path.begin(), path.end());
	forn(i, path.size()) cout << path[i] << endl;
}