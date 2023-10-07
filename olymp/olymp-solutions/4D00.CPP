#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;
vector<vector<int>> g;
vector<pair<int,int>> rib;
set<int> v;
int comp[111]={0},used[111]={0},n,comp_count=0,ans=0;

void dfs(int v,int nc)	
{
	used[v]=1,comp[v]=nc;
	for (int i=0;i<(int)g[v].size();i++)
	{
		int to=g[v][i];
		if (!used[to]) dfs(to,nc);
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n;
	vector<int> aa(n),bb(n),a,b;
	for (int i=0;i<n;i++) cin>>aa[i];
	bb=aa;
	sort(bb.begin(),bb.end());
	for (int i=0;i<n;i++)
	{
		if (aa[i]!=bb[i])
		{
			a.push_back(aa[i]);
			b.push_back(bb[i]);
		}
	}
	n=(int)a.size();
	g.resize(n);
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			if (a[i]==b[j])
			{
				g[i].push_back(j);
				g[j].push_back(i);
				rib.push_back(make_pair(i,j));
			}
		}
	}
	for (int i=0;i<n;i++)
		if (!used[i]) dfs(i,++comp_count);
	for (int i=1;i<=comp_count;i++)
	{
		v.clear();
		bool ok=true;
		for (int j=0;j<(int)rib.size();j++)
		{
			if (comp[rib[j].first]==i && comp[rib[j].second]==i)
			{
				swap(a[rib[j].first],a[rib[j].second]);
				int org=0;
				for (int t=0;t<n;t++)
					if (a[t]==b[t]) org++;
				if (org!=2) ok=false;
				v.insert(rib[j].first);
				v.insert(rib[j].second);
				swap(a[rib[j].first],a[rib[j].second]);
			}
		}
		ans+=(ok ? v.size()/2 : v.size()-1);
	}
	cout<<ans;
}