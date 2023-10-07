#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
#define mp make_pair
#define pb push_back
vector<pair<int,int>> c,e;
string s;
int k=0,x=0,y=0,sq=0,nx,ny;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>s;
	c.push_back(mp(x,y));
	for (;k<(int)s.length();)
	{
		if (s[k]=='E') x++;
		if (s[k]=='W') x--;
		if (s[k]=='N')
		{
			if (s[k+1]=='W') x--;else x++;
			k++,y++;
		}
		if (s[k]=='S')
		{
			if (s[k+1]=='W') x--;else x++;
			k++,y--;
		}
		k++;
		c.push_back(mp(x,y));
	}
	for (int i=0;i<(int)c.size()-1;i++)
		sq=sq+(c[i+1].first-c[i].first)*(c[i+1].second+c[i].second);
	if (sq<0) reverse(c.begin(),c.end());
	sq=(sq>0 ? sq : -sq)/8;
	for (int i=0;i<(int)c.size()-1;i++)
	{
		int x1=c[i].first,y1=c[i].second,x2=c[i+1].first,y2=c[i+1].second;
		if (y1==y2)
		{
			if (x1<x2) nx=x1,ny=y1-2;else nx=x1-1,ny=y1;
		} else
		if (x1<x2)
		{
			if (y1<y2) nx=x1+1,ny=y1-1;else nx=x1-1,ny=y1-2;
		} else
		if (x1>x2)
		{
			if (y1<y2) nx=x1,ny=y1;else nx=x1-2,ny=y1-1;
		}
		e.pb(mp(nx,ny));
	}
	sort(e.begin(),e.end());
	e.erase(unique(e.begin(),e.end()),e.end());
	cout<<sq<<" "<<(int)e.size();
}