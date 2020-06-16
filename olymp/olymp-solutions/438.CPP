#include<iostream>
#include<algorithm>
using namespace std;
#define MAXDISTANCE 1<<20
int dist[1001][1001],color[1001],n,mind,maxd;

bool fill(int index,int C,int value)
{
	if (color[index]==0)
	{
		color[index]=C;
		for(int i=0;i<n;++i)
			if (i!=index && dist[index][i]>value && !fill(i,3-C,value)) return false;
		return true;
	} else return (color[index]==C);
}

bool canDivide(int value)
{
	memset(color,0,sizeof color);
	for (int i=0;i<n;++i)
		if (color[i]==0 && !fill(i,1,value)) return false;
	return true;
}

int solve(int mind,int maxd)
{
	if (n==2) return 0;
	while (maxd>mind)
	{
		int m=(maxd+mind)/2;
		if (canDivide(m)) maxd=m;else mind=m+1;
	}
	return maxd;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n-1;++i)
	{
		for(int j=i+1;j<n;++j)
		{
			scanf("%d",&dist[i][j]);
			dist[j][i]=dist[i][j];
		}
	}
	maxd=-1,mind=MAXDISTANCE;
	for (int i=0;i<n-1;++i)
	{
		for (int j=i+1;j<n;++j)
		{
			maxd=max(maxd,dist[i][j]);
			mind=min(mind,dist[i][j]);
		}
	}
	cout<<solve(mind,maxd);
}