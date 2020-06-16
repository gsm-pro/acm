#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<set>
using namespace std;
#define forn(i,n) for(int i=0;i<int(n);++i)
int n,m;
int c[1014];
int minw;
set<int> minmst;
vector<pair<int,pair<int,int>>> ed;
vector<vector<pair<pair<int,int>,int>>> g;
int wmr[1001][1001];
const int MINV=-2000000001;
bool used[1014];

void spdfs(int st,int v,int nmw)
{
	if(used[v]) return;
	used[v]=true;
	wmr[st][v]=nmw;
	forn(j,g[v].size())
	{
		int nr;
		if(nmw==-1) nr=g[v][j].second;else
			if(ed[nmw].first>g[v][j].first.second)	
				nr=nmw;
			else
				nr=g[v][j].second;
		spdfs(st,g[v][j].first.first,nr);		
	}
}

int leader(int v)
{
	if (c[v]!=v) c[v]=leader(c[v]);
	return c[v];
}

bool merge(int a,int b)
{
	a=leader(a);
	b=leader(b);
	if(a==b) return false;
	if(rand()&2)
		c[a]=b;
	else
		c[b]=a;
	return true;
}

void main()
{
	scanf("%d%d",&n,&m);
	ed.reserve(m);
	forn(i,m)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		if (a!=b)
		{
			a--;b--;
			ed.push_back(make_pair(c,make_pair(a,b)));
		}
	}
	m=(int)ed.size();
	sort(ed.begin(),ed.end());
	forn(i,n) c[i]=i;
	minw=0;
	g.resize(n);
	forn(i,m)
	{
		if(merge(ed[i].second.first,ed[i].second.second))
		{
			minw+=ed[i].first;
			minmst.insert(i);
			g[ed[i].second.first].push_back(make_pair(make_pair(ed[i].second.second,ed[i].first),i));
			g[ed[i].second.second].push_back(make_pair(make_pair(ed[i].second.first,ed[i].first),i));
		}
	}
	if (minmst.size()!=n-1)
	{
		printf("-1\n");
		return;
	}
	forn(i,n)
	{
		memset(used,0,sizeof(used));
		spdfs(i,i,-1);
	}
	int answ=2000000000;
	int puted;
	int rmved;
	forn(i,m)
	{
		if(minmst.count(i)==0)
		{
			if(minw+ed[i].first-ed[wmr[ed[i].second.first][ed[i].second.second]].first<answ)
			{
				answ=minw+ed[i].first-ed[wmr[ed[i].second.first][ed[i].second.second]].first;
				puted=i;
				rmved=wmr[ed[i].second.first][ed[i].second.second];
				if(answ==minw) break;
			}
		}
	}
	if (answ==2000000000)
	{
		printf("-1\n");
		return;
	}
	printf("%d\n",answ);
	minmst.erase(rmved);
	minmst.insert(puted);
	set<int>::iterator it;
	for(it=minmst.begin();it!=minmst.end();++it)
		printf("%d %d %d\n",ed[*it].second.first+1,ed[*it].second.second+1,ed[*it].first);
}