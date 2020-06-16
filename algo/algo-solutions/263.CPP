#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
using namespace std;
__int64 A[1001],R[1001],a[1001][2],d[1001][2];
int a_old=0,a_new=1,d_old=0,d_new=1,pos,n,k;

int main()
{
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d",&A[i]);
	scanf("%d",&k);
	a[0][a_old]=2;
	a[1][a_old]=a[n-1][a_old]=d[0][d_old]=1;
	while (k>0)
	{
		if (k%2==0)
		{
			for (int i=0;i<n;i++)
			{
				a[i][a_new]=0,pos=i;
				for (int j=0;j<n;j++)
				{
					a[i][a_new]+=a[j][a_old]*a[pos][a_old];
					(pos==0) ? pos=n-1 : pos--;
				}
				a[i][a_new]%=10000;
			}
			k>>=1;
			swap(a_old,a_new);
		}
		else
		{
			for (int i=0;i<n;i++)
			{
				d[i][d_new]=0,pos=i;
				for (int j=0;j<n;j++)
				{
					d[i][d_new]+=d[j][d_old]*a[pos][a_old];
					(pos==0) ? pos=n-1 : pos--;
				}
				d[i][d_new]%=10000;
			}
			swap(d_old,d_new);
			k--;
		}
	}
	for (int i=0;i<n;i++)
	{
		R[i]=0,pos=i;
		for (int j=0;j<n;j++)
		{
			R[i]+=A[j]*d[pos][d_old];
			(pos==0) ? pos=n-1 : pos--;
		}
		R[i]%=10000;
		printf("%d ",R[i]);
	}
}