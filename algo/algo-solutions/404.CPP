#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
#define pb push_back
#define mp make_pair
vector<pair<pair<int,int>,int>> p;

int main()
{
	int t,m,x,cnt=0;
	cin>>t>>m;
	p.pb(mp(mp(-1,2),99999));
	p.pb(mp(mp(m+1,1),99999));
	string s;
	while (t-->0)
	{
		cin>>s;
		if (s=="alloc")
		{
			sort(p.begin(),p.end());
			bool found=false; 
			cin>>x;
			for (int i=1;i<(int)p.size();i++)
			{
				if (p[i].first.first-p[i-1].first.first-p[i-1].first.second>=x)
				{
					p.pb(mp(mp(p[i-1].first.first+p[i-1].first.second,x),++cnt));
					found=true;
					cout<<cnt<<endl;
					break;
				}
			}
			if (!found) cout<<"NULL"<<endl;
		}
		if (s=="erase")
		{
			bool found=false;
			cin>>x;
			vector<pair<pair<int,int>,int>>::iterator it,q=p.end();
			for (it=p.begin();it!=p.end();it++)
			{
				if (it->second==x)
				{
					found=true;
					q=it;
					break;
				}
			}
			if (q==p.end()) cout<<"ILLEGAL_ERASE_ARGUMENT"<<endl;
			else p.erase(q);

		}
		if (s=="defragment")
		{
			sort(p.begin(),p.end());
			for (int i=1;i<(int)p.size()-1;i++) p[i].first.first=p[i-1].first.first+p[i-1].first.second;
		}
	}
}