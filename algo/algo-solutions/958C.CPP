#include<iostream>
#include<vector>
using namespace std;
#define forn(i,n) for(int i=0;i<int(n);++i)
const int NMAX=4000;
vector<int> g[NMAX];
bool u[NMAX];
bool ctS[NMAX];
int p[NMAX];

bool try_kuhn(int v)
{
	if(u[v]) return false;
	u[v]=true;
	forn(j,g[v].size())
	{
		int to=g[v][j];
		if(p[to]==-1 || try_kuhn(p[to]))
		{
			p[to]=v;
			return true;
		}
	}
	return false;
}

void main()
{
	int n, m;
	scanf("%d%d",&m,&n);
	forn(i,m)
	{
		int s;
		scanf("%d",&s);
		g[i].resize(s);
		forn(j,s)
		{
			int t;
			scanf("%d",&t);
			--t;
			g[i][j]=t;
		}
	}
	memset(p,-1,sizeof(p));
	memset(ctS,0,sizeof(ctS));
	forn(i,m)
	{
		int t;
		scanf("%d",&t);
		--t;
		p[t]=i;
		if(t!=-1) ctS[i]=true;
	}
	memset(u,0,sizeof(u)); 
	bool flag=false;
	for(int i=0;i<m && !flag;++i)
		if(!ctS[i] && try_kuhn(i)) flag=true;
	if(!flag)
	{
		puts("YES");
		return;
	}
	puts("NO");
	vector<pair<int,int>> res;
	forn(i,n)
		if(p[i]!=-1)
			res.push_back(make_pair(p[i]+1,i+1));
	printf("%d\n",res.size());
	forn(i,res.size())
		printf("%d %d\n",res[i].first,res[i].second);
}