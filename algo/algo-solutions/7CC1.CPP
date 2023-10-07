#include<iostream>
#include<string>
#include<queue>
#include<map>
using namespace std;
string s,t;
int l;
map<string,string> pr;
queue<string> q;

bool palin(string &w)
{
	for (char i=0;i<l/2;i++) if (w[i]!=w[l-i-1]) return false;
	return true;
}

int print_ans(string &q)
{
	int res=-1;
	while (q!="#") q=pr.find(q)->second,++res;
	return res;
}

int main()
{
	cin>>s;
	l=(int)s.length();
	int z[255]={},kol_odd=0;
	for (int i=0;i<l;i++) z[s[i]-' ']++;
	for (int i=0;i<255;i++) kol_odd+=(z[i]&1);
	if (kol_odd>1)
	{
		cout<<-1;
		return 0;
	}
	q.push(s);
	pr[s]="#";
	while (!q.empty())
	{
		s=q.front(),q.pop();
		if (palin(s))
		{
			cout<<print_ans(s);
			break;
		}
		for (int i=0;i<=l-2;i++)
		{
			t=s;
			swap(t[i],t[i+1]);
			if (pr.count(t)==0)
			{
				pr[t]=s;
				q.push(t);
			}
			if (i==l-2) break;
			t=s;
			swap(t[i],t[i+2]);
			if (pr.count(t)==0)
			{
				pr[t]=s;
				q.push(t);
			}
		}
	}
}