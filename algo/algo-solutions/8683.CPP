#include<iostream>
using namespace std;
int z[128001];
char s[128001];

int main()
{
	while (scanf("%s",s)==1)
	{
		int n=(int)strlen(s),l=0,r=0;
		z[0]=n;
		for (int i=1;i<n;i++)
		{
			z[i]=0;
			if (i>=l && i<r) z[i]=min(z[i-l],r-i);
			while (s[z[i]]==s[i+z[i]]) z[i]++;
			if (i+z[i]>r) l=i,r=i+z[i];
			printf("%d ",z[i]);
		}
		printf("\n");
	}
}