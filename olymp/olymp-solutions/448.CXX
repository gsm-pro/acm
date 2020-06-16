#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#define MAX 1000002
#define oo 1<<30
int n,m,k,i,color[MAX],wisemen_colors[MAX]={0},ans=oo,wisemen_cap[MAX],wisemen_diff[MAX];

int next()
{
	char c;
	int t=0;
	while ((c=getchar())>0)
	{
		if (c==' ' || c=='\r' || c=='\n') break;
		if (c<'0' || c>'9') continue;
		t*=10;
		t+=c-'0';
	}
	return t;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d%d%d\n",&n,&m,&k);
	for (i=1;i<=k;i++) color[i]=next();
	for (i=1;i<=n;i++)
	{
		wisemen_cap[i]=next();
		wisemen_colors[wisemen_cap[i]]++;
	}
	for (i=1;i<=n;i++)
	{
		if (m-n<color[wisemen_cap[i]])
		{
			wisemen_diff[i]=m-n-(color[wisemen_cap[i]]-wisemen_colors[wisemen_cap[i]]);
			if (ans>wisemen_diff[i]) ans=wisemen_diff[i];
		}
	}
	if (ans==oo) printf("0");else
	{
		for (i=1;i<=n;i++)
			if (wisemen_diff[i]==ans) printf("%d ",i);
		printf("\n%d",ans+1);
	}
}