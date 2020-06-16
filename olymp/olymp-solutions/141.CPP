#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<algorithm>
using namespace std;
map<string,int> w;
map<string,int>::iterator it;
vector<vector<int>> g;
int n,m;
bool was[5000];
vector<int> used, path;

bool rec(int cur,int pred)
{
	if (used[cur]==2) return false;
	path.push_back(cur);
	if (used[cur]==1) return true;
	used[cur]=1;
	for (vector<int>::iterator it=g[cur].begin();it!=g[cur].end();++it)
		if (*it!=pred)
			if (rec(*it,cur))
				return true;
	used[cur]=2;
	path.pop_back();
	return false;
}

void dfs(int v)
{
	was[v]=true;
	for (int i=0;i<(int)g[v].size();i++)
		if (!was[g[v][i]]) dfs(g[v][i]);
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n>>m;
	string n1[5000],n2[5000];
	vector<string> names;
	for (int i=0;i<m;i++)
	{
		cin>>n1[i]>>n2[i];
		names.push_back(n1[i]);
		names.push_back(n2[i]);
	}
	sort(names.begin(),names.end());
	names.erase(unique(names.begin(),names.end()),names.end());
	for (int i=0;i<(int)names.size();i++) w[names[i]]=i;
	g.resize(n);
	for (int i=0;i<m;i++)
	{
		it=w.find(n1[i]);
		int a=it->second;
		it=w.find(n2[i]);
		int b=it->second;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	int cnt=0;
	for (int i=0;i<n;i++)
	{
		if (!was[i])
		{
			dfs(i);
			cnt++;
		}
	}
	if (cnt==1) cout<<"Yes\n\n";else cout<<"No\n"<<cnt-1<<endl;
	used.assign(n,0);
	path.clear();
	bool hasCycle=false;
	for (int i=0;i<n && !hasCycle;i++)
	{
		if (!used[i])
			if (rec(i,-1))
			{
				vector<int>::iterator it=find(path.begin(),path.end(),path.back());
				if (path.end()-it-1<3) continue;
				cout<<"No\n";
				int t=*it;
				if (t==(int) names.size()-1) cout<<names[path[t]]<<" "<<names[path[t-1]];
							else cout<<names[*it]<<" "<<names[*it+1];
				hasCycle=true;
			}
	}
	if (!hasCycle) cout<<"Yes\n\n";
}