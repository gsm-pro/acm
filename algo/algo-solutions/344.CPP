#include <iostream>
using namespace std;
int g[30],n,m,e,best,gr,mask_best,mask1[30];

void rec(int k,int get,int cnt,int mask)
{
	if (k==n)
	{
		if (mask==gr)
		{
			best=cnt;
			mask_best=get;
		}
		return;
	}
	if (((mask|mask1[k])!=gr)||(cnt>=best)) return;
	if ((mask|g[k])!=mask) rec(k+1,get|(1<<k),cnt+1,mask|g[k]);
	rec(k+1,get,cnt,mask);
}

int main()
{
	while (cin>>n>>m>>e)
	{
		for (int i=0;i<n;i++) g[i]=0;
		for (int i=0;i<e;i++)
		{
			int u,v;
			cin>>u>>v;
			g[u-1]|=(1<<(v-1));
		}
		mask1[n-1]=g[n-1];
		for (int i=n-2;i>=0;i--) mask1[i]=mask1[i+1]|g[i];
		gr=(1<<m)-1;
		best=n+1;
		mask_best=0;
		rec(0,0,0,0);
		if (best>n) best=-1;
		cout<<best<<endl;
		for (int i=0;i<n;i++) if (mask_best&(1<<i)) cout<<i+1<<" ";
		cout<<endl;
	}
}