#define _USE_MATH_DEFINES
#include<iostream>
#include<map>
#include<set>
#include<vector>
#include<algorithm>
#include<cmath>
#define C(a) (int)(a.size())
using namespace std;
vector<pair<pair<int,int>,pair<int,int>>> rib;
map<pair<int,int>,int> mm;
vector<pair<int,int>> pt(500);
set<vector<int>> facets;

class cmp
{
	int center;
public:
	cmp(int center):center(center) {}
	bool operator() (int a,int b)
	{
		double x1=pt[a].first,y1=pt[a].second,x2=pt[b].first,y2=pt[b].second;
		x1-=pt[center].first,y1-=pt[center].second,
			x2-=pt[center].first,y2-=pt[center].second;
		double ang1=atan2(y1,x1)*180/M_PI+(y1<0)*360,
			ang2=atan2(y2,x2)*180/M_PI+(y2<0)*360;
		if (ang1<ang2) return true;
		return false;
	}
};

int main()
{
	int n,m;
	vector<vector<int>> g;
	cin>>m;
	int kk=-1;
	for (int i=0;i<m;i++)
	{
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		rib.push_back(make_pair(make_pair(a,b),make_pair(c,d)));
		pair<int,int> aa=make_pair(a,b),bb=make_pair(c,d);
		if (mm.count(aa)==0) kk++,mm[aa]=kk,pt[kk]=aa;
		if (mm.count(bb)==0) kk++,mm[bb]=kk,pt[kk]=bb;
	}
	n=(int)mm.size();
	g.resize(n);
	for (int i=0;i<C(rib);i++)
	{
		pair<int,int> aa=make_pair(rib[i].first.first,rib[i].first.second),
			bb=make_pair(rib[i].second.first,rib[i].second.second);
		int a1=mm[aa],b1=mm[bb];
		g[b1].push_back(a1);
		g[a1].push_back(b1);
	}
	for (int i=0;i<n;i++)
		sort(g[i].begin(),g[i].end(),cmp(i));
	vector<vector<char>> used(n);
	for (int i=0;i<n;i++) used[i].resize(g[i].size());
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<C(g[i]);j++)
		{
			if (!used[i][j])
			{
				used[i][j]=true;
				int v=g[i][j],pv=i;
				vector<int> facet;
				for (;;)
				{
					facet.push_back(v);
					vector<int>::iterator it=find(g[v].begin(),g[v].end(),pv);
					if (++it==g[v].end()) it=g[v].begin();
					if (used[v][it-g[v].begin()]) break;
					used[v][it-g[v].begin()]=true;
					pv=v,v=*it;
				}
				sort(facet.begin(),facet.end());
				facets.insert(facet);
			}
		}
	}
	cout<<C(facets)<<endl;
	for (set<vector<int>>::iterator it=facets.begin();it!=facets.end();it++)
	{
		vector<int> p=*it;
		cout<<C(p)<<endl;
		for (int j=0;j<C(p);j++) cout<<pt[p[j]].first<<" "<<pt[p[j]].second<<endl;
		cout<<endl;
	}
}