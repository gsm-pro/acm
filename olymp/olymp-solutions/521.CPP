#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
int LEFT[100001],RIGHT[100001],n;

struct item
{
	int l,r,v,i;
	bool up;
} a[100001];

int get_lf(int lf,int rg)
{
	if (rg<lf) return 0;
	return (lf==0 ? LEFT[rg] : LEFT[rg]-LEFT[lf-1]);
}

int get_rg(int lf,int rg)
{
	if (rg<lf) return 0;
	return (lf==0 ? RIGHT[rg] : RIGHT[rg]-RIGHT[lf-1]);
}

int by_lower(const item &x,const item &y)
{
	return x.l<y.l;
}

int by_order(const item &x,const item &y)
{
	return x.i<y.i;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n;
	for (int i=0;i<n;i++)
	{
		string token;
		cin>>token;
		for (int j=0;j<(int)token.length();j++)
			if (token[j]!='.') a[i].v=a[i].v*10+(token[j]-'0');
		a[i].i=i;
		int x=(a[i].v/100)*100;
		a[i].l=a[i].v-x;
		a[i].r=(x==a[i].v ? 0 : 100-a[i].l);
	}
	sort(a,a+n,by_lower);
	for (int i=0;i<n;i++)
	{
		LEFT[i]=a[i].l+(i==0 ? 0 : LEFT[i-1]);
		RIGHT[i]=a[i].r+(i==0 ? 0 : RIGHT[i-1]);
	}
	for (int i=0;i<n;i++)
		a[i].up=(max(get_lf(0,i-1),get_rg(i,n-1))<max(get_lf(0,i),get_rg(i+1,n-1)));
	sort(a,a+n,by_order);
	for (int i=0;i<n;i++) 
		printf("%d ",(a[i].up ? (a[i].v+a[i].r)/100 : (a[i].v-a[i].l)/100));
}