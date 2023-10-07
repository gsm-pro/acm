#include<iostream>
using namespace std;
int n,m,nbox,a[16][16],t[16][1<<16],p[16][1<<16],s[1<<16],uz[16],k;

int calc(int v)
{
	int res=0;
	for (int i=0;i<n;i++)
		if ((v&(1<<i))!=0) 
			for (int j=0;j<n;j++)
				if ((v&(1<<j))==0) res+=a[i+1][j+1];  
	return res;
}

int main()
{
	cin>>n>>m>>nbox;
	for (int i=1;i<=m;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		a[x][y]=a[y][x]=z;
	}
	int ans=(int)1e9,num=(1<<n)-1;
	for (int i=0;i<num;i++)	s[i]=calc(i); 
	memset(t,-1,sizeof t);
	t[0][0]=0;  
	for (int i=0;i<nbox;i++)
	{
		for (int j=0;j<=num;j++)
		{
			if (t[i][j]==-1) continue;
			k=(j+1)|j;
			while (k<=num)
			{
				if (t[i+1][k]==-1 || t[i+1][k]>t[i][j]+s[k-j])
				{
					t[i+1][k]=t[i][j]+s[k-j];
					p[i+1][k]=j;
				}
				k=(k+1) | j;   
			}
		}
	}
	int j=num;
	for (int i=nbox;i>=1;i--)
	{
		k=j-p[i][j];
		for (int x=0;x<n;x++)
			if ((k&(1<<x))!=0) uz[x+1]=i;
		j=p[i][j];    
	}
	for (int i=1;i<=n;i++) cout<<uz[i]<<" ";
}