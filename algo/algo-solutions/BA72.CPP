#include<iostream>
#include<vector>
using namespace std;
vector<vector<pair<int,pair<double,double>>>> e;
vector<double> p;
vector<bool> used;
int n,prev;
double w,w1,w2;
vector<int> ans;

void dfs(int v)
{
	if (used[v]) return;
	used[v]=true;
	for (int i=0;i<(int)e[v].size();i++)
	{
		int t=e[v][i].first;
		double e1=e[v][i].second.first,e2=e[v][i].second.second;
		p[t]=p[v]*e1+(1-p[v])*e2;
		dfs(t);
	}
}

int main()
{
	cin>>n;
	e.resize(n);
	p.resize(n);
	used.resize(n);
	cin>>w;
	p[0]=(w+.0)/100.0;
	for (int i=1;i<n;i++)
	{
		cin>>prev>>w1>>w2;
		e[prev].push_back(make_pair(i,make_pair((w1+.0)/100.0,(w2+.0)/100.0)));
	}
	dfs(0);
	double c,d;
	cin>>c>>d;
	c/=100.0,d/=100.0;
	for (int i=0;i<n;i++)
		if (p[i]>c && p[i]<d) ans.push_back(i);
	cout<<(int)ans.size()<<endl;
	for (int i=0;i<(int)ans.size();i++) cout<<ans[i]<<" ";
}