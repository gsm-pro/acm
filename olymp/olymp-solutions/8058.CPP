#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
int n,kt=0,kk=0;

vector<pair<int,int>> calc(string w,string x)
{
	vector<pair<int,int>> res;
	for (int i=0;i<n;i++)
		if (w[i]!=x[i])
			for (int j=n-1;j>=i+1;j--)
				if (w[j]!=x[j])
				{
					swap(x[i],x[j]);
					res.push_back(make_pair(i+1,j+1));
					break;
				}
				return res;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	string s;
	cin>>n>>s;
	for (int i=0;i<n;i++)
		kt+=(s[i]=='T'),kk+=(s[i]=='K');
	string w1="",w2;
	for (int i=0;i<kk;i++) w1+="K";
	for (int i=0;i<kt;i++) w1+="T";
	w2=w1;
	reverse(w2.begin(),w2.end());
	vector<pair<int,int>> z1=calc(s,w1),z2=calc(s,w2),ans;
	ans=(z1.size()<z2.size() ? z1 : z2);
	cout<<ans.size()<<endl;
	for (size_t i=0;i<ans.size();i++) cout<<ans[i].first<<" "<<ans[i].second<<endl;
}