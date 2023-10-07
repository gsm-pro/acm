#include<iostream>
#include<vector>
using namespace std;
#define forn(i,n) for(int i=0;i<int(n);++i)
int n,m;
bool g1[254][254];
bool g2[254][254];
bool u[254];
bool u2[254];
int p[254];
int sate[254];

bool kuhn(int v)
{
	if(u[v]) return false;
	u[v]=true;
	forn(j,m)
		if(g1[v][j])
			if(p[j]==-1 || kuhn(p[j]))
			{
				sate[v]=j;
				p[j]=v;
				return true;
			}
	return false;
}

void main()
{
	cin>>n>>m;
	memset(g1,0,sizeof(g1));
	memset(g2,0,sizeof(g2));
	forn(i,n)
	{
		int a;
		cin>>a;
		while(a!=0)
		{
			--a;
			g1[i][a]=true;
			g2[a][i]=true;
			cin>>a;
		}
	}
	memset(p,-1,sizeof(p));
	memset(u2,0,sizeof(u2));
	memset(sate,-1,sizeof(sate));
	forn(i,n)
		forn(j,m)
			if(g1[i][j] && p[j]==-1)
			{
				p[j]=i;
				sate[i]=j;
				u2[i]=true;
				break;
			}		
	forn(i,n)
		if(!u2[i])
		{
			memset(u,false,sizeof(u));
			kuhn(i);
		}
	vector<pair<int,int>> ans;
	forn(i,n)
		if(sate[i]!=-1)
			ans.push_back(make_pair(i,sate[i]));
		else
			forn(j,m)
			if(g1[i][j])
			{
				ans.push_back(make_pair(i,j));
				break;
			}
	forn(i,m)
		if(p[i]==-1)
			forn(j,n)
			if(g2[i][j])
			{
				ans.push_back(make_pair(j,i));
				break;
			}
	printf("%d\n",ans.size());
	forn(i,ans.size())
		printf("%d %d\n",ans[i].first+1,ans[i].second+1);
}