#include<cstdio>
#include<vector>
#include<queue>
#include<map>
#include<iostream>
using namespace std;
const int INF=1000000000;
#define LL long long
vector<pair<pair<int,int>,int>> rib,rb;
vector<int> fr1,frn;
vector<vector<int>> g(20001),g1(20001),id(20001);
int n,m;
vector<char>used;
int timer=0;
vector<int> t,f,c;
map<LL,int> hash;

vector<int> dsk(int s)
{
	vector<int> d(n,INF);
	d[s]=0;
	priority_queue<pair<int,int>> q;
	q.push(make_pair(0,s));
	while (!q.empty()) 
	{
		int v=q.top().second,cur_d=-q.top().first;
		q.pop();
		if (cur_d>d[v]) continue;
 		for (int j=0;j<(int)g[v].size();++j) 
		{
			int to=g[v][j],len=1;
			if (d[v]+len<d[to]) 
			{
				d[to]=d[v]+len;
				q.push(make_pair(-d[to],to));
			}
		}
	}
	return d;
}

LL getHash(int a,int b)
{
	return (min(a,b)+1945990+1UL)*(max(a,b)+2054030+1UL);
}

void dfs(int v,int p=-1)
{
	used[v]=true;
	t[v]=f[v]=timer++;
	for (size_t i=0;i<g1[v].size();++i)
	{
		int to=g1[v][i];
		if (to==p) continue;
		if (used[to]) f[v]=min(f[v],t[to]);else 
		{
			dfs(to,v);
			f[v]=min(f[v],f[to]);
			if (f[to]>t[v])
			{
				int num=id[v][i];
				int a=rib[num].first.first;
				int b=rib[num].first.second;
				LL hs=getHash(a,b);
				map<LL,int>::iterator it=hash.find(hs);
				if (it->second==1) c.push_back(num);
			}
		}
	}
}
 
int main() 
{
	scanf_s("%d%d",&n,&m);
	for (int i=0;i<m;i++)
	{
		int a,b;
		scanf_s("%d%d",&a,&b);
		a--,b--;
		g[a].push_back(b);
		g[b].push_back(a);
		rib.push_back(make_pair(make_pair(a,b),i));
	}
	fr1=dsk(0);
	frn=dsk(n-1);
	for (int i=0;i<(int)rib.size();i++)
	{
		int a=rib[i].first.first;
		int b=rib[i].first.second;
		if (fr1[a]+1+frn[b]==frn[0] || fr1[b]+1+frn[a]==frn[0]) 
			rb.push_back(rib[i]);
	}
	for (int i=0;i<(int)rb.size();i++)
	{
		int a=rb[i].first.first;
		int b=rb[i].first.second;
		int q=rb[i].second;
		g1[a].push_back(b);
		g1[b].push_back(a);
		id[a].push_back(q);
		id[b].push_back(q);
		hash[getHash(a,b)]++;
	}
	used.assign(n,false);
	t.resize(n);
	f.resize(n);
	dfs(0);
	printf("%d\n",(int)c.size());
	for (int i=0;i<(int)c.size();i++) printf("%d\n",c[i]+1);
}