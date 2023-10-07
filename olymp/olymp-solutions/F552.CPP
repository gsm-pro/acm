#include<iostream>
#include<string>
using namespace std;
string s;
int n,m,f[12][12],ff[12][12],color,res=1<<9,t[12];

void push(int &dst,int &x)
{
	dst=(dst+x)%3;
}

void rec(int pos)
{
	if (pos==m+1)
	{
		int sum=0;
		memcpy(ff,f,sizeof f);
		for (int j=1;j<=m;j++)
		{
			push(ff[1][j],t[j]);
			push(ff[2][j],t[j]);
			push(ff[1][j+1],t[j]);
			push(ff[1][j-1],t[j]);
			sum+=t[j];
		}
		for (int i=2;i<=n+1;i++)
		{
			if (i==n+1)
			{
				for (int j=1;j<=m;j++)
					if (ff[n][j]!=color) return;
				res=min(res,sum);
				return;
			}
			for (int j=1;j<=m;j++)
			{
				for (int p=0;p<3;p++)
				{
					if ((ff[i-1][j]+p)%3!=color) continue;
					push(ff[i+1][j],p);
					push(ff[i-1][j],p);
					push(ff[i][j+1],p);
					push(ff[i][j-1],p);
					push(ff[i][j],p);
					sum+=p;
					break;
				}
			}
		}
	}
	for (int q=0;q<3;q++)
	{
		t[pos]=q;
		rec(pos+1);
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n>>m;
	for (int i=1;i<=n;i++)
	{
		cin>>s;
		for (int j=1;j<=m;j++)
			f[i][j]=(s[j-1]=='R') ? 0 : (s[j-1]=='G' ? 1 : 2);
	}
	for (color=0;color<3;color++) rec(1);
	cout<<(res==1<<9 ? -1 : res);
}