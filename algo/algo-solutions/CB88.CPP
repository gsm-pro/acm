#include<iostream>
using namespace std;
char s[128001],t[128001];
int p[128000];

int main()
{
	gets_s(s),gets_s(t);
	int m=(int)strlen(s),n=(int)strlen(t),k=0,q=0;
	p[0]=0;
	for (int i=1;i<=m-1;i++)
	{
		while (k && s[k]!=s[i]) k=p[k-1];
		if (s[k]==s[i]) k++;
		p[i]=k;
	}
	for (int i=0;i<n;i++)
	{
		while (q && s[q]!=t[i]) q=p[q-1];
		if (s[q]==t[i]) q++;
		if (q==m) printf("%d ",i-m+2),q=p[q-1];
	}
}