#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
#define LL long long 
typedef pair<LL,LL> pd;
LL n;
vector<pd> ans;

bool less(pd &a,pd &b) 
{
	return (a.first>b.first || (a.first==b.first && a.second<b.second));
}

void fact() 
{
	LL i=2;
	while (i*i<=n) 
	{
		LL p=0;
		while (n%i==0) n/=i,++p;
		if (p>0) ans.push_back(make_pair(p,i));
		++i;
	}
	if (n>1) ans.push_back(make_pair(1,n));
}

int main()
{
	cin>>n;
	fact();
	sort(ans.begin(),ans.end(),less);	
	cout<<(int)ans.size()<<endl;
	for (int i=0;i<(int)ans.size();i++) cout<<ans[i].second<<" "<<ans[i].first<<endl;
}