#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef vector<int> VI;
#define forn(i,n) for(int i=0;i<int(n);i++)
int n,k,ans=(1<<9);
vector<VI> pSet,pSet1[6],pSet2[6];
VI p,q;

VI rev(VI &x)
{
	VI res(n);
	forn(i,n) res[x[i]]=i;
	return res;
}

VI mul(VI &x,VI &y)
{
	VI res(n);
	forn(i,n) res[i]=x[y[i]];
	return res;
}

void rec(int len,int cnt,VI &pp,VI &qq)
{
	if (cnt==len)
	{
		pSet1[len].push_back(pp);
		pSet2[len].push_back(qq);
		if (pp==q) ans=min(ans,len);
		return;
	}
	forn(i,k) rec(len,cnt+1,mul(pp,pSet[i]),mul(qq,rev(pSet[i])));
}

int main()
{
	cin>>n;
	p.resize(n);
	q.resize(n);
	forn(i,n)
	{
		cin>>p[i];
		p[i]--;
	}
	forn(i,n)
	{
		cin>>q[i];
		q[i]--;
	}
	cin>>k;
	pSet.resize(k,VI(n));
	forn(i,k)
	{
		forn(j,n)
		{
			cin>>pSet[i][j];
			pSet[i][j]--;
		}
	}
	forn(len,6) rec(len,0,p,q);
	forn(len,6)
	{
		sort(pSet1[len].begin(),pSet1[len].end());
		sort(pSet2[len].begin(),pSet2[len].end());
	}
	for (int len2=1;len2<6;len2++)
	{
		forn(i,pSet1[5].size())
		{
			if (binary_search(pSet2[len2].begin(),pSet2[len2].end(),pSet1[5][i])==true)
				ans=min(ans,len2+5);
		}
	}
	cout<<(ans==(1<<9) ? -1 : ans);
}