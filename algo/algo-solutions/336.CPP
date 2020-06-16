#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
#define forn(i,n) for(int i=0;i<n;i++)
#define LD long double
#define pt pair<LD,LD>
#define pb push_back
#define mp make_pair
#define X first
#define Y second
#define segm pair<pt,pt>
const LD eps=1e-9;
int n,m;
vector<pair<segm,int>> pl;
pt p1[55],p2[55],c(0,0);

struct line
{
	LD a,b,c;
	line(){};
	line(pt p1,pt p2)
	{
		a=p2.Y-p1.Y,b=p1.X-p2.X,c=-a*p1.X-b*p1.Y;
	}    
};

struct item
{
	LD y1,y2;
	int id;
	item(){};
	item(LD y1,LD y2,int id)
	{
		this->y1=y1,this->y2=y2,this->id=id;
	};
};

bool cmp(const pt& p1,const pt& p2)
{
	return atan2(p1.Y-c.Y,p1.X-c.X)+eps<atan2(p2.Y-c.Y,p2.X-c.X);
}

bool operator < (const item& i1,const item& i2)
{
	return i1.y1+eps<i2.y1 || (fabs(i1.y1-i2.y1)<eps && i1.y2+eps<i2.y2);
}

LD det(LD a11,LD a12,LD a21,LD a22)
{
	return a11*a22-a12*a21;
}

bool in(segm& s,pt& p)
{
	return min(s.first.X,s.second.X)<p.X+eps && p.X-eps<max(s.first.X,s.second.X) && 
		min(s.first.Y,s.second.Y)<p.Y+eps && p.Y-eps<max(s.first.Y,s.second.Y); 
}

void inters(segm& s1,segm& s2,vector<LD>& p)
{
	line l1(s1.first,s1.second),l2(s2.first,s2.second);
	LD d=det(l1.a,l1.b,l2.a,l2.b);
	if (fabs(d)<eps) return;
	LD d1=det(-l1.c,l1.b,-l2.c,l2.b); 
	LD d2=det(l1.a,-l1.c,l2.a,-l2.c);
	pt tmp(d1/d,d2/d);
	if (in(s1,tmp) && in(s2,tmp)) p.pb(tmp.X);
}

LD y_inters(segm& s,LD x)
{
	return s.first.Y+(s.second.Y-s.first.Y)*(x-s.first.X)/(s.second.X-s.first.X);
}

LD decomp(vector<pair<segm,int>> pl)
{
	int n=(int)pl.size();
	vector<LD> xs(2*n);
	forn(i,n)
		if (pl[i].first.first>pl[i].first.second) 
			swap(pl[i].first.first,pl[i].first.second);
	forn(i,n)
	{
		xs[2*i]=pl[i].first.first.X;
		xs[2*i+1]=pl[i].first.second.X; 
	}
	forn(i,n)
		forn(j,i)
		inters(pl[i].first,pl[j].first,xs);
	sort(xs.begin(),xs.end());
	xs.erase(unique(xs.begin(),xs.end()),xs.end());
	LD ans=0;
	forn(i,int(xs.size())-1)
	{
		LD x1=xs[i],x2=xs[i+1];
		vector<item> cur;
		forn(i,n)
		{
			segm s=pl[i].first;
			int id=pl[i].second;
			if (fabs(s.first.X-s.second.X)<eps) continue;
			if (s.first.X<=x1+eps && x2-eps<=s.second.X)
				cur.pb(item(y_inters(s,x1),y_inters(s,x2),id));
		}
		vector<bool> us(n,false);
		sort(cur.begin(),cur.end());
		int cnt=0;
		item lower,upper;
		forn(i,(int)cur.size())
		{
			if (cnt==0) lower=cur[i];
			if (!us[cur[i].id])
			{
				cnt++;
				us[cur[i].id]=true;
			}
			else 
			{
				cnt--;
				us[cur[i].id]=false;
			}
			if (cnt==0)
			{
				upper=cur[i];
				ans+=(x2-x1)*(upper.y1-lower.y1+upper.y2-lower.y2)/2;
			}
		}
	}
	return ans;
}

int main()
{
	cin>>n;
	forn(i,n)
	{
		cin>>p1[i].X>>p1[i].Y;
		c.X+=p1[i].X,c.Y+=p1[i].Y;
	}
	c.X/=n,c.Y/=n;
	sort(p1,p1+n,cmp);
	cin>>m;
	forn(i,m) cin>>p2[i].X>>p2[i].Y;
	forn(i,n) pl.pb(mp(segm(p1[i],p1[(i+1)%n]),0));
	forn(i,m) pl.pb(mp(segm(p2[i],p2[(i+1)%m]),1));
	LD sq1=0,sq2=0;
	forn(i,n) 
		sq1+=(p1[(i+1)%n].Y+p1[i].Y)*(p1[(i+1)%n].X-p1[i].X)/2;
	sq1=fabs(sq1);
	forn(i,m) 
		sq2+=(p2[(i+1)%m].Y+p2[i].Y)*(p2[(i+1)%m].X-p2[i].X)/2; 
	sq2=fabs(sq2);
	LD sqob=decomp(pl);
	cout.precision(9);
	cout<<fixed<<sq1+sq2-sqob; 
}