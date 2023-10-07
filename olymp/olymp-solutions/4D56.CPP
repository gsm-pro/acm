#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
int n,m;
vector<vector<int>> g;
int a,b,c;
vector<int> p;
vector<bool> used;
bool fnd;

void dfs(int v,int f)
{
	used[v]=true;
	if (v==f) fnd=true;
	for (int i=0;i<(int)g[v].size();i++)
	{
		if (fnd) return;
		int a=g[v][i];
		if (used[a]) continue;
		p[a]=v;
		dfs(a,f);
	}
}
 
int main() 
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>a>>b>>c;
	a--,b--,c--;
	cin>>n>>m;
	g.resize(n);
	while (m-->0)
	{
		int a,b;
		cin>>a>>b;
		a--,b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	p.clear();
	p.resize(n);
	p[a]=a;
	used.resize(n);
	used.assign(n,false);
	fnd=false;
	dfs(a,c);
	vector<int> a1;
	if (!used[c])
	{
		cout<<"NO";
		return 0;
	}
	a1.push_back(c);
	int v=c;
	while (v!=p[v])
	{
		a1.push_back(p[v]);
		v=p[v];
	}
	reverse(a1.begin(),a1.end());
	used.assign(n,false);
	p.clear();
	p.resize(n);
	p[c]=c;
	fnd=false;
	dfs(c,b);
	if (!used[b])
	{
		cout<<"NO";
		return 0;
	}
	vector<int> a2;
	a2.push_back(b);
	v=b;
	while (v!=p[v])
	{
		a2.push_back(p[v]);
		v=p[v];
	}
	reverse(a2.begin(),a2.end());
	cout<<"YES"<<endl;
	cout<<(int)a1.size()+(int)a2.size()-1<<" ";
	for (int i=0;i<(int)a1.size();i++) cout<<a1[i]+1<<" ";
	for (int i=1;i<(int)a2.size();i++) cout<<a2[i]+1<<" ";
}