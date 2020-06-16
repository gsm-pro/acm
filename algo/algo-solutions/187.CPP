#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
vector<vector<short>> g;
vector<long long> d;
vector<short> ans;

long long paths(int v)
{
	if (d[v]!=-1) return d[v];
	d[v]=1;
	for (size_t i=0;i<g[v].size();i++) d[v]+=paths(g[v][i]);
	return d[v];
}

void kth(int v,long long k)
{
	again:
	ans.push_back(v);
	if (k--==1) return;
	sort(g[v].begin(),g[v].end());
	for (size_t i=0;i<g[v].size();i++)
	{
		int pow=1;
		while (i+1<g[v].size() && g[v][i]==g[v][i+1]) pow++,i++;
		long long p=paths(g[v][i])*pow;
		if (k<=p) 
		{
			k=(k-1)/pow+1;
			v=g[v][i];
			goto again;
		}
		else k-=p;
	}
}

int main()
{
	int n,m;
	long long k;
	scanf_s("%d%d%lld",&n,&m,&k);
	g.resize(n);
	for (int i=0;i<n;i++) g[i].reserve(n/10);
	for (int i=0;i<m;i++)
	{
		short a,b;
		scanf_s("%hd%hd",&a,&b);
		g[a-1].push_back(b-1);
	}
	d.resize(n,-1);
	kth(0,k);
	for (size_t i=0;i<ans.size();i++) printf("%hd ",ans[i]+1);
}