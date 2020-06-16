#include<iostream>
using namespace std;
int a[555][555]={0};

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,m,iMax=1,jMax=1,iMin,jMin;
	scanf_s("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			scanf_s("%d",&a[i][j]);
			if (a[i][j]>a[iMax][jMax]) iMax=i,jMax=j;
		}
	}
	iMin=1;
	for (int i=1;i<=n;i++)
		if (a[i][jMax]<a[iMin][jMax]) iMin=i;
	jMin=1;
	for (int j=1;j<=m;j++)
		if (a[iMax][j]<a[iMax][jMin]) jMin=j;
	printf("%d",a[iMin][jMin]);
}