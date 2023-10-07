#include<iostream>
#define LL long long
#define SZ 16001
#define ALPH 58
using namespace std;
LL l[SZ]={},suf[SZ]={},next[SZ][ALPH],sumlen[SZ]={},t[SZ]={};
LL la=1,n=1;
char s[SZ];

void add(int c)
{
	n++,l[n]=l[la]+1;
	LL v=la;la=n;
	while (!next[v][c] && v) next[v][c]=la,v=suf[v];
	if (!v)
	{
		suf[la]=1;
		return;
	}
	LL q=next[v][c];
	if (l[v]+1!=l[q])
	{
		n++;
		LL r=n;
		l[r]=l[v]+1,suf[la]=r,suf[r]=suf[q],suf[q]=r;
		memcpy(next[r],next[q],sizeof(next[q]));
		while (next[v][c]==q && v) next[v][c]=r,v=suf[v];
	} else suf[la]=q;
}

LL go(LL v)
{
	if (t[v]!=-1) return t[v];
	t[v]=1;
	for (int i=0;i<ALPH;i++)
		if (next[v][i]) t[v]+=go(next[v][i]);
	return t[v];
}

LL answer(LL v)
{
	if (sumlen[v]!=-1) return sumlen[v];
	sumlen[v]=0;
	for (int i=0;i<ALPH;i++)
		if (next[v][i]) sumlen[v]+=answer(next[v][i])+t[next[v][i]];
	return sumlen[v];
}

void main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	gets_s(s);
	int l=(int)strlen(s);
	for (int i=0;i<l;i++) add(s[i]-'A');
	memset(t,255,sizeof(t));
	memset(sumlen,255,sizeof(sumlen));
	go(1);
	cout<<answer(1);
}