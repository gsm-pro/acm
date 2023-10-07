#include<iostream>
#include<cmath>
using namespace std;

int main()
{
	int n,i,a[100001],b[320],j=0,p=0,x;
	cin>>n;
	for (int i=0;i<100000;i++) a[i]=0;
	int bs=(int)sqrt(n+.0);
	for (i=0;i<320;i++) b[i]=bs;
	for (i=0;i<n;i++)
	{
		cin>>x;
		while (x-b[p]>=0) x-=b[p],p++;
		b[p]--,j=p*bs;
		while (x>=0)
		{
			while (a[j]!=0) j++;
			j++,x--;
		}
		a[j-1]=i+1,j=0,p=0;
	}
	for (i=0;i<n;i++) cout<<a[i]<<" ";
}