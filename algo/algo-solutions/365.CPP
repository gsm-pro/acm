#include<iostream>
#include<vector>
using namespace std;
#define forn(i,n) for(int i=0;i<int(n);++i)
int n,m;
bool g[105][105];
bool used[105];
bool used2[105];
int p[105];
int p1[105];

bool kuhn(int v)
{
	if(used[v]) return false;
	used[v]=true;
	forn(j,n)
		if(g[v][j])
			if(p[j]==-1 || kuhn(p[j]))
			{
				p[j]=v;
				p1[v]=j;
				return true;
			}
	return false;
}

void main()
{
	scanf("%d%d",&n,&m);
	memset(g,0,sizeof(g));
	forn(i,m)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		--a;--b;
		g[a][b]=true;
	}
	memset(p,-1,sizeof(p));
	memset(p1,-1,sizeof(p1));
	memset(used2,0,sizeof(used2));
	forn(i,n)
		forn(j,n)
		if(g[i][j] && p[j]==-1)
		{
			p[j]=i;
			p1[i]=j;
			used2[i]=true;
			break;
		}
	forn(i,n)
		if(!used2[i])
		{
			memset(used,0,sizeof(used));
			kuhn(i);
		}
	vector<vector<int>> ans;
	memset(used2,0,sizeof(used2));
	forn(i,n)
	{
		if(!used2[i] && p[i]==-1)
		{
			vector<int> tmp;
			int v=i;
			while(v!=-1)
			{
				tmp.push_back(v);
				used2[v]=true;
				v=p1[v];				
			}
			ans.push_back(tmp);
		}
	}
	printf("%d\n",ans.size());
	forn(i,ans.size())
	{
		forn(j,ans[i].size())
			printf("%d ",ans[i][j]+1);
		printf("\n");
	}
}