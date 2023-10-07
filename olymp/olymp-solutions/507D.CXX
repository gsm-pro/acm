#include<bits/stdc++.h>
using namespace std;
#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define forv(i, v) forn(i, v.size())
typedef long long ll;
const int MAXN = 10000;

struct State {
	int len, link, endpos;
	map<char, int> next;
	State() {
		len = 0, link = -1;
	}
};

State st[2 * MAXN];
ll d[2 * MAXN];
int sz, last;

void extend(char c) {
	int cur = sz++;
	st[cur].len = st[last].len + 1;
	st[cur].endpos = st[cur].len - 1;
	int p;
	for (p = last; p != -1 && !st[p].next.count(c); p = st[p].link) {
		st[p].next[c] = cur;
	}
	last = cur;
	if (p == -1) {
		st[cur].link = 0;
		return;
	}
	int q = st[p].next[c];
	if (st[q].len == st[p].len + 1) {
		st[cur].link = q;
		return;
	}
	int clone = sz++;
	st[clone].link = st[q].link;
	st[clone].len = st[p].len + 1;
	st[q].link = clone;
	st[clone].next = st[q].next;
	st[clone].endpos = st[q].endpos;
	while (p != -1 && st[p].next[c] == q) {
		st[p].next[c] = clone;
		p = st[p].link;
	}
	st[cur].link = clone;
}

int calc(int v) {
	if (d[v] != -1) return d[v];
	d[v] = 0;
	for (map<char, int>::iterator it = st[v].next.begin(); it != st[v].next.end(); it++) {
		if (it->first < 0)
			d[v] |= (1 << (-it->first - 1));
		else
			d[v] |= calc(it->second);
	}
	return d[v];
}

int main() {
	ifstream I("input.txt");
	ofstream O("output.txt");
	sz = 1, last = 0;
	int n = 3, ans = 0;
	string s, t;
	forn(i, n) {
		I >> s;
		t += s;
		forv(j, s) extend(s[j]);
		extend(-i - 1);
		t += char(-i - 1);
	}
	memset(d, 255, sizeof(d));
	forn(i, sz) if (calc(i) == (1 << n) - 1) {
		if (st[i].len > st[ans].len) ans = i;
	}
	O << t.substr(st[ans].endpos - st[ans].len + 1, st[ans].len).length();
}