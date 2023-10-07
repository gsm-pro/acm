#include<cstdio>
#include<algorithm>
using namespace std;
#define forn(i,n) for (int i=0;i<(int)(n);++i)
int n,m,k;
int a[10000],b[10000];

int main()
{
	scanf("%d",&n);
	forn(i,n) scanf("%d",&a[i]);
	scanf("%d",&m);
	forn(i,m) scanf("%d",&b[i]);
	sort(a,a+n);
	sort(b,b+m);
	scanf("%d",&k);
	forn(i,k)
	{
		int c;
		scanf("%d",&c);
		int l=0;
		int r=m-1;
		bool flag=false;
		while (l<n && r>=0)
		{
			if (a[l]+b[r]>c) --r;else
				if (a[l]+b[r]<c) ++l;else
				{
					flag=true;
					break;
				}
		}
		(flag) ? puts("YES") : puts("NO");
	}
}