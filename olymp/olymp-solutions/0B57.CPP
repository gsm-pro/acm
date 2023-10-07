#include<cstdio>
#include<iostream>
#include<map>
#include<string>;
#include<queue>
using namespace std;

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	int n,m;
	scanf("%d%d\n",&n,&m);
	queue<int> q;
	for(int i=1;i<=n;i++) q.push(i);
	map<string,int> a;
	string s;
	for(int i=0;i<m;i++)
	{
		cin>>s;
		string tmp;
		int k=s.find('(');
		if (k>=0)
		{
			tmp=s.substr(s.find('(')+1,s.find(')')-s.find('(')-1);
			map<string,int>::iterator it=a.find(tmp);
			q.push(it->second);
			a.erase(it);
		}
		else 
		{
			tmp=s.substr(0,s.find(':'));
			a[tmp]=q.front();
			printf("%d\n",q.front());
			q.pop();            
		}
	}
}