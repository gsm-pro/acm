#include<string>
#include<map>
#include<iostream>
using namespace std;
map<int,int> m;

void fact(int n,int sgn) 
{
	int i=2;
	while (i*i<=n)
	{
		int p=0;
		while (!(n%i)) n/=i,++p;
		m[i]+=(sgn*p);
		i++;
	}
	m[n]+=(sgn*(n>1));
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int x;
	cin>>x;
	fact(x,1);
	string sg;
	while (cin>>sg>>x) fact(x,(sg=="*") ? 1 : -1);
	__int64 ans=1;
	for (map<int,int>::iterator it=m.begin();it!=m.end();it++) ans=(ans*(it->second+1))%100000;
	cout<<ans;
}