#include<iostream>
#define LL long long
#define SZ 200002
#define ALPH 27
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

void main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	char w[SZ/2];
	while (gets_s(w))
	{
		strupr(w);
		if (w[0]=='A')
			for (int i=2;i<(int)strlen(w);i++) add(w[i]-64);
		if (w[0]=='?')
		{
			LL p=1;
			for (int i=2;i<(int)strlen(w) && p!=-1;i++) 
				p=next[p][w[i]-64] ? next[p][w[i]-64] : -1;
			(p!=-1) ? puts("YES") : puts("NO");
		}
	}
}