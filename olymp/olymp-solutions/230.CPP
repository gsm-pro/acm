#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<map>
using namespace std;
map<char,int> l,r,t,b,symb;
map<char,int>::iterator it,it1,it2,it3,it4;
vector<string> w(101);
int n,m;
vector<vector<int>> g(101);
bool used[101];
vector<int> ans;
vector<char> letter(101);

void dfs(int v)
{
	if (!used[v])
	{
		used[v]=true;
		for (int i=0;i<(int)g[v].size();i++) dfs(g[v][i]);
		ans.push_back(v);
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>m>>n;
	for (int i=0;i<n;i++) cin>>w[i];
	m=(int)w[0].size();
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
		{
			char z=w[i][j];
			l[z]=101,r[z]=-1,t[z]=101,b[z]=-1;
		}
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
		{
			char z=w[i][j];
			l[z]=min(l[z],j),r[z]=max(r[z],j),
			t[z]=min(t[z],i),b[z]=max(b[z],i);
		}
	int i=-1;
	for (it=l.begin();it!=l.end();it++) symb[it->first]=(++i);
	it1=l.begin(),it2=r.begin(),it3=t.begin(),it4=b.begin();
	for (;it1!=l.end();)
	{
		int left=it1->second,right=it2->second,top=it3->second,bottom=it4->second;
		char q=it1->first;
		int num=symb.find(q)->second;
		char z;
		it1++,it2++,it3++,it4++;
		if (q=='.') continue;
		for (int i=left;i<=right;i++)
		{
			z=w[top][i];
			if (z!=q) g[num].push_back(symb.find(z)->second);
			z=w[bottom][i];
			if (z!=q) g[num].push_back(symb.find(z)->second);
		}
		for (int i=top;i<=bottom;i++)
		{
			z=w[i][left];
			if (z!=q) g[num].push_back(symb.find(z)->second);
			z=w[i][right];
			if (z!=q) g[num].push_back(symb.find(z)->second);
		}
	}
	for (int i=0;i<101;i++)
	{
		sort(g[i].begin(),g[i].end());
		g[i].erase(unique(g[i].begin(),g[i].end()),g[i].end());
	}
	memset(used,false,sizeof(used));
	for (int i=0;i<(int)symb.size();i++)
		if (!used[i]) dfs(i);
	for (it=symb.begin();it!=symb.end();it++)
		letter[it->second]=it->first;
	reverse(ans.begin(),ans.end());
	for (int i=0;i<(int)ans.size();i++) 
		if (letter[ans[i]]!='.') cout<<letter[ans[i]];
}