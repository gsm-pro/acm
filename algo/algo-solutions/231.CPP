#include<cstdio>
#include<vector>
using namespace std;

struct Node
{
	bool flag;
	int w,s;
};

Node md[600001];
int n,k;

void relax(int idx,int l,int r)
{
	if (!md[idx].flag) return;
	md[idx].s+=md[idx].w*(r-l);
	md[idx].flag=false;
	if (r-l>1)
	{
		md[(idx<<1)+1].flag=md[(idx+1)<<1].flag=true;
		md[(idx<<1)+1].w+=md[idx].w;
		md[(idx+1)<<1].w+=md[idx].w;		
	}
	md[idx].w=0;
}

void updateOne(Node &a,Node &b,Node &c)
{
	a.s=c.s+b.s;
}

void updateSegm(int idx,int l,int r,int x,int y,int w)
{
	relax(idx,l,r);
	if (x==l && y==r) 
	{
		md[idx].flag=true;
		md[idx].w=w;
		relax(idx,l,r);
		return;
	}
	int mid=(l+r)>>1;
	if (x<mid)
		updateSegm((idx<<1)+1,l,mid,x,min(y,mid),w);
	if (y>mid)
		updateSegm((idx+1)<<1,mid,r,max(x,mid),y,w);
	updateOne(md[idx],md[(idx<<1)+1],md[(idx+1)<<1]);
}

int mdSearch(int idx,int l,int r,int p)
{
	relax(idx,l,r);
	if (r-l==1) return md[idx].s;
	int mid=(l+r)>>1;
	if (p<mid)
		return mdSearch((idx<<1)+1,l,mid,p);
	else
		return mdSearch((idx+1)<<1,mid,r,p);
}

void main()
{
	scanf_s("%d %d",&n,&k);
	for(int i=0;i<k;i++)
	{
		int op; 
		scanf_s("%d",&op);
		if (op==1)
		{
			int l,r,c;
			scanf_s("%d %d %d",&l,&r,&c);
			updateSegm(0,0,n,l-1,r,c);
		}
		else
		{
			int num; 
			scanf_s("%d",&num);
			printf("%d ",mdSearch(0,0,n,num-1));
		}
	}
}