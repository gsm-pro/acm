#include<iostream>
#include<cstdio>
int a[10002],b[10002],n,cnt[10002],e;

inline bool could(int i,int j)
{
	if (b[i] && b[i]!=j) return 0;
	if (b[i]) return 1;
	b[i]=j;
	if (!could(j,a[i])) b[i]=0;
	return (b[i]!=0);
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if (a[i]>=1 && a[i]<=n) cnt[a[i]]++;
	}
	for (int i=1;i<=n;i++)
		if (cnt[i]!=1) 
		{
			printf("No solution");
			return 0;
		}
	for (int i=1;i<=n;i++) 
	{
		if (!b[i])
		{
			e=0;
			for (int j=n;j>=1;j--) 
				if (could(i,j))
				{
					e=1;
					break;
				}
			if (e==0)
			{
				printf("No solution");
				return 0;
			}
		}
	}
	for (int i=1;i<=n;i++) printf("%d ",b[i]);
}