#include<iostream>
using namespace std;
int p[1111],lf[1111],rg[1111],v[1111],m=0,n,d,res=0;

int dec(int p,int n)
{
	return (p+n-1)%n;
}

int inc(int p,int n)
{
	return (p+1)%n;
}

int dist(int a,int b)
{
	return min(abs(a-b),n-abs(a-b));
}

int costLeft(int idx)
{
	int res=dist(dec(lf[idx],n),p[idx]),prev=dec(idx,m);
	while (rg[prev]==dec(lf[idx],n))
	{
		res-=dist(rg[prev],p[prev]);
		res+=dist(dec(lf[prev],n),p[prev]);
		idx=dec(idx,m);
		prev=dec(idx,m);
	}
	return res;
}

int costRight(int idx)
{
	int res=dist(inc(rg[idx],n),p[idx]),prev=inc(idx,m);
	while (lf[prev]==inc(rg[idx],n))
	{
		res-=dist(lf[prev],p[prev]);
		res+=dist(inc(rg[prev],n),p[prev]);
		idx=inc(idx,m);
		prev=inc(idx,m);
	}
	return res;
}

void moveLeft(int idx)
{
	int prev=dec(idx,m);
	lf[idx]=dec(lf[idx],n);
	while (rg[prev]==lf[idx])
	{
		rg[prev]=dec(rg[prev],n);
		lf[prev]=dec(lf[prev],n);
		idx=dec(idx,m);
		prev=dec(idx,m);
	}
}

void moveRight(int idx)
{
	int prev=inc(idx,m);
	rg[idx]=inc(rg[idx],n);
	while (lf[prev]==rg[idx])
	{
		rg[prev]=inc(rg[prev],n);
		lf[prev]=inc(lf[prev],n);
		idx=inc(idx,m);
		prev=inc(idx,m);
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n;
	for (int i=0;i<n;i++)
	{
		cin>>d;
		if (d>0) v[m]=d,p[m]=i,m++;
	}
	for (int i=0;i<m;i++) lf[i]=rg[i]=p[i],v[i]--;
	for (int i=0;i<m;i++)
	{
		while (v[i]>0)
		{
			int l=costLeft(i),r=costRight(i);
			if (costLeft(i)<costRight(i)) moveLeft(i);
			else moveRight(i);
			v[i]--;
			res+=min(l,r);
		}
	}
	cout<<res;
}