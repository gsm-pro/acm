#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define LL long long
vector<pair<LL,LL>> p,q;
int n;
LL lf,rg;
vector<pair<int,pair<LL,LL>>> rights;

class RMQSparseTable
{
	vector<LL> a;
	vector<int> logTable;
	vector<vector<int>> rmq;
public:
	RMQSparseTable(vector<LL> &x);
	int maxPos(int i,int j);
};

RMQSparseTable::RMQSparseTable(vector<LL> &x)
{
	a=x;
	int n=(int)a.size();
	logTable.resize(n+1);
	for (int i=2;i<=n;i++) logTable[i]=logTable[i>>1]+1;
	rmq.resize(logTable[n]+1);
	for (int i=0;i<(int)rmq.size();i++) rmq[i].resize(n);
	for (int i=0;i<n;++i) rmq[0][i]=i;
	for (int k=1;(1<<k)<n;++k)
		for (int i=0;i+(1<<k)<=n;i++)
		{
			int x=rmq[k-1][i];
			int y=rmq[k-1][i+(1<<(k-1))];
			rmq[k][i]=(a[x]>=a[y] ? x : y);
		}
}

int RMQSparseTable::maxPos(int i,int j)
{
	int k=logTable[j-i];
	int x=rmq[k][i];
	int y=rmq[k][j-(1<<k)+1];
	return a[x]>=a[y] ? x : y;
}

pair<LL,LL> count(int msk,vector<pair<LL,LL>> &x)
{
	pair<LL,LL> res;
	for (int i=31;i>=0;i--)
		if (msk&(1LL<<i)) res.first+=x[i].first,res.second+=x[i].second;
	return res;
}

int cmp(pair<int,pair<LL,LL>> &a,pair<int,pair<LL,LL>> &b)
{
	return a.second.first<b.second.first;
}

int main()
{
	cin>>n>>lf>>rg;
	int t=n>>1;
	p.resize(t);
	q.resize(n-t);
	for (int i=0;i<t;i++)
		cin>>p[i].first>>p[i].second;
	for (int i=t;i<n;i++)
		cin>>q[i-t].first>>q[i-t].second;
	for (int i=0;i<(1<<q.size());i++)
		rights.push_back(make_pair(i,count(i,q)));
	sort(rights.begin(),rights.end(),cmp);
	vector<LL> w_rg(rights.size());
	vector<LL> c_rg(rights.size());
	for (int i=0;i<(int)rights.size();i++)
	{
		w_rg[i]=rights[i].second.first;
		c_rg[i]=rights[i].second.second;
	}
	RMQSparseTable table(c_rg);
	LL maxC=-1,bestL=0,bestR=0;
	for (int i=0;i<(1<<p.size());i++)
	{
		pair<LL,LL> e=count(i,p);
		int p1=lower_bound(w_rg.begin(),w_rg.end(),lf-e.first)-w_rg.begin();
		int p2=upper_bound(w_rg.begin(),w_rg.end(),rg-e.first)-w_rg.begin();
		if (p1>p2-1) continue;
		int index=table.maxPos(p1,p2-1);
		pair<LL,LL> f=count(rights[index].first,q);
		if (e.second+f.second>maxC)
		{
			maxC=e.second+f.second;
			bestL=i;
			bestR=rights[index].first;
		}
	}
	vector<int> ans;
	for (int i=31;i>=0;i--) if (bestL&(1LL<<i)) ans.push_back(i+1);
	for (int i=31;i>=0;i--) if (bestR&(1LL<<i)) ans.push_back(i+1+p.size());
	sort(ans.begin(),ans.end());
	cout<<(int)ans.size()<<endl;
	for (int i=0;i<(int)ans.size();i++) cout<<ans[i]<<" ";
}