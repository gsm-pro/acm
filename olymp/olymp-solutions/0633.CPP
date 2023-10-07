#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

void main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	set<int> r;
	set<long long> razl;
	int kol;
	cin>>kol;
	for (int q=1;q<=kol;q++)
	{
		r.clear();
		string s;
		cin>>s;
		int x1=0,y1=0,x2=0,y2=0,h;
		long long hash=0;
		for (int i=0;i<(int)s.length();i++)
		{
			if (s[i]=='U')
			{
				y2=y1+1;
				h=min(x1,x2)*17+min(y1,y2)*211+max(x1,x2)*1001+max(y1,y2)*60001;
				r.insert(h);
			}
			if (s[i]=='D')
			{
				y2=y1-1;
				h=min(x1,x2)*17+min(y1,y2)*211+max(x1,x2)*1001+max(y1,y2)*60001;
				r.insert(h);
			}
			if (s[i]=='R')
			{
				x2=x1+1;
				h=min(x1,x2)*17+min(y1,y2)*211+max(x1,x2)*1001+max(y1,y2)*60001;
				r.insert(h);
			}
			if (s[i]=='L')
			{
				x2=x1-1;
				h=min(x1,x2)*17+min(y1,y2)*211+max(x1,x2)*1001+max(y1,y2)*60001;	
				r.insert(h);
			}
			x1=x2;
			y1=y2;
		}
		for (set<int>::iterator it=r.begin();it!=r.end();it++)
		{
			hash=(hash+(*it)*(*it)+1000000001)%1000000001; 
		}
		razl.insert(hash);
	}
	cout<<razl.size();
}