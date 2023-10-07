#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int INF = 1 << 30;
int N, M;
int ans[555];
int id[225][225];
int up[555];

struct Edge {
	int to, cap, rev;
	Edge() {}
	Edge(int to, int cap, int rev) {
		this->to = to;
		this->cap = cap;
		this->rev = rev;
	}
};

struct DinicFlow {
	int size, src, sink;
	vector<vector<Edge>> G;
	vector<int> level, iter;

	DinicFlow() {}
	DinicFlow(int size, int src, int sink) {
		this->size = size;
		this->src = src;
		this->sink = sink;
		G = vector<vector<Edge>>(size);
		level = vector<int>(size, -1);
		iter = vector<int>(size, 0);
	}

	void addEdge(int from, int to, int cap) {
		G[from].push_back(Edge(to, cap, (int)G[to].size()));
		G[to].push_back(Edge(from, 0, (int)G[from].size() - 1));
	}

	bool bfs(int src, int sink) {
		queue<int> q;
		q.push(src);
		level[src] = 0;
		while (!q.empty() && level[sink] == -1) {
			int here = q.front();
			q.pop();
			for (size_t i = 0; i < G[here].size(); i++) {
				Edge& e = G[here][i];
				if (e.cap <= 0 || level[e.to] != -1) {
					continue;
				}
				level[e.to] = level[here] + 1;
				q.push(e.to);
			}
		}
		return level[sink] != -1;
	}

	int dfs(int here, int minFlow, int sink) {
		if (here == sink) {
			return minFlow;
		}
		for (size_t i = iter[here]; i < G[here].size(); i++) {
			Edge& e = G[here][i];
			if (e.cap == 0 || level[e.to] != level[here] + 1) {
				continue;
			}
			int f = dfs(e.to, min(minFlow, e.cap), sink);
			if (f > 0) {
				e.cap -= f;
				G[e.to][e.rev].cap += f;
				return f;
			}
		}
		return 0;
	}

	int getMaxFlow() {
		int fl = 0;
		for (;;) {
			level = vector<int>(size, -1);
			iter = vector<int>(size, 0);
			if (!bfs(src, sink)) {
				break;
			}
			while (int f = dfs(src, INF, sink)) {
				fl += f;
			}
		}
		return fl;
	}
};

struct LRMaxFlow {
	DinicFlow dinicFlow;
	int size, src, sink, fsrc, fsink;
	vector<int> inSum, outSum;

	LRMaxFlow(int size, int src, int sink) {
		this->size = size;
		this->src = src;
		this->sink = sink;
		fsrc = size;
		fsink = size + 1;
		dinicFlow = DinicFlow(size + 2, fsrc, fsink);
		inSum = vector<int>(size, 0);
		outSum = vector<int>(size, 0);
	}

	void addEdge(int from, int to, int cap, int lower) {
		dinicFlow.addEdge(from, to, cap);
		inSum[to] += lower;
		outSum[from] += lower;
	}

	int getMaxFlow() {
		for (int i = 0; i < size; i++)
			if (inSum[i]) dinicFlow.addEdge(fsrc, i, inSum[i]);
		for (int i = 0; i < size; i++)
			if (outSum[i]) dinicFlow.addEdge(i, fsink, outSum[i]);
		dinicFlow.addEdge(sink, src, INF);
		return dinicFlow.getMaxFlow();
	}
};

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	for (int i = 0; i < 222; i++)
		for (int j = 0; j < 222; j++) id[i][j] = 500;
	cin >> N >> M;
	LRMaxFlow lr(N, 0, 0);
	for (int i = 0; i < M; i++) {
		int a, b, l, r;
		cin >> a >> b >> l >> r;
		a--, b--;
		id[a][b] = i;
		lr.addEdge(a, b, r - l, l);
		up[i] = r;
	}
	int fl = lr.getMaxFlow(), sum = 0;
	for (int i = 0; i < N; i++) sum += lr.inSum[i];
	if (fl != sum) {
		cout << "NO";
		return 0;
	}
	for (int i = 0; i < N; i++) {
		for (size_t j = 0; j < lr.dinicFlow.G[i].size(); j++) {
			Edge& e = lr.dinicFlow.G[i][j];
			int num = id[i][e.to];
			ans[num] = up[num] - e.cap;
		}
	}
	cout << "YES\n";
	for (int i = 0; i < M; i++) cout << ans[i] << "\n";
}