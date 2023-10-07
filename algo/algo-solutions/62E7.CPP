#include<iostream>
#include<algorithm>
#include<vector>
#define forn(i,n) for(int (i)=0;(i)<(n);(i)++) 
using namespace std;
vector<bool> used(101,false);
int g[101][101],n;
vector<int> way;

void dfs(int v)
{
	if(!used[v])
	{
		used[v]=true;
		forn(i,n)
			if (g[v][i]==1) dfs(i);
		way.push_back(v);
	}
}

int main()
{
	cin>>n;
	forn(i,n)
		forn(j,n)
			cin>>g[i][j];
	forn(i,n)
		if (!used[i])
			dfs(i);
	reverse(way.begin(),way.end());
	for(int i=0;i<(int)way.size();i++)
		cout<<way[i]+1<<" ";
}