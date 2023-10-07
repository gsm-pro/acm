#include <iostream>
using namespace std;
#define N 13
int n,k,ans,p[N];
bool d1[2*N],d2[2*N],used[N];

void Rec(int idx,int c)
{
	if (c>k || c+n-idx<k) return;
	if (idx==n)
	{
		if (c==k) ans++;
		if (p[0]!=-1 && 2*p[0]!=n-1) ans++;
		return;
	}
	for(int i=0;i<n;i++)
	{
		if (used[i] || d1[i+idx] || d2[i-idx+n]) continue;
		if (idx>0)
		{
			if (p[idx-1]!=-1 && (p[idx-1]==i-2 || p[idx-1]==i+2)) continue;
			if ((idx>1) && (p[idx-2]!=-1 && (p[idx-2]==i-1 || p[idx-2]==i+1))) continue;
		}
		else 
			if (2*i>=n) break;
		d1[i+idx]=d2[i-idx+n]=used[i]=true;
		p[idx]=i;
		Rec(idx+1,c+1);
		d1[i+idx]=d2[i-idx+n]=used[i]=false;
	}
	p[idx]=-1;
	Rec(idx+1,c);
}

void main()
{
	cin>>n>>k;
	Rec(0,0);
	cout<<ans;	
}