#include<iostream>
#include<string>
#include<stack>
#include<vector>
using namespace std;

void main()
{
	vector<string> ans;
	string p;
	string s;
	getline(cin,s);
	stack<char> st;
	for(int i=0;i<(int)s.size();i++)
	{
		if (s[i]=='(')
		{
			st.push(s[i]);
		}
		else
		if (s[i]==')')
		{
			while (st.top()!='(')
			{
				p=st.top();
				ans.push_back(p);
				st.pop();
			}
			st.pop();
		}
		else
		if (s[i]=='+' || s[i]=='-')
		{
			while (!st.empty() && st.top()!='(')
			{
				p=st.top();
				ans.push_back(p);
				st.pop();
			}
			st.push(s[i]);
		}
		else
		if(s[i]=='*')
		{
			st.push(s[i]);
		}
		else
		{
			p="";
			int j=i;
			while (j<(int)s.length() && isdigit(s[j]))
			{
				p+=s[j];
				++j;
			}
			ans.push_back(p);
			i=j-1;
		}
	}
	while (!st.empty())
	{
		p=st.top();
		ans.push_back(p);
		st.pop();
	}
	for (vector<string>::iterator it=ans.begin();it!=ans.end();it++)
		cout<<*it<<" ";
}