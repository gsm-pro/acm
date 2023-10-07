#define _CRT_SECURE_NO_DEPRECATE
#include<cstdio>
#include<iostream>
using namespace std;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	double t[51],x=300,h=512;
	int n,iter=1000,c,m;
	scanf("%d\n",&n);
	char buf[9];
	for (int i=0;i<=n;i++)
	{
		gets(buf);
		sscanf(buf,"%d:%d",&c,&m);
		t[i]=c*60+m;
	}
	while (iter-->0)
	{
		double time=t[0];
		for (int i=1;i<=n;i++)
			if (time+x<=t[i]) time=t[i];else time+=x;
		(time>t[n]) ? x-=h : x=x+h;
		h/=2.0;
	}
	cout.precision(9);
	(x<5) ? cout<<-1 : cout<<fixed<<x;
}