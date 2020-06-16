#include<cstdio>
#include<set>
using namespace std;
#define fn(e1,e2) e1+e2;
int n;
int t[400001];
int list[100001],b[100001],ex[100001],tp[100001],num[100001];

int res(int l,int r,int i=1,int tl=0,int tr=n-1)
{
	if (l==tl && r==tr) return t[i];
	int m=(tl+tr)/2;
	if (r<=m) return res(l,r,i*2,tl,m);
	if (l> m) return res(l,r,i*2+1,m+1,tr);
   	return fn(res(l,m,i*2,tl,m),res(m+1,r,i*2+1,m+1,tr));
}

void update(int pos,int newval,int i=1,int l=0,int r=n-1)
{
	if (l==r) t[i]=newval;else
	{
		int m=(l+r)/2;
		if (pos<=m) update(pos,newval,i*2,l,m);else update(pos,newval,i*2+1,m+1,r);
        	t[i]=fn(t[i*2],t[i*2+1]);
	}
}

int binsearch(int l,int r,int x)
{
	int m=(l+r)/2;
	while (l<=r && list[m]!=x)
	{
		m=(l+r)/2;
		if (x<list[m]) r=m-1;
		if (x>list[m]) l=m+1;
	}
	return m;
}

int main()
{
	int kol,ch;
	scanf_s("%d\n",&kol);
	string s;
	char buf[30];
	set<int> st;
	for (int i=1;i<=kol;i++)
	{
		gets_s(buf);
		if (buf[0]=='A') 
		{
			sscanf(buf,"ADD %d",&ch);
			tp[i]=1;
		}
		if (buf[0]=='R')
		{
			sscanf(buf,"REMOVE %d",&ch);
			tp[i]=2;
		}
		if (buf[0]=='F')
		{
			sscanf(buf,"FIND %d",&ch);
			tp[i]=3;
		}
		num[i]=ch;
		st.insert(ch);
	}
	st.insert(2000000000);
	n=-1;
	for (set<int>::iterator it=st.begin();it!=st.end();it++)
	{
		n++;
		list[n]=*it;
	}
	for (int i=1;i<=kol;i++)
	{
		int p=binsearch(0,n,num[i]);
		if (tp[i]==1) 
		{
			if (ex[p]==1) printf("NO\n");else
			{
				printf("YES\n");
				update(p,1);
				ex[p]=1;
			}
		}
		if (tp[i]==2)
		{
			if (ex[p]==0) printf("NO\n");else 
			{
				printf("YES\n");
				update(p,0);
				ex[p]=0;
			}
		}
		if (tp[i]==3)
		{
			if (ex[p]==0) printf("-1\n");else printf("%d\n",res(0,p));
		}
	}
}