#include<cstdio>
#include<queue>
using namespace std;
const int INF=1000000000;
 
int main() 
{
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
	}
	int s=0;
	vector<int> d(n,INF);
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
				q.push(make_pair(-d[to],to));
			}
		}
	}
	for (int i=1;i<n;i++)
		if (d[i]==INF) printf("NO\n");else printf("%d\n",d[i]);
}