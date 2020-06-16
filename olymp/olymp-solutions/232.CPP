#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
#define fn(e1,e2) min(e1,e2);
#define inf 999999
vector<int> t;
int n,m;
vector<pair<int,pair<int,int>>> sob;

int res(int l,int r,int i=1,int tl=0,int tr=n-1)
{
	if (l==tl && r==tr) return t[i];
	int m=(tl+tr)/2;
	if (r<=m) return res(l,r,i*2,tl,m);
	if (l> m) return res(l,r,i*2+1,m+1,tr);
	return fn(res(l,m,i*2,tl,m),res(m+1,r,i*2+1,m+1,tr));
}

void update(int pos,int newval,int i=1,int l=0,int r=n-1)
{
	if (l==r) t[i]=newval;else
	{
		int m=(l+r)/2;
		if (pos<=m) update(pos,newval,i*2,l,m);
		else update(pos,newval,i*2+1,m+1,r);
		t[i]=fn(t[i*2],t[i*2+1]);
	}
}

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	scanf("%d%d",&n,&m);
	for (int i=0;i<=m-1;i++)
	{
		int t1,t2,c;
		scanf("%d%d%d",&t1,&t2,&c);
		sob.push_back(make_pair(t1,make_pair(i,c-1)));
		sob.push_back(make_pair(t2,make_pair(i,c-1)));
	}
	sort(sob.begin(),sob.end());
	t.resize(n*4+1);
	for (int i=0;i<=n-1;i++) update(i,i);
	vector<bool> was(m,false);
	vector<int> place(m);
	for (int i=0;i<(int)sob.size();i++)
	{
		int pl;
		int num=sob[i].second.first;
		int c=sob[i].second.second;
		if (was[num])
		{
			pl=place[num];
			update(pl,pl);
		} else {
			pl=res(c,n-1);
			if (pl==inf) pl=res(0,c-1);
			update(pl,inf);
			was[num]=true;
			place[num]=pl;
		}
	}
	for (int i=0;i<m;i++) printf("%d\n",place[i]+1);
}