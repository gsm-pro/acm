#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
	int m,n,a,b,v,cost=0;
	scanf("%d%d",&n,&m);
	vector<pair<int,pair<int,int>>>g(m);
	for (int i=0;i<m;i++) 
	{
		scanf("%d%d%d",&a,&b,&v);
		g[i].first=v;
		g[i].second.first=a-1;
		g[i].second.second=b-1;
	}
	vector<pair<int,int>>res;
	sort(g.begin(),g.end());
	vector<int>p(n);
	for (int i=0;i<n;i++) p[i]=i;
	for (int i=0;i<m;i++)
	{
		int a=g[i].second.first,
			b=g[i].second.second,
			l=g[i].first,
			pa,pb;
		for (pa=a;pa!=p[pa];pa=p[pa]);
		for (pb=b;pb!=p[pb];pb=p[pb]);
		for (int j=a;j!=p[j];j=p[j]) p[j]=pa;
		for (int j=b;j!=p[j];j=p[j]) p[j]=pb;
		if (pa!=pb)
		{
			cost+=l;
			res.push_back(g[i].second);
			if (rand()&1) p[pb]=pa;else p[pa]=pb;
		}
	}
	printf("%d\n",cost);
	for (int i=0;i<(int)res.size();i++) 
		printf("%d %d\n",res[i].first+1,res[i].second+1);
}