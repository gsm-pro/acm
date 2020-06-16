#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
#define forn(i,n) for(int i=0;i<int(n);i++)
#define MP(x,y) make_pair(x,y)
typedef pair<int,int> PII;
const int INF=1000000;

int main()
{
	int n,m,start,finish;
	scanf_s("%d%d%d%d",&n,&m,&start,&finish);
	start--;
	finish--;
	vector<vector<PII>> g(n);
	vector<int> d(n,INF);
	queue<int> q;
	forn(i,m)
	{
		int p,q,t;
		scanf_s("%d%d%d",&p,&q,&t);
		p--; 
		q--; 
		t=(t==0) ? 2:1;
		g[p].push_back(MP(q,t));
		g[q].push_back(MP(p,t));
	}
	d[start] = 0;
	q.push(start);
	while(!q.empty())
	{
		int w = q.front();
		q.pop();
		forn(x,g[w].size())
		{
			PII gx=g[w][x];
			if(d[w]+gx.second<d[gx.first])
			{
				d[gx.first]=d[w]+gx.second;
				q.push(gx.first);
			}
		}
	}
	(d[finish]==INF) ? printf("No solution"):printf("%f",d[finish]/2.0);
}