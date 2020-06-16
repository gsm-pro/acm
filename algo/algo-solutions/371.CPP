#include<iostream>
#include<map>
#define LL long long
#define SIZE 200001
using namespace std;

struct EL 
{
	int len,lnk;
	map<char,int> next;
	LL d;
} state[SIZE*2];
int sz,l;
char c;

void add(char c) 
{
	int nl=sz++;
	state[nl].len=state[l].len+1;
	int p;
	for (p=l;p!=-1 && !state[p].next.count(c);p=state[p].lnk) state[p].next[c]=nl;
	if (p==-1) state[nl].lnk=0;else
	{
		int q=state[p].next[c];
		if (state[p].len+1==state[q].len) state[nl].lnk=q;else 
		{
			int nov=sz++;
			state[nov].len=state[p].len+1;
			state[nov].next=state[q].next;
			state[nov].lnk=state[q].lnk;
			state[q].lnk=nov;
			state[nl].lnk=nov;
			for (;p!=-1 && state[p].next.count(c) && state[p].next[c]==q;p=state[p].lnk) 
				state[p].next[c]=nov;
		}
	}
	l=nl;
}

LL go(int p)
{
	if (state[p].d==-1) 
	{
		state[p].d=0;
		for (map<char,int>::iterator i=state[p].next.begin();i!=state[p].next.end();++i) 
			state[p].d+=go(i->second)+1UL;
	}
	return state[p].d;
}

int main() 
{
	for (int i=0;i<SIZE*2;++i) state[i].d=-1;
	state[sz++].lnk=-1;
	for (;(c=fgetc(stdin))!=EOF && c!='\n' && c!='\r';) add(c);
	cout<<go(0);
}