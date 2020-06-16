#include<iostream>
int c[32],n,a,b1,b2,c1,c2,k,x,i,j;

int main()
{
	scanf("%d",&n);
	for (i=0;i<n;i++)
	{
		scanf("%d",&a);
		if (!b1 || a==b1) b1=a,c1++;else
			if (!b2 || a==b2) b2=a,c2++;
		for (j=0;j<32;j++) c[j]+=(a>>j)&1;
	}
	k=std::max(c1,c2);
	for (i=0;i<32;i++) if (c[i]%k) x^=1<<i;
	printf("%d",x);
}