#include<string>
#include<iostream>
#include<vector>
using namespace std;
#define SIZE 200001
#define ALPH 26

struct state 
{
	int lnk,len;
	int next[ALPH];
	bool term;
};

state st[2*SIZE];
int sz,la;

void initialize() 
{
	sz=la=0;
	for (int i=0;i<2*SIZE;++i) st[i].term=false;
	st[0].len=0,st[0].lnk=-1;
	memset(st[0].next,-1,sizeof st[0].next);
	++sz;
}

void add(char c)
{
	int nlast=sz++;
	st[nlast].len=st[la].len+1;
	memset(st[nlast].next,-1,sizeof st[nlast].next);
	int p;
	for (p=la;p!=-1 && st[p].next[c]==-1;p=st[p].lnk) st[p].next[c]=nlast;
	if (p==-1) st[nlast].lnk=0;else 
	{
		int q=st[p].next[c];
		if (st[p].len+1==st[q].len) st[nlast].lnk=q;else 
		{
			int nov=sz++;
			st[nov].len=st[p].len+1;
			memcpy(st[nov].next,st[q].next,sizeof st[nov].next);
			st[nov].lnk=st[q].lnk;
			for (;p!=-1 && st[p].next[c]==q;p=st[p].lnk) st[p].next[c]=nov;
			st[q].lnk=st[nlast].lnk=nov;
		}
	}
	la=nlast;
}

string lcs(string &a,string &b)
{
	initialize();
	for (int i=0;i<(int)a.length();++i) add(a[i]-'a');
	int p=0,l=0,best_l=0,best_p=0;
	for (int i=0;i<(int)b.length();++i)
	{
		if (st[p].next[b[i]-'a']==-1)
		{
			for (;p!=-1 && st[p].next[b[i]-'a']==-1;p=st[p].lnk);
			if (p==-1)
			{
				p=l=0;
				continue;
			}
			l=st[p].len;
		}
		p=st[p].next[b[i]-'a'];
		++l;
		if (l>best_l) best_l=l,best_p=i;
	}
	return b.substr(best_p-best_l+1,best_l);
}

int main()
{
	int n;
	cin>>n;
	vector<string> inp(n),st; 
	for (int i=0;i<n;i++) cin>>inp[i];
	if (n==1)
	{
		cout<<inp[0];
		return 0;
	}
	for (int i=0;i<n;i++)
		for (int j=i+1;j<n;j++)
			st.push_back(lcs(inp[i],inp[j]));
	for (int i=0;i<(int)st.size();i++)
		for (int j=0;j<(int)st.size()-1;j++)
			if (st[j].size()<st[j+1].size()) swap(st[j],st[j+1]);
	for (int i=0;i<(int)st.size();i++)
	{
		bool ok=true;
		for (int j=0;j<(int)inp.size();j++)
			if (inp[j].find(st[i])==-1) ok=false;
		if (ok)
		{
			cout<<st[i];
			return 0;
		}
	}
}