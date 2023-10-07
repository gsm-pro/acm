#include <vector>
using namespace std;
const int inf=1000000000;

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

int N;
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
	scanf("%d\n",&N);
	t.resize(4*N);
	for(int i=0;i<N;i++){
		int x;
		scanf("%d",&x);
		update(0,i+1,i+1,1,N,x);
	}
	int M;
	scanf("%d\n",&M);
	for(int i=0;i<M;i++){
		int ty,l,r,x;
		scanf("%d",&ty);
		if (ty==1){
			scanf("%d%d\n",&l,&r);
			printf("%d\n",query(0,l,r,1,N));
		}
		else {
			scanf("%d%d%d\n",&l,&r,&x);
			update(0,l,r,1,N,x);
		}
	}
}