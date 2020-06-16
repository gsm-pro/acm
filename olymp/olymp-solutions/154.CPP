#include<iostream>
#define max 2000
char s1[max],s2[max];
int A[max],B[max],d[max],fr[max],frt[max],r1[max],r2[max],rp,L1,L2,n;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d%d%s%s",&L1,&L2,s1,s2);
	int n=(int)strlen(s2);
	for (int i=0;i<=n;i++)
	{
		char cc;
		char *p;
		int l=0,u=n-i;
		while (l<u)
		{
			int m=(l+u+1)/2;
			cc=s2[i+m];
			s2[i+m]=0;
			p=strstr(s1,s2+i);
			if (p) l=m;else u=m-1;
			s2[i+m]=cc;
		}
		cc=s2[i+l],s2[i+l]=0;
		p=strstr(s1,s2+i);
		s2[i+l]=cc,A[i]=(int)(p-s1),B[i]=l;
	}
	d[0]=0;
	for (int i=1;i<=n;i++) d[i]=(1<<29);
	for (int i=0;i<=n;i++)
	{
		for (int j=1;j<=n-i;j++)
		{
			if (B[i]>=j && d[i+j]>d[i]+L1)
				d[i+j]=d[i]+L1,fr[i+j]=j,frt[i+j]=0;
			if (d[i+j]>d[i]+L2+j)
				d[i+j]=d[i]+L2+j,fr[i+j]=j,frt[i+j]=1;
		}
	}
	int i=n;
	while(i>0)
		r1[rp]=fr[i],r2[rp]=frt[i],rp++,i-=fr[i];
	printf("%d\n%d\n",d[n],rp);
	int pp=0;
	for (int i=rp-1;i>=0;i--)
	{
		if (r2[i]==0)
			printf("Old %d %d\n",A[pp]+1,r1[i]);
		else
		{
			char cc=s2[pp+r1[i]];
			s2[pp+r1[i]]=0;
			printf("New %s\n",s2+pp);
			s2[pp+r1[i]]=cc;
		}
		pp+=r1[i];
	}
}