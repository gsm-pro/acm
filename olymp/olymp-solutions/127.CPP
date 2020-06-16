#include<iostream>
using namespace std;
int a,b,v;
char t[10];

int k3(int x,int y)
{
	int r=0;
	for (int i=x;i<=y;i++)
	{
		_itoa(i,t,10);
		if (strchr(t,'3')!=NULL) r++;
	}
	return r;
}

int go(int x)
{
	int y=x/10000,r=0;
	for (int i=0;i<y;i++)
	{
		_itoa(i,t,10);
		if (strchr(t,'3')!=NULL) r+=10000;else r+=v;
	}
	return r+k3(y*10000,x);
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	v=k3(0,9999);
	cin>>a>>b;
	cout<<go(b)-go(a)+k3(a,a);
}