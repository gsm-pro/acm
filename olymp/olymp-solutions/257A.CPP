#include<vector>
#include<iostream>
#define LL long long
using namespace std;
int n,m;
vector<LL> a,b;
LL k,v,w;

LL count(LL z)
{
	LL l=0;
	int i,u,v,w;
	if (z<=b[m>>1]*a[n>>1])
	{
		for (w=n,i=0;i<m;i++) 
		{
			for (v=0;v<w;) 
			{
				u=(v+w)>>1;
				if (z<b[i]*a[u]) w=u;else v=u+1;
			}
			l+=v;
		}
	} else {
		for (v=0,i=m-1;i>=0;i--) 
		{
			for (w=n;v<w;) 
			{
				u=(v+w)>>1;
				if (z<b[i]*a[u]) w=u;else v=u+1;
			}
			l+=v;
		}
	}
	return l;
}

int main() 
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	cin>>n>>k;
	a.resize(n);
	for (int i=0;i<n;i++) a[i]=i+1;
	b=a,m=n;
	for (v=a[0]*b[0]-1,w=a[n-1]*b[m-1]+1;v<w;)
	{
		LL u=(v+w)>>1; 
		LL t=count(u);
		(k<=t) ? w=u : v=u+1;
	}
	cout<<v;
}