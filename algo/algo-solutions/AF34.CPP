#include<vector>
#include<cstdio>
using namespace std;

class edge
{
public:
	int x,y,w;
	edge(int x1,int y1,int w1)
	{
		x=x1;
		y=y1;
		w=w1;
	}
};
const int inf=1000000000;

void main()
{
	int n,m;
	scanf_s("%d%d\n",&n,&m);
	vector<edge>e;
	vector<int>d(n+1,inf),p(n+1,0);
	for(int i=0;i<m;i++)
	{
		int x,y,w;
		scanf_s("%d%d%d\n",&x,&y,&w);
		edge tmp(x,y,w);
		e.push_back(tmp);
	}
	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<m;j++)
		{
			if (d[e[j].y]>d[e[j].x]+e[j].w)
			{
				d[e[j].y]=d[e[j].x]+e[j].w;
				p[e[j].y]=e[j].x;
			}
		}
	}
	vector<int> in_path(n+1,0),pos(n+1,0),path;
	for(int j=0;j<m;j++)
	{
		if (d[e[j].y]>d[e[j].x]+e[j].w)
		{
			p[e[j].y]=e[j].x;
			printf("YES\n");
			int v=e[j].y,k=0;            
			while (!in_path[v])
			{
				pos[v]=k;
				path.push_back(v);
				in_path[v]=1;
				k++;
				v=p[v];
			}
			printf("%d\n",k-pos[v]+1);
			for(int i=k-1;i>=pos[v];i--)
				printf("%d ",path[i]);
			printf("%d",path[k-1]);
			return;
		}
	}
	printf("NO");
}