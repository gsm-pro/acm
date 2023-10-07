#include<string>
#include<vector>
#include<iostream>
using namespace std;
#define int64 __int64
const int MAXVER = 10000;
const int MAXLEN = 100;
vector<string> ss;
int64 cost[MAXVER + 1], vercost[MAXVER + 1];
int sym[MAXVER + 1], nver, go[MAXVER + 1][26], rt[MAXVER + 1], n;

int GetGo(int ver, char c)
{
	if (go[ver][c] == 0)
		nver++, sym[nver] = c, rt[nver] = ver, go[ver][c] = nver;
	return go[ver][c];
}

void AddTree(string& a, int64 ccost)
{
	int cur = 1;
	for (int i = 0; i < (int)a.length(); i++) cur = GetGo(cur, a[i]);
	vercost[cur] += ccost;
}

int suflink[MAXVER + 1];
int getLink(int ver);

int countGo(int ver, int sym)
{
	if (go[ver][sym] != 0) return go[ver][sym];
	if (ver == 1) go[ver][sym] = 1; else
		go[ver][sym] = countGo(getLink(ver), sym);
	return go[ver][sym];
}

int getLink(int ver)
{
	if (suflink[ver] != 0) return suflink[ver];
	if (ver == 1)
	{
		suflink[ver] = 1;
		return 1;
	}
	if (rt[ver] == 1)
	{
		suflink[ver] = 1;
		return 1;
	}
	suflink[ver] = countGo(getLink(rt[ver]), sym[ver]);
	return suflink[ver];
}

void input()
{
	memset(vercost, 0, sizeof(vercost));
	nver = 1;
	int numwrd = 0;
	cin >> numwrd;
	for (int i = 0; i < numwrd; i++)
	{
		string nstr = "";
		char c;
		c = cin.get();
		while (c < 'a' || c > 'z') c = cin.get();
		while (c >= 'a' && c <= 'z')
		{
			nstr += (char)(c - 'a');
			c = cin.get();
		}
		ss.push_back(nstr);
		cin >> cost[i];
	}
	for (int i = 0; i < numwrd; i++) AddTree(ss[i], cost[i]);
	memset(suflink, 0, sizeof(suflink));
	for (int i = 1; i <= nver; i++)
	{
		getLink(i);
		for (int j = 0; j < 26; j++) countGo(i, j);
	}
	cin >> n;
}

int64 res[MAXLEN + 1][MAXVER + 1];
char rsym[MAXLEN + 1][MAXVER + 1];
int64 resval[MAXVER + 1];
int64 sumall = 0;

int64 getAnswer(int ver)
{
	if (resval[ver] != -1) return resval[ver];
	if (ver == 1)
	{
		resval[ver] = 0;
		return 0;
	}
	resval[ver] = getAnswer(suflink[ver]) + vercost[ver];
	return resval[ver];
}

void solve()
{
	memset(resval, 0xFF, sizeof(resval));
	memset(res, 0xFF, sizeof(res));
	for (int i = 0; i < (int)ss.size(); i++) sumall += cost[i];
	for (int i = 1; i <= nver; i++) getAnswer(i);
	for (int i = 1; i <= nver; i++) vercost[i] = resval[i];
	for (int i = 1; i <= nver; i++) res[n][i] = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = 1; j <= nver; j++)
		{
			for (int k = 0; k < 26; k++)
			{
				int nj = go[j][k];
				if (res[i + 1][nj] == -1) continue;
				if (res[i][j] < res[i + 1][nj] + vercost[nj])
				{
					res[i][j] = res[i + 1][nj] + vercost[nj];
					rsym[i][j] = k;
				}
			}
		}
	}
	string rs = "";
	cout << res[0][1] << endl;
	int cj = 1;
	for (int i = 0; i < n; i++)
	{
		rs += (char)(rsym[i][cj] + 'a');
		cj = go[cj][rsym[i][cj]];
	}
	cout << rs;
}

int main()
{
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
	input();
	solve();
}