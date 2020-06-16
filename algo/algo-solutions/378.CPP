#include<cstdio>
#include<vector>
using namespace std;
vector<vector<int>> g;
bool used[100001];
int a[100001];
int n;

void go(int x,int cnt)
{
	if (used[x]) return;
	g[cnt].push_back(x);
	used[x]=true;
	go(a[x],cnt);
}

int main()
{
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
		--a[i];
	}
	int cnt=-1;
	g.resize(100001);
	for (int i=0;i<n;i++)
		if (!used[i])
		{
			cnt++;
			go(i,cnt);
		}
	cnt++;
	printf("%d\n",cnt);
	for (int i=0;i<cnt;i++)
	{
		printf("%d",g[i][0]+1);
		for (int j=1;j<(int)g[i].size();j++)
			printf(" -> %d",g[i][j]+1);
		printf("\n");
	}
}