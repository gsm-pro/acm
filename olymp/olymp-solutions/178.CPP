#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
#define LL long long

class Pair
{
public:
	LL value;
	int origin,cnt;
	Pair(){}
	Pair(LL _value,int _origin,int _cnt)
	{
		value=_value;
		origin=_origin;
		cnt=_cnt;
	}
};

bool operator < (const Pair &a,const Pair &b)
{
	return a.value>b.value;
}

int n,k;
vector<LL> a;
vector<LL> res;
priority_queue<Pair> q;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n>>k;
	a.resize(n);
	for (int i=0;i<n;i++) cin>>a[i];
	sort(a.begin(),a.end());
	for (int i=0;i<n;i++) q.push(Pair(a[i],i,1));
	res.push_back(1);
	while (res.size()!=k+1)
	{
		Pair pr=q.top();
		q.pop();
		LL val=pr.value;
		if (val!=res.back()) res.push_back(val);
		q.push(Pair(a[pr.origin]*res[pr.cnt],pr.origin,pr.cnt+1));
	}
	cout<<res.back();
}