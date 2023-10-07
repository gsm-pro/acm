#include <vector>
using namespace std;
const int inf=99999999;

class vertex
{
public:
	int val,func;
	vertex()
	{
		val=-1;
		func=inf;
	}
};

int n;
vector<vertex> t;

void update(int v,int la,int ra,int lt,int rt,int val)
{
	if (la==lt && ra==rt)
	{
		t[v].val=val;
		t[v].func=val;
		return;
	}
	int mid=(lt+rt)/2;
	if (t[v].val!=-1)
	{ 
		t[v*2+1].val=t[v*2+2].val=t[v].val;
		t[v*2+1].func=t[v*2+2].func=t[v].val;
		t[v].val=-1;
	}  
	if (la<=mid) update(v*2+1,la,min(mid,ra),lt,mid,val);
	if (ra>mid) update(v*2+2,max(mid+1,la),ra,mid+1,rt,val);
	t[v].func=min(t[v*2+1].func,t[v*2+2].func);
}

int query(int v,int la,int ra,int lt,int rt)
{
	if ((lt<=la)&&(la<=ra)&&(ra<=rt)&&(t[v].val!=-1)) return t[v].val;
	if (la==lt && ra==rt) return t[v].func;
	int mid=(lt+rt)/2;
	int res=inf;
	if (la<=mid) res=min(res,query(v*2+1,la,min(mid,ra),lt,mid));
	if (ra>mid) res=min(res,query(v*2+2,max(mid+1,la),ra,mid+1,rt));
	return res;
}

int main()
{
	scanf("%d",&n);
	t.resize(4*n);
	for (int i=1;i<=n;i++) update(0,i,i,1,n,0);
	int m;
	scanf("%d",&m);
	for (int i=0;i<m;i++)
	{
		int l,r,x;
		scanf("%d%d%d",&l,&r,&x);
		if (l==r) continue; 
		l++;
		update(0,l,r,1,n,x);
	}
	for (int i=1;i<=n;i++) printf("%d ",query(0,i,i,1,n));
}