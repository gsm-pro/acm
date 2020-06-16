#include<iostream>
using namespace std;
long double x[2][20002]={0},y[2][20002]={0},w[20002]={0},k=0.0;
int n,m,a[6],b[6];

int main()
{
	cin>>n;
	int p=0,q=1,u=0,v=1;
	for (int i=0;i<6;i++) 
	{
		cin>>a[i];
		x[p][a[i]]+=(1.0/6.0);
	}
	cin>>m;
	for (int i=0;i<6;i++) 
	{
		cin>>b[i];
		y[u][b[i]]+=(1.0/6.0);
	}
	for (int i=1;i<=n-1;i++)
	{
		memset(x[q],0,sizeof x[q]);
		for (int j=1;j<=20000;j++)
			if (x[p][j]>0)
				for (int h=0;h<6;h++)
					x[q][j+a[h]]+=(x[p][j]/6);
		swap(p,q);
	}
	for (int i=1;i<=m-1;i++)
	{
		memset(y[v],0,sizeof y[v]);
		for (int j=1;j<=20000;j++)
			if (y[u][j]>0)
				for (int h=0;h<6;h++)
					y[v][j+b[h]]+=(y[u][j]/6);
		swap(u,v);
	}
	for (int i=1;i<=20000;i++) w[i]=w[i-1]+y[u][i];
	for (int i=1;i<=20000;i++) k+=(w[i-1]*x[p][i]);
	cout.precision(15);
	cout<<fixed<<k;
}