#include<iostream>
#include<string>
#include<cmath>
using namespace std;
int t[30002][2][2];
int a[30002],b[30002],n;

int rec(int x,int avt,int can)
{
	if (x==n) return 0;
	if (t[x][avt][can]!=-1) return t[x][avt][can];
	int m;
	if (can==1)
		m=min(a[x]+rec(x+1,1,0),b[x]+rec(x+1,0,1));
	if (can==0)
	{
		if (avt==1) m=min(a[x]+rec(x+1,1,0),b[x]+rec(x+1,0,0));
		if (avt==0) m=b[x]+rec(x+1,0,0);
	}
	t[x][avt][can]=m;
	return m;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	memset(t,-1,sizeof t);
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d",&a[i]);
	for (int i=0;i<n;i++) scanf("%d",&b[i]);
	printf("%d",rec(0,0,1));
}