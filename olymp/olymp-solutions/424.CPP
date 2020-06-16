#include<iostream>
#include<vector>
#include<set>
using namespace std;
int m[50][50],n;
vector<bool> used;
vector<int> pr,num;

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	cin>>n;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++) cin>>m[i][j];
	int root=-1;
	used.resize(n);
	pr.resize(n);
	num.resize(n);
	for (int i=0;i<n;i++)
	{
		bool ok=true;
		for (int j=1;j<n;j++) ok=ok && (m[i][j]==m[i][j-1]);
		if (ok) root=i;
	}
	used[root]=true;
	pr[root]=-1;
	num[root]=1;
	set<int> w;
	for (int v=1;v<n;v++)
	{
		for (int i=0;i<n;i++)
		{
			if (used[i]) continue;
			w.clear();
			for (int j=0;j<n;j++) w.insert(m[i][j]);
			bool ok=true;
			for (set<int>::iterator it=w.begin();it!=w.end();it++)
				if (*it!=i && !used[*it]) ok=false;
			if (!ok) continue;
			int last=0;
			int nlast=0;
			for (set<int>::iterator it=w.begin();it!=w.end();it++)
			{
				if (num[*it]>last)
				{
					last=num[*it];
					nlast=*it;
				}
			}
			pr[i]=nlast;
			num[i]=v+1;
			used[i]=true;
			break;
		}
	}
	for (int i=0;i<n;i++) cout<<pr[i]<<" ";
}