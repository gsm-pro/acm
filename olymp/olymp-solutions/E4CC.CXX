#include<fstream>
#include<queue>
#include<map>
using namespace std;
#define N 200002
ifstream I("input.txt");
ofstream O("output.txt");
int n, i, fa[N], sons[N], isleaf[N], leafdst[N], forwrd[N];
map<int, int> backwrd;
priority_queue<int> pq;
queue<int> q;

int main() {
	I >> n;
	for (i = 1; i < n; i++) isleaf[i] = 1;
	for (i = 1, fa[0] = -1; i < n; i++) {
		I >> fa[i];
		isleaf[--fa[i]] = 0;
		sons[fa[i]]++;
	}
	for (i = 1; i < n; i++)
		if (isleaf[i]) q.push(i), leafdst[i] = 1;
	while (!q.empty()) {
		int v = q.front(), pv = fa[v];
		q.pop();
		if (!leafdst[pv] || leafdst[pv] < leafdst[v] + 1) {
			leafdst[pv] = leafdst[v] + 1;
			forwrd[pv] = v;
		}
		sons[pv]--;
		if (pv && !sons[pv]) q.push(pv);
	}
	for (i = 0; i < n; i++)
		if (forwrd[i]) backwrd[forwrd[i]] = i;
	for (i = 0; i < n; i++)
		if (isleaf[i]) {
			int len = 1, v = i;
			while (backwrd.count(v)) v = backwrd[v], len++;
			pq.push(len);
		}
	int sum = 0, rem = n - pq.size();
	while (!pq.empty()) {
		sum += pq.top();
		pq.pop();
		O << sum << " ";
	}
	while (rem--) O << n << " ";
}