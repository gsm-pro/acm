#include<cstdio>
using namespace std;
int n,p,k,q,w,a[10001],rev[1023];

void main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	scanf_s("%d %d",&n,&p);
	for(q=0;q<n;++q) scanf_s("%d",a+q);
	for(q=0;q<p;++q) rev[q]=0;
	for(q=1;q<p;++q)
		if (!rev[q])
		{
			for(w=q;q*w%p!=1;++w);
			rev[q]=w,rev[w]=q;
		}
	if (n==2)
	{
		puts("1 1");
		return;
	}
	if (k=a[2]*rev[a[1]]%p)
	{
		for(q=3;q<n;++q)
			if(a[q]!=a[q-1]*k%p) goto case_1;
			printf("1 %d",k);
			return;
		}
	case_1:
	if (k=a[2]*rev[a[0]]%p)
	{
		for(q=3;q<n;++q)
			if(a[q]!=a[q-1]*k%p) goto case_else;
		printf("2 %d",k);
		return;
	}
	case_else:
	int kol0=0;
	for (int i=0;i<n;i++)
		if (a[i]==0) kol0++;
	if (kol0==n-1)
	{
		for (int i=0;i<n;i++)
			if (a[i]!=0)
			{
				printf("%d 1",i+1);
				return;
			}
	}
	if (k=a[1]*rev[a[0]]%p)
		for(q=2;q<n;++q)
			if(a[q]!=a[q-1]*k%p)
			{
				printf("%d %d",q+1,k);
				return;
			}
}