#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
using namespace std;
int b[100001],c[3]={-1,-1,-1},pos[100001],n,z;
char res[100001];

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		scanf("%d",&z);
		pos[z-1]=i;
	}
	for (int i=0;i<n;i++)
	{
		scanf("%d",&b[i]);
		--b[i];
	}
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<4;j++)
		{
			if (j==3)
			{
				puts("NO");
				return 0;
			}
			if (pos[b[i]]>c[j])
			{
				c[j]=max(c[j],pos[b[i]]);
				res[b[i]]="RGB"[j];
				break;
			}
		}
	}
	printf("%s",res);
}