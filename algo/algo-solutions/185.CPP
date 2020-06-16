#include<iostream>
#include<vector>
using namespace std;
vector<int> v[10001];
int n,m,v1,v2;
int z[10001];

void dfs(int k) 
{
	int mx=-1;
	int s;
	if (v[k].empty()) z[k]=0;else 
	{
		for(int i=0;i<(int)v[k].size();i++) 
		{
			if (z[v[k][i]]==-1) dfs(v[k][i]);
			s=z[v[k][i]]+1;
			mx=max(mx,s);
		}
		z[k]=mx;
	}
}

int main() 
{
	scanf_s("%d%d",&n,&m);
	memset(z,-1,sizeof(z));
	for(int i=0;i<m;i++) 
	{
		scanf_s("%d%d",&v1,&v2);
		v[v1-1].push_back(v2-1);
	}
	for(int i=0;i<n;i++) 
	{
		if (z[i]==-1) dfs(i);
		printf("%d\n",z[i]);
	}
}