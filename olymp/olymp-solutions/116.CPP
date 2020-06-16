#include<vector>
#include<iostream>
using namespace std;
long long a[51][51];
long long t;

long long calc(vector<vector<int>> &g)
{
	int v1=-1,v2;
	for(int i=0;(i<(int)g.size());i++)
	{
		for(int j=0;j<(int)g.size();j++)
		{
			if ((!g[i][j]) && (i!=j))
			{
				v1=i;
				v2=j;
				break;
			}
		}
	}
	if (v1<0) return a[t][g.size()];
	vector<vector<int>> g1=g;
	g1[v1][v2]=1;
	g1[v2][v1]=1;
	for(int i=0;i<(int)g.size();i++)
	{
		g[v1][i]=g[v1][i] || g[v2][i];
		g[i][v1]=g[v1][i];
	}
	vector<vector<int>> g2(g.size()-1,vector<int>(g.size()-1));
	int k=-1,p=-1;
	for(int i=0;i<(int)g.size();i++)
	{
		p=-1;
		k++;
		if (i==v2)
		{
			k--;
			continue;
		}
		for(int j=0;j<(int)g.size();j++)
		{
			p++;
			if (j==v2)
			{
				p--;
				continue;
			}
			g2[k][p]=g[i][j];
		}
	}
	return calc(g1)+calc(g2);
}

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	cin>>t;
	for(int i=1;i<51;i++) a[i][1]=i;
	for(int i=2;i<51;i++)
	{
		for(int j=2;j<=i;j++)
		{
			a[i][j]=a[i][j-1]*(i-j+1);
		}
	}
	vector<vector<char>> c(3,vector<char>(3));
	vector<vector<int>> num(3,vector<int>(3));
	int k=-1;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			cin>>c[i][j];
			if (c[i][j]=='x')
			{
				k++;
				num[i][j]=k;
			}
		}
	}
	vector<vector<int>> g(k+1,vector<int>(k+1));
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if (c[i][j]=='x')
			{
				for(int k=i+1;k<3;k++)
				{
					if (c[k][j]=='x')
					{
						g[num[i][j]][num[k][j]]=1;
						break;
					}
				}
				for(int k=i-1;k>=0;k--)
				{
					if (c[k][j]=='x')
					{
						g[num[i][j]][num[k][j]]=1;
						break;
					}
				}
				for(int k=j+1;k<3;k++)
				{
					if (c[i][k]=='x')
					{
						g[num[i][j]][num[i][k]]=1;
						break;
					}
				}
				for(int k=j-1;k>=0;k--)
				{
					if (c[i][k]=='x')
					{
						g[num[i][j]][num[i][k]]=1;
						break;
					}
				}
			}
		}
	}
	cout<<calc(g);
}