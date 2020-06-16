#include<iostream>
#include<vector>
#include<set>
#include<queue>
using namespace std;
#define forn(i,n) for (int i=0;i<int(n);i++)
typedef long long LL;
set<vector<int>> s;
queue<vector<int>> q;
vector<int> shift,revol,a;
LL n,res;
int m;
bool used[20];

int cycle(vector<int> &a)
{
	int res=0;
	memset(used,0,sizeof(used));
	forn(i,a.size())
	{
		if (used[i]) continue;
		res++;
		int v=i;
		while (!used[v])
		{
			used[v]=true;
			v=a[v];
		}
	}
	return res;
}

LL pw(LL a,int b)
{
	LL res=1;
	forn(i,b) res*=a;
	return res;
}

int main()
{
	cin>>m>>n;
	shift.resize(m);
	revol.resize(m);
	for (int i=0;i<m-1;i++) shift[i]=i+1;
	shift[m-1]=0;
	for (int i=0;i<m-1;i++) revol[i]=(m-1)-i;
	forn(i,m) a.push_back(i);
	q.push(a);
	s.insert(a);
	while (!q.empty())
	{
		vector<int> t=q.front(),tt=t;
		q.pop();
		forn(i,m) tt[i]=t[shift[i]];
		if (!s.count(tt))
		{
			s.insert(tt);
			q.push(tt);
		}
		forn(i,m) tt[i]=t[revol[i]];
		if (!s.count(tt))
		{
			s.insert(tt);
			q.push(tt);
		}
	}
	for (set<vector<int>>::iterator it=s.begin();it!=s.end();it++)
	{
		int c=cycle(*it);
		res+=pw(n,c);
	}
	cout<<res/(int)s.size();
}