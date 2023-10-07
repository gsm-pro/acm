#pragma comment(linker,"/stack:256000000")
#include<iostream>
#include<set>
#include<vector>
#include<cmath>
using namespace std;
set<vector<char>> s;
vector<char> ans;
int cnt[20],nm,k,n,m;

void rec(int pos)
{
	if (pos==nm)
	{
		printf("%d\n",nm);
		for (int i=0;i<nm;i++) printf("%d ",ans[i]);
		exit(0);
	}
	vector<char> r(m);
	int c=0;
	for (int j=pos-m+1;j<=pos-1;j++) r[c++]=ans[j];
	for (int t=1;t<=n;t++)
	{
		if (cnt[t]<k)
		{
			r[m-1]=t;
			if (!s.count(r))
			{
				s.insert(r);
				ans[pos]=t;
				cnt[t]++;
				rec(pos+1);
				cnt[t]--;
				s.erase(r);
			}
		}
	}
}

int main()
{
	cin>>n>>m;
	if (n==1)
	{
		cout<<1<<endl<<1;
		return 0;
	}
	vector<char> q;
	nm=(int)pow(n+.0,m+.0),k=(int)pow(n+.0,m-1.0);;
	ans.resize(nm);
	for (int i=1;i<=m;i++)
	{
		ans[i-1]=1;
		q.push_back(1);
		cnt[1]++;
	}
	s.insert(q);
	q.clear();
	for (int i=1;i<=n-1;i++) q.push_back(m);
	q.push_back(1);
	s.insert(q);
	rec(m);
}