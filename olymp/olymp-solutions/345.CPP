#include<iostream>
using namespace std;
bool ex[52000]={};
short z1[52000],z2[52000];
int n,k=0,p,q;

void rec(int i)
{
	if (i>n)
	{
		printf("%d\n",k);
		for (int i=1;i<=k;i++) printf("%d %d %d\n",z1[i],z2[i],z1[i]+p+q);
		exit(0);
	}
	int y=i,b=i+p,c=i+p+q;
	if (ex[i] && ex[b] && ex[c])
	{
		ex[y]=ex[b]=ex[c]=false,k++,z1[k]=i,z2[k]=b;
		while (!ex[y]) y++;
		rec(y);
		ex[i]=ex[b]=ex[c]=true;
		k--;
	} 
	b=i+q,y=i;
	if (ex[i] && ex[b] && ex[c])
	{
		ex[y]=ex[b]=ex[c]=false,k++,z1[k]=i,z2[k]=b;
		while (!ex[y]) y++;
		rec(y);
		ex[i]=ex[b]=ex[c]=true;
		k--;
	} 
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int b,c;
	scanf_s("%d%d%d",&q,&p,&n);
	memset(ex,true,sizeof(ex));
	bool ok=true;
	for (int i=1;i<=n;i++)
	{
		b=i+q,c=i+p+q;
		if (ex[i] && ex[b] && ex[c]) ex[i]=ex[b]=ex[c]=false,k++,z1[k]=i,z2[k]=b;else 
		{
			b=i+p;
			if (ex[i] && ex[b] && ex[c]) ex[i]=ex[b]=ex[c]=false,k++,z1[k]=i,z2[k]=b;
		}
	}
	for (int i=1;i<=n;i++) if (ex[i]) ok=false;
	if (ok)
	{
		printf("%d\n",k);
		for (int i=1;i<=k;i++) printf("%d %d %d\n",z1[i],z2[i],z1[i]+p+q);
	} 
	else  
	{
		memset(ex,true,sizeof(ex));
		k=0;
		rec(1);
	}
}