#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

__int64 powmod(__int64 a,__int64 b,__int64 m)
{
	__int64 res=1;
	while (b>0)
		if (b&1)
			res=(res*a)%m,--b;
		else
			a=(a*a)%m,b>>=1;
	return res;
}
 
__int64 solve(int a,int b,int m)
{
	int sq1=(int)sqrt(m+.0)+1;
	int sq2=m/sq1+(m%sq1 ? 1 : 0);
	vector<pair<__int64,int>> v(sq2);
	for (int i=1;i<=sq2;++i)
		v[i-1]=make_pair(powmod(a,i*sq1,m),i);
	sort(v.begin(),v.end());
	for (int i=0;i<=sq1;++i)
	{
		__int64 cur=powmod(a,i,m);
		cur=(cur*b)%m;
		vector<pair<__int64,int>>::iterator it=lower_bound(v.begin(),v.end(),make_pair(cur,0));
		if (it!=v.end() && it->first==cur)
		{
			cur=(__int64)(((it->second)*sq1-i)%(m-1));
			return cur;
		}
	}
	return -1;
}

int main()
{
	int a,b,m;
	cin>>a>>b>>m;
	__int64 res=solve(a,b,m);
	if (res==-1) cout<<"No solution"; else cout<<res;
}