#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	string s="",t;
	while (getline(cin,t)) s+=t;
	while (s.find("<BR>",0)!=-1) s.replace(s.find("<BR>",0),4,"\n"); 
	vector<pair<int,int>> br,z;
	stack<pair<char,int>> st;
	for (int i=0;i<(int)s.size();i++)
	{
		if (s[i]=='<')
		{
			st.push(make_pair('<',i));
		}
		if (s[i]=='>')
		{
			if (!st.empty())
			{
				if (st.top().first=='<')
				{
					br.push_back(make_pair(st.top().second,i));
					st.pop();
				}
			}
		}
	}
	br.push_back(make_pair(20000,20000));
	sort(br.begin(),br.end());
	z.push_back(br[0]);
	for(int i=1;i<(int)br.size();i++)
		if (br[i].first>z.back().second) z.push_back(br[i]);
			else z.back().second=max(z.back().second,br[i].second);
	bool no[20001]={};
	for (int i=0;i<(int)z.size();i++)
		for (int j=z[i].first;j<=z[i].second;j++) no[j]=true;
	for (int i=0;i<(int)s.length();i++)
		if (!no[i]) printf("%c",s[i]);
}