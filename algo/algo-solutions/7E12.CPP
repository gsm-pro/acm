#include<iostream>
#include<map>
#include<string>
using namespace std;

void main()
{
	string s,t;
	map<string,int> m;
	int k;
	cin>>k;
	while (cin>>s>>t>>k)
	{
		m[s]-=k;
		m[t]+=k;
	}
	for (map<string,int>::iterator I=m.begin();I!=m.end();I++)
		cout<<I->first<<" "<<I->second<<endl;
}