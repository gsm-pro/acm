#include<iostream>
using namespace std;
int x[8],n,r=0;

void rec(int i,int j)
{
	if (j==n)
	{
		if (i==n-1)
		{
			if (!x[n-1]) r++;
			return;
		}
		if (!x[i]) rec(i+1,i+2);
		return;
	}
	if (x[i]>(n-j)*3) return;
	if (x[i]>2)
	{
		x[i]-=3;
		rec(i,j+1);
		x[i]+=3;
	}
	if (x[j]>2)
	{
		x[j]-=3;
		rec(i,j+1);
		x[j]+=3;
	}
	if (x[i] && x[j])
	{
		x[i]--,x[j]--;
		rec(i,j+1);
		x[i]++,x[j]++;
	}
}

int main()
{
	cin>>n;
	for (int i=0;i<n;i++) cin>>x[i];
	rec(0,1);
	cout<<r;
}