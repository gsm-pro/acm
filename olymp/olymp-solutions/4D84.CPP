#include<iostream>
using namespace std;
int z[101][101],prev[101][101],sz[101],cl[101],n;

int rec(int l,int r)
{
	if (r-l+1<=2) return 0;
	if (z[l][r]!=-1) return z[l][r];
	z[l][r]=0;
	for (int i=l+1;i<=r-1;i++)
	{
		int t=rec(l,i)+rec(i,r);
		if (t==r-l+1-3 && (sz[l]==sz[r] || cl[l]==cl[r])) t++;
		if (z[l][r]<t)
		{
			z[l][r]=t;
			prev[l][r]=i;
		}
	}
	return z[l][r];
}

void ans(int l,int r)
{
	if (r-l+1<=2) return;
	if (rec(l,r)==0) return;
	ans(l,prev[l][r]);
	ans(prev[l][r],r);
	if (z[l][r]==r-l+1-2) cout<<prev[l][r]+1<<" ";
}

int main() 
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n;
	for(int i=0;i<n;i++) cin>>sz[i]>>cl[i];
	memset(z,-1,sizeof(z));
	cout<<rec(0,n-1)<<endl;
	ans(0,n-1);
}