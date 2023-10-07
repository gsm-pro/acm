#include<iostream>
using namespace std;
#define PII pair<int,int>
int n;
PII z[101][101][2][2],a[101];
bool used[101][101][2][2];

PII calc(int l,int r,int f1,int f2)
{
	if (used[l][r][f1][f2]) return z[l][r][f1][f2];
	if (l>r) return make_pair(0,0);
	used[l][r][f1][f2]=true;
	PII w=make_pair(0,0);
	int move=(l-r+n+101)%2;
	if (move==0)
	{
		int d=(f1==0 ? a[l].first : a[l].second);
		PII p=calc(l+1,r,(f1+d)%2,f2);
		if (w.first<p.first+d || (w.first==p.first+d && w.second>p.second))
			w.first=p.first+d,w.second=p.second;
		d=(f1==0 ? a[r].first : a[r].second);
		p=calc(l,r-1,(f1+d)%2,f2);
		if (w.first<p.first+d || (w.first==p.first+d && w.second>p.second))
			w.first=p.first+d,w.second=p.second;
	}
	else
	{
		int d=(f2==0 ? a[l].first : a[l].second);
		PII p=calc(l+1,r,f1,(f2+d)%2);
		if (w.second<p.second+d || (w.second==p.second+d && w.first>p.first))
			w.first=p.first,w.second=p.second+d;
		d=(f2==0 ? a[r].first : a[r].second);
		p=calc(l,r-1,f1,(f2+d)%2);
		if (w.second<p.second+d || (w.second==p.second+d && w.first>p.first))
			w.first=p.first,w.second=p.second+d;
	}
	return z[l][r][f1][f2]=w;
}

int main()
{
	cin>>n;
	for (int i=0;i<n;i++) cin>>a[i].first>>a[i].second;
	PII q=calc(0,n-1,0,0);
	cout<<q.first<<" "<<q.second;
}