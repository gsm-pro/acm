#include<vector>
#include<queue>
#include<cstdio>
using namespace std;
const int inf=999999;
queue<int> q;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,m,i,j,x,y,len,min;
	while (scanf_s("%d%d",&n,&m)==2)
	{
		vector<vector<int>> g(n);
		bool used[1000];
		int dst[1000],pred[1000];
		for (i=0;i<m;i++)
		{
			scanf_s("%d%d",&x,&y);
			--x;
			--y;
			g[x].push_back(y); 
			g[y].push_back(x);
		}
		min=inf;
		for (j=0;j<n;j++)
		{
			memset(used,0,sizeof(used));
			memset(dst,0,sizeof(dst));
			memset(pred,0,sizeof(pred));
			q.push(j);
			used[j]=true;
			while (!q.empty())
			{
				int v=q.front(); 
				q.pop();
				for (i=0;i<(int)g[v].size();i++)   
				{
					int s=g[v][i];
					if (!used[s]) 
					{
						q.push(s);
						used[s]=true;
						dst[s]=dst[v]+1;
						pred[s]=v;
					}				
					else  
						if (pred[v]!=s) 
						{
							len=dst[s]+dst[v]+1;
							if (len<min) min=len;
						}
				}
			}
		}
		(min==inf) ? printf("-1 ") : printf("%d ",min);
	}
}