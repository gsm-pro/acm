#include<iostream>
#include<string>
using namespace std;
#define INF (1<<20)
string s;
int t[260][260],a[260],v[260];

int toNum(char c)
{
	if (c>='A' && c<='Z') return c-'A'+1;
	if (c>='a' && c<='z') return c-'a'+27;
	return c-'0'+53;
}

int sum(int l,int r)
{
	return v[r]-v[l-1];
}

int calc(int l,int r)
{
	if (l>=r) return 0;
	if (l+1==r)
	{
		if (s[l]==s[r]) return 0;
		if (sum(l,r)<=62) return 1;
		return INF;
	}
	if (t[l][r]!=-1) return t[l][r];
	int w=INF;
	for (int p=l;p<=r-1;p++)
	{
		for (int q=p+1;q<=r;q++)
		{
			int len1=p-l+1,len2=r-q+1,d1=sum(l,l+len1-1),d2=sum(q,q+len2-1);
			if (len1==len2)
			{
				if (s.substr(l,len1)==s.substr(q,len2)) 
					w=min(w,calc(p+1,q-1));
			}
			if (d1==d2 && d1<=62)
				w=min(w,len1-1+len2-1+calc(p+1,q-1));
		}
	}
	if (sum(l,r)<=62) w=min(w,r-l);
	t[l][r]=w;
	return w;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	memset(t,-1,sizeof t);
	cin>>s;
	int n=(int)s.length();
	s="#"+s;
	for (int i=1;i<=n;i++) a[i]=toNum(s[i]);
	for (int i=1;i<=n;i++) v[i]=v[i-1]+a[i];
	int res=calc(1,n);
	(res==INF) ? cout<<-1 : cout<<res;
}