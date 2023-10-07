#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
#define x first
#define men second
int N,K;
vector<pair<int,int>> X;
double Y[10000];

int get(double U)
{
	int a=0;
	Y[0]=X[0].x+U/X[0].men;
	for (int i=1;i<N;i++)
	{
		if (Y[a]>X[i].x)
		{
			if ((Y[a]-X[i].x)*X[i].men>U) Y[a]=X[i].x+U/X[i].men;
		}
		else if ((X[i].x-Y[a])*X[i].men>U)
		{
			a++;
			Y[a]=X[i].x+U/X[i].men;
		}
	}
	return a+1;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	double d,y0,y1;
	scanf("%d%d",&N,&K);
	X.resize(N);
	for (int i=0;i<N;i++) scanf("%d",&X[i].x);
	for (int i=0;i<N;i++) scanf("%d",&X[i].men);
	sort(X.begin(),X.end());
	y0=double(X[0].x+X[N-1].x)/2,y1=0;
	for (int i=0;i<N;i++)
	{
		d=fabs(y0-X[i].x)*X[i].men;
		if (d>y1) y1=d;
	}
	y0=0;
	do
	{
		d=(y1+y0)/2;
		int w=get(d);
		if (w>K) y0=d;else y1=d;
	} while (y1-y0>1e-10);
	int w=get(y1);
	for (int i=0;i<K;i++) printf("%lf ",Y[i]);
}