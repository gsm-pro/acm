#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1000000000;
 
int main() 
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	vector<vector<pair<int,int>>> g(n);
	for (int i=0;i<m;i++)
	{
		int a,b,v;
		scanf("%d%d%d",&a,&b,&v);
		a--;
		b--;
		g[a].push_back(make_pair(b,v));
		g[b].push_back(make_pair(a,v));
	}
	int s=0;
	vector<int> d(n,INF),p(n,-1);
	d[s]=0;
	priority_queue<pair<int,int>>q;
	q.push(make_pair(0,s));
	while (!q.empty()) 
	{
		int v=q.top().second,cur_d=-q.top().first;
		q.pop();
		if (cur_d>d[v]) continue;
 		for (int j=0;j<(int)g[v].size();++j) 
		{
			int to=g[v][j].first,len=g[v][j].second;
			if (d[v]+len<d[to]) 
			{
				d[to]=d[v]+len;
				p[to]=v;
				q.push(make_pair(-d[to],to));
			}
		}
	}
	if (p[n-1]==-1) printf("No solution");else
	{
		vector<int>path;
		for (int v=n-1;v!=-1;v=p[v]) path.push_back(v);
		reverse(path.begin(),path.end());
		for (unsigned i=0;i<path.size();++i) printf("%d ",path[i]+1);
	}
}