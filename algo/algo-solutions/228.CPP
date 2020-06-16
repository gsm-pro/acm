#define _CRT_SECURE_NO_DEPRECATE
#include<cstdio>
#include<iostream>
#define LL __int64

bool witness(int a,int n)
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

bool MillerRabin(int n,int t=3)
{
	while (t-->0) if (witness(rand()%(n-1)+1,n)) return false;
	return true;
}

bool prime(int n)
{
	if ((n>7) && !((n%2)&&(n%3)&&(n%5)&&(n%7))) return false; 
	if (n==1 || !MillerRabin(n)) return false;
	return true;
}

int main()
{
	int k,n;
	scanf("%d",&k);
	while (k-->0)
	{
		scanf("%d",&n);
		(prime(n)) ? printf("YES\n") : printf("NO\n");
	}
}