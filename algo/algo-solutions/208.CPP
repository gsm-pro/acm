#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
#define LL long long

int main()
{
	string s;
	cin>>s;
	vector<LL> hs_1,hs_2;
	int n=(int)s.length();
	int i,j,ans=0;
	for (i=0;i<n;i++)
	{
		LL h1=0,h2=0;
		for (j=i;j<n;j++)
		{
			h1=h1*57+(LL)s[j];
			h2=h2*57+(LL)s[n-j-1];
			hs_1.push_back(h1);
			hs_2.push_back(h2);
		}
	}
	sort(hs_1.begin(),hs_1.end());
	sort(hs_2.begin(),hs_2.end());
	hs_1.erase(unique(hs_1.begin(),hs_1.end()),hs_1.end());
	for (i=0;i<(int)hs_2.size();i++)
	{
		bool ok=true;
		if (i>0) ok=ok && (hs_2[i]!=hs_2[i-1]); 
		if (i<(int)hs_2.size()-1) ok=ok && (hs_2[i]!=hs_2[i+1]);
		if (ok && binary_search(hs_1.begin(),hs_1.end(),hs_2[i])) ans++; 
	}
	cout<<ans;
}