#include <iostream>
using namespace std;
#define N 12
int n,k,m,ans=0,used[20][20],z[N][N],k1,k2;
const int dx[4]={1,2,2,1};
const int dy[4]={-2,-1,1,2};
bool uh[12],ug[40],ud[40];

void rec(int v,int c)
{
	if (n-v<k-c) return;
	if (c==k) 
	{
		ans++;
		return;
	}
	rec(v+1,c);
	for(int i=0;i<n;i++) 
	{
		if (z[v][i]==1) continue;
		if (!used[v][i] && !uh[i] && !ug[i + v] && !ud[i - v + N])
		{
			for(int j=0;j<4;j++) ++used[v+dx[j]][i+dy[j]];
			uh[i]=ug[i+v]=ud[i-v+N]=true;
			rec(v+1,c+1);
			for(int j=0;j<4;j++) --used[v+dx[j]][i+dy[j]];
			uh[i]=ug[i+v]=ud[i-v+N]=false;
		}
	}
}

void main() 
{
	cin>>n>>k>>m;
	for (int i=0;i<m;i++)
	{
		cin>>k1>>k2;
		used[--k1][--k2]++;
	}
	rec(0,0);
	cout<<ans;
}