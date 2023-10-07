#include<iostream>
#include<set>
using namespace std;
set<int> s;
int a,n;

int main()
{  
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	cin>>n;
	while (n-->0)
	{
		cin>>a;
		s.insert(a);
	}
	cout<<*(--s.end())<<" "<<*(--(--s.end()))<<" "<<*(--(--(--s.end())));
}