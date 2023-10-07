#include<iostream>
#include<vector>
using namespace std;
#define forn(i,n) for(int i=0;i<int(n);i++)
#define NMAX 100005
int t,n,m;
int colors[NMAX];
vector<int> g[NMAX];

bool dfs(int v,int color)
{
	forn(i,g[v].size())
	{
		int to=g[v][i];
		if (colors[to]<0)
		{
			colors[to]=color;
			if (!dfs(to,1-color)) return false;
		} else {
			if (colors[to]!=color) return false;
		}
	}
	return true;
}

int main()
{
	scanf_s("%d",&t);
	forn(k,t)
	{
		scanf_s("%d%d",&n,&m);
		bool ok=true;
		memset(colors,-1,sizeof(colors));
		forn(i,n) g[i].clear();
		forn(i,m)
		{
			int a,b;
			scanf_s("%d%d",&a,&b);
			g[--a].push_back(--b);
			g[b].push_back(a);
		}
		forn(i,n)
		{
			if (colors[i]<0)
			{
				colors[i]=0;
				if (!dfs(i,1))
				{
					ok=false;
					break;
				}
			}
		}
		printf(ok ? "YES\n" : "NO\n");
	}
}