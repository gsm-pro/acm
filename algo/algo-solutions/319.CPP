#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

int main()
{
	vector<int> days;
	vector<pair<int,int>> work;
	int n;
	cin>>n;
	n++;
	string s;
	while (n-->0)
	{
		getline(cin,s);
		int p=(int)s.find(" ");
		if (p<0)
		{
			int q=atoi(s.c_str());
			days.push_back(q);
		} 
		else 
		{
			int q=atoi(s.substr(0,p).c_str());
			int r=atoi(s.substr(p+1,s.length()).c_str());
			work.push_back(make_pair(q,r));
		}
	}
	sort(work.begin(),work.end());
	reverse(work.begin(),work.end());
	sort(days.begin(),days.end());
	reverse(days.begin(),days.end());
	int ans=0;
	for (size_t i=0;i<work.size();i++)
	{
		int bestday=0;
		for (size_t j=0;j<days.size();j++)
			if (work[i].second<=days[j]) bestday=(int)j;
		if (work[i].second<=days[bestday])
		{
			ans+=work[i].first;
			days[bestday]=-1;
		}
	}
	cout<<ans;
}