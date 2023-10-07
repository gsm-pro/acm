#define _CRT_SECURE_NO_WARNINGS
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<string>
#include<map>
using namespace std;

struct Edge {
	int u, v, w, next, id;
};

int cnt;
int head[5005];
int n, m, k;
int p[5005];
int vis[5005];
int Max[5005];
int sign[100005];
int num;
int print[100005];
Edge edge[100005], edge_temp[100005], dp[5005];

void add(int u, int v, int w, int id) {
	edge[cnt].u = u;
	edge[cnt].v = v;
	edge[cnt].w = w;
	edge[cnt].id = id;
	edge[cnt].next = head[u];
	head[u] = cnt++;
}

bool cmp(Edge t1, Edge t2) {
	return t1.w < t2.w;
}

int find1(int x) {
	if (p[x] == x) {
		return x;
	}
	return p[x] = find1(p[x]);
}

int kruscal() {
	int ans = 0;
	sort(edge_temp + 1, edge_temp + 1 + m, cmp);
	int temp_num = 0;
	for (int i = 1; i <= m; i++) {
		int u = edge_temp[i].u;
		int v = edge_temp[i].v;
		int w = edge_temp[i].w;
		int id = edge_temp[i].id;
		if (u != 1) {
			int t1 = find1(u);
			int t2 = find1(v);
			if (t1 != t2) {
				temp_num++;
				ans += w;
				p[t1] = t2;
				add(u, v, w, id);
				add(v, u, w, id);
				sign[id] = 1;
			}
		}
	}
	return ans;
}

namespace fastIO {
#define BUF_SIZE 100000
	bool IOerror = 0;
	inline char nc() {
		static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
		if (p1 == pend) {
			p1 = buf;
			pend = buf + fread(buf, 1, BUF_SIZE, stdin);
			if (pend == p1) {
				IOerror = 1;
				return -1;
			}
		}
		return *p1++;
	}

	inline bool blank(char ch) {
		return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}

	inline void read(int &x) {
		char ch;
		while (blank(ch = nc()));
		if (IOerror) {
			return;
		}
		for (x = ch - '0'; (ch = nc()) >= '0'&&ch <= '9'; x = x * 10 + ch - '0');
	}
#undef BUF_SIZE
};

void dfs(int cur, int pre) {
	for (int i = head[cur]; i != -1; i = edge[i].next) {
		int v = edge[i].v;
		int w = edge[i].w;
		int id = edge[i].id;
		if (v != pre&&sign[id]) {
			if (dp[v].w != -1) {
				if (w > dp[cur].w) {
					dp[v].w = w;
					dp[v].u = cur;
					dp[v].v = v;
					dp[v].id = id;
				}
				else {
					dp[v] = dp[cur];
				}
			}
			dfs(v, cur);
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	fastIO::read(n);
	fastIO::read(m);
	fastIO::read(k);
	cnt = 0;
	int cnt1 = 0;
	for (int i = 1; i <= m; i++) {
		sign[i] = 0;
	}
	for (int i = 1; i <= n; i++) {
		head[i] = -1;
		p[i] = i;
		vis[i] = 0;
		Max[i] = 0x3f3f3f3f;
	}
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		fastIO::read(u);
		fastIO::read(v);
		fastIO::read(w);
		if (u > v) {
			swap(u, v);
		}
		if (u == 1) {
			cnt1++;
		}
		edge_temp[i].u = u;
		edge_temp[i].v = v;
		edge_temp[i].w = w;
		edge_temp[i].id = i;
	}
	if (cnt1 < k) {
		printf("-1\n");
		return 0;
	}
	int ans = kruscal();
	int k_temp = 0;
	for (int i = 1; i <= m; i++) {
		int u = edge_temp[i].u;
		int v = edge_temp[i].v;
		int w = edge_temp[i].w;
		int id = edge_temp[i].id;
		int t1 = find1(v);
		if (u == 1 && vis[t1] == 0) {
			add(u, v, w, id);
			dp[v].w = -1;
			Max[v] = -1;
			k_temp++;
			ans += w;
			vis[t1] = 1;
			sign[id] = 1;
		}
	}
	if (k_temp > k) {
		printf("-1\n");
		return 0;
	}
	for (int i = k_temp + 1; i <= k; i++) {
		for (int j = 2; j <= n; j++) {
			if (Max[j] == -1) {
				dp[j].w = -1;
			}
			else {
				dp[j].w = 0;
			}
		}
		dfs(1, -1);
		int Min = 0x3f3f3f3f;
		int pos;
		int pos_temp;
		for (int j = 1; j <= m; j++) {
			int u = edge_temp[j].u;
			int v = edge_temp[j].v;
			int w = edge_temp[j].w;
			int id = edge_temp[j].id;
			if (u == 1 && dp[v].w != -1) {
				if (Min > w - dp[v].w) {
					Min = w - dp[v].w;
					pos = v;
					pos_temp = id;
				}
			}
		}
		sign[pos_temp] = 1;
		sign[dp[pos].id] = 0;
		Max[pos] = -1;
		ans += Min;
		add(1, pos, 0, pos_temp);
	}
	for (int i = 1; i <= m; i++) {
		if (sign[i]) {
			print[num++] = i;
		}
	}
	printf("%d\n", num);
	for (int i = 0; i < num; i++) {
		printf(i == num - 1 ? "%d\n" : "%d ", print[i]);
	}
}