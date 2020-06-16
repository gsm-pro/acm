#include<iostream>
using namespace std;
#define LL long long
int _10[11]={1};
int d,len;

bool witness(int a,int &n)
{
	LL d=1;
	int b=n-1;
	for (int i=31;i>=0;i--)
	{
		LL x=d;
		d=(d*d)%n;
		if (d==1 && x!=1 && x!=n-1) return true;
		if (b&(1<<i)) d=(d*a)%n;
	}
	return (d!=1);
}

bool MillerRabin(int &n,int t=3)
{
	while (t-->0) if (witness(rand()%(n-1)+1,n)) return false;
	return true;
}

bool prime(int &n)
{
	if ((n>7) && !((n%2)&&(n%3)&&(n%5)&&(n%7))) return false; 
	if (n==1 || !MillerRabin(n)) return false;
	return true;
}

bool prost(int &n,int &len)
{
	int a,b;
	for (int i=d;i<=len-d;i++)
	{
		a=n/_10[i];
		b=n%_10[i];
		if (a/_10[d-1]==0 || b/_10[d-1]==0 || a*_10[i]+b!=n) continue;
		if (prime(a) && prime(b)) return true;
	}
	return false;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	for (int i=1;i<10;i++) _10[i]=_10[i-1]*10; 
	int n;
	while (cin>>d>>n)
	{
		int start=n;
		if (n/_10[2*d-1]==0) start=_10[2*d-1];
		int q=start,len=1,i=start;
		while (q>0) q/=10,len++;
		if (!(i&1)) 
		{
			i++;
			if ((i-1)%10==2) i--;
		}
		bool fnd=false;
		while (!fnd)
		{
			if (i&1)
			{
				if (prost(i,len))
				{
					cout<<i<<endl;
					fnd=true;
				}
				if (i%10==1) i++;else i+=2;
			} else
				if (i%10==2)
				{
					if (prost(i,len))
					{
						cout<<i<<endl;
						fnd=true;
					}
					i++;
				}
		}
	}
}