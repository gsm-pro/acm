#include<cstdio>
using namespace std;
enum {MAXN=1024};

int main()
{
	int n,q,temp,t,cur,res;
	int a[1024];
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf_s("%u",&n);  
	for (q=0;q<MAXN;++q) a[q]=0;
	for (q=0;q<n;++q)
	{
		scanf_s("%u",&temp);
		++a[temp];
	}
	scanf_s("%u",&t);  
	cur=0,res=0,++t;
	for (q=1;q<=t;++q) cur+=a[q];
	res=cur;
	for (q=1;q+t<MAXN;++q)
		if ((cur+=a[q+t]-a[q])>res) res=cur;
	printf("%u",res);
}