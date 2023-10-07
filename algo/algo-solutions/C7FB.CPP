#include<cstdio>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;
typedef pair<int,int> rib;
typedef vector<rib> graf_line;
typedef graf_line::iterator graf_iter;
typedef vector<graf_line> graf;
const int inf=1000000000;

int main()
{
	int n,m,v1,v2,v;
	graf g;
	scanf_s("%d%d",&n,&m);
	g.resize(n);
	while (m-->0)
	{
		scanf_s("%d%d%d",&v1,&v2,&v);
		v1--;
		v2--;
		g[v1].push_back(make_pair(v2,v));
		g[v2].push_back(make_pair(v1,v));
	}
	vector<int> d(n,inf);
	v1=0;
	v2=n-1;
	d[v1]=0;
	set<pair<int,int>>u;
	for (int i=0;i<n;i++) u.insert(make_pair(i==v1 ? 0:inf,i));
	vector<bool> used(n);
	vector<int> parent(n,-1);
	for (int iter=0;iter<n;++iter)
	{
		int v=u.begin()->second;
		u.erase(u.begin());
		used[v]=true;
		for (graf_iter i=g[v].begin();i!=g[v].end();++i)
		{
			int to=i->first;
			if (!used[to])
				if (d[to]>d[v]+i->second)
				{
					u.erase(u.find(make_pair(d[to], to)));
					d[to]=d[v]+i->second;
					u.insert(make_pair(d[to],to));
					parent[to]=v;
				}
		}
	}
	if (parent[v2]==-1) printf("No solution");else
	{
		vector<int>path;
		for (int v=v2;v!=-1;v=parent[v]) path.push_back(v);
		reverse(path.begin(),path.end());
		for (unsigned i=0;i<path.size();++i) printf("%d ",path[i]+1);
	}
}