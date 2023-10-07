#include<fstream>
#include<string>
#include<queue>
using namespace std;
const int N = 64, INF = 0x3f3f3f3f;

struct state { int ac, p, v, l; };

int n, s, k, r[N];
bool vst[N][N][2048];
queue<state>q;
string c;

void add(state t) {
	if (!vst[t.ac][t.p][t.v]) vst[t.ac][t.p][t.v] = true, q.push(t);
}

int rec() {
	state init = { s - 1, n, 0, 0 };
	add(init);
	while (q.size()) {
		state t = q.front();
		q.pop();
		if (t.v >= k) return t.l;
		if ((r[t.ac] > r[t.p]) && (c[t.ac] != c[t.p])) add({ t.ac, t.ac, t.v + r[t.ac], t.l });
		if (t.ac > 0) add({ t.ac - 1, t.p, t.v, t.l + 1 });
		if (t.ac < n - 1) add({ t.ac + 1, t.p, t.v, t.l + 1 });
	}
	return -1;
}

int main() {
	ifstream I("input.txt");
	I >> n >> s >> k;
	for (int i = 0; i < n; i++) I >> r[i];
	I >> c;
	c += 'N';
	ofstream("output.txt") << rec();
}