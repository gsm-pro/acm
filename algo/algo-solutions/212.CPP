#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int n;
	while (cin>>n)
	{
		vector<pair<double,double>>a(n);
		for (int i=0;i<n;++i) cin>>a[i].first>>a[i].second;
		vector<pair<double,pair<int,int>>>b;
		b.reserve(n*2);
		for (int i=0;i<n;++i)
		{
			b.push_back(make_pair(a[i].first,make_pair(i,0)));
			b.push_back(make_pair(a[i].second,make_pair(i,1)));
		}
		sort(b.begin(),b.end());
		vector<char>used(n);
		vector<int>tmp[2];
		tmp[0].reserve(n);
		tmp[1].reserve(n);
		for (int i=0;i<n*2;++i)
		{
			if (!used[b[i].second.first])
			{
				used[b[i].second.first]=true;
				tmp[b[i].second.second].push_back(b[i].second.first);
			}
		}
		vector<int>result;
		result.reserve(n);
		copy(tmp[0].begin(),tmp[0].end(),back_inserter(result));
		copy(tmp[1].rbegin(),tmp[1].rend(),back_inserter(result));
		double time1=0,time2=0;
		for (int i=0;i<n;++i)
		{
			int cur=result[i];
			time1+=a[cur].first;
			if (time2<time1) time2=time1;
			time2+=a[cur].second;
		}
		double ans=max(time1,time2);
		cout.precision(5);
		cout<<fixed<<ans<<endl;
		for (int i=0;i<n;++i) cout<<result[i]+1<<" ";
		cout<<endl;
	}
}