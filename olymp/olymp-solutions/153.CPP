#include<iostream>
using namespace std;
int n,k;
int d[33];
int m[33][33];
int l[33],ac[33],lc[33];
int cv[33][5555],acs[33][5555];
int lt[5555],cc[5555];

void rec(int g)
{
	k--;
	if (k==0) 
	{
		for (int i=1;i<=g;i++) cout<<char(lt[i]+'a'-1);
		exit(0);
	}
	memset(ac,0,sizeof ac);
	memset(lc,0,sizeof ac);
	for (int i=1;i<=cc[g];i++)
		for (int j=1;j<=d[cv[i][g]];j++)
			ac[m[cv[i][g]][j]]=1;
	for (int i=1;i<=n;i++)
	{
		acs[i][g]=ac[i];
		if (ac[i]>0) lc[l[i]]=1;
	}
	for (int i=1;i<=26;i++)
	{
		if (lc[i]>0)
		{
			lt[g+1]=i,cc[g+1]=1;
			for (int j=1;j<=n;j++)
				if (l[j]==i && ac[j]>0)
					cc[g+1]++,cv[cc[g+1]][g+1]=j;
			rec(g+1);
			for (int q=1;q<=n;q++) ac[q]=acs[q][g];
			memset(lc,0,sizeof ac);
			for (int q=1;q<=n;q++)
				if (ac[q]>0) lc[l[q]]=1;
		}
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n>>k;
	for (int i=1;i<=n;i++)
	{
		char ch;
		cin>>ch;
		l[i]=ch-'a'+1;
		cin>>d[i];
		for (int j=1;j<=d[i];j++) cin>>m[i][j];
	}
	for (int j=1;j<=26;j++)
	{
		lt[1]=j,cc[1]=0;
		for (int i=1;i<=26;i++)
			if (l[i]==j) cc[1]++,cv[cc[1]][1]=i;
		if (cc[1]>0) rec(1);
	}
}