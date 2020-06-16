#include<iostream>
#include<vector>
using namespace std;
vector<int> v[10001];
int n,m,v1,v2;
long long z[10001];

void dfs(int k) 
{
	for(int i=0;i<(int)v[k].size();i++) 
	{
		if (z[v[k][i]]==0) dfs(v[k][i]);
		z[k]+=z[v[k][i]]+1;
	}
}

int main() 
{
	scanf_s("%d%d",&n,&m);
	memset(z,0,sizeof(z));
	for(int i=0;i<m;i++) 
	{
		scanf_s("%d%d",&v1,&v2);
		v[v1-1].push_back(v2-1);
	}
	for(int i=0;i<n;i++) 
	{
		if (z[i]==0) dfs(i);
		cout<<z[i]+1<<endl;
	}
}