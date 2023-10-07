#include<iostream>
using namespace std;
char z[14][1<<14];

int next(int &n,int &m)
{
	int mm=m^(m>>1);
	mm=mm^((1<<n)-1);
	if (mm>=(1<<(n-1))) mm-=(1<<(n-1));
	return mm;
}

int kol1(int &n,int &m)
{
	int r=0;
	for (int i=0;i<=n;i++) r+=((m>>i)&1);
	return r;
}

int rec(int n,int msk)
{
	if (n==1) return (msk&1) ? 1 : 0;
	if (n<14 && z[n][msk]!=-1) return z[n][msk];
	int t=kol1(n,msk)+rec(n-1,next(n,msk));
	if (n<14) z[n][msk]=t;
	return t;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	memset(z,-1,sizeof(z));
	int n,p1,p2,q1,q2,ans=0;
	cin>>n>>p1>>p2>>q1>>q2;
	for (int i=1;i<=n;i++)
	{
		int kk=i*(i+1)/2;
		for (int mask=0;mask<(1<<i);mask++)
		{
			int k1=rec(i,mask);
			int k2=kk-k1;
			if (p1<=k1 && k1<=p2 && q1<=k2 && k2<=q2) ans++;
		}
	}
	cout<<ans;
}