#include<iostream>
#include<vector>
using namespace std;

class RMQSparseTable
{
	vector<int> a,logTable;
	vector<vector<int>> rmq;
	bool forMinimum;
public:
	RMQSparseTable(vector<int> &x,bool _forMinimum)
	{
		a=x;
		forMinimum=_forMinimum;
		int n=(int)a.size();
		logTable.resize(n+1);
		for (int i=2;i<=n;i++) logTable[i]=logTable[i>>1]+1;
		rmq.resize(logTable[n]+1);
		for (int i=0;i<(int)rmq.size();i++) rmq[i].resize(n);
		for (int i=0;i<n;++i) rmq[0][i]=i;
		for (int k=1;(1<<k)<n;++k)
		{
			for (int i=0;i+(1<<k)<=n;i++)
			{
				int x=rmq[k-1][i],y=rmq[k-1][i+(1<<(k-1))];
				rmq[k][i]=(forMinimum ? (a[x]<=a[y] ? x : y) : (a[x]>=a[y] ? x : y));
			}
		}
	}

	int query(int lf,int rg)
	{
		int k=logTable[rg-lf],x=rmq[k][lf],y=rmq[k][rg-(1<<k)+1];
		return (forMinimum ? (a[x]<=a[y] ? x : y) : (a[x]>=a[y] ? x : y));
	}
};

int main()
{
	int n,d,maxV=-(1<<30),cnt=0;
	scanf_s("%d%d",&n,&d);
	vector<int> w(n);
	for (int i=0;i<n;i++) scanf_s("%d",&w[i]);
	RMQSparseTable t1(w,false),t2(w,true);
	for (int i=0;i<n-d+1;i++)
	{
		int r=w[t1.query(i,i+d-1)]-w[t2.query(i,i+d-1)];
		if (r>maxV) maxV=r,cnt=0;
		if (r==maxV) cnt++;
	}
	printf("%d %d",maxV,cnt);
}