#include<cstdio>
#include<vector>
using namespace std;
vector<vector<int>> g;
bool used[100001];
int color[100001];
int n;

void go(int x,int c,int pred)
{
	if (x==pred)
	{
		color[x]=1;
		return;
	}
	if (color[x]>0 && color[x]!=c)
	{
		printf("-1");
		exit(0);
	}
	if (used[x]) return;
	color[x]=c;
	used[x]=true;
	for (int i=0;i<(int)g[x].size();i++)
		go(g[x][i],(c+2)%2+1,x);
}

int main()
{
	scanf("%d",&n);
	g.resize(n);
	for (int i=0;i<n;i++)
	{
		int t;
		scanf("%d",&t);
		t--;
		g[i].push_back(t);
	}
	for (int i=0;i<n;i++)
		if (!used[i]) go(i,1,-1);
	for (int i=0;i<n;i++) printf("%d ",color[i]);
}