#include<iostream>
#include<set>
using namespace std;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	set<int> a,b,c;
	set<int>::iterator it;
	int x,n;
	cin>>n;
	while (n-->0)
	{
		cin>>x;
		a.insert(x);
	}
	cin>>n;
	while (n-->0)
	{
		cin>>x;
		b.insert(x);
	}
	for (it=a.begin();it!=a.end();it++)
		if (b.count(*it)==0) c.insert(*it);
	for (it=b.begin();it!=b.end();it++)
		if (a.count(*it)==0) c.insert(*it);
	cout<<(int)c.size();
	for (it=c.begin();it!=c.end();it++) cout<<" "<<*it;
}