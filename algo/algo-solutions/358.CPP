#include<iostream>
using namespace std;
const int N=201;
int l[N],r[N],pred[N],p[N],dfs[N],bfs[N],n;

int main()
{                        
	cin>>n;
	for (int i=0;i<n;i++)
	{
		cin>>bfs[i];
		bfs[i]--;
	}
	for (int i=0;i<n;i++)
	{
		cin>>dfs[i];
		dfs[i]--;
	}
	memset(l,-1,sizeof l);
	memset(r,-1,sizeof r);
	memset(pred,0,sizeof pred);
	memset(p,-1,sizeof p);
	l[0]=0,r[0]=n;
	int ptr1=0,ptr2=1;
	for (;ptr2<n;)
	{
		int a=bfs[ptr1],lv=-1;
		for (;;)
		{
			if (ptr2==n || pred[bfs[ptr2]]!=bfs[ptr1]) break;
			if (lv!=-1 && bfs[ptr2]<lv) break;
			p[bfs[ptr2]]=a;
			if (lv!=-1)
			{
				r[lv]=l[lv];
				for (;dfs[r[lv]]!=bfs[ptr2];++r[lv]) pred[dfs[r[lv]]]=lv;
				l[bfs[ptr2]]=r[lv];
			}
			else l[bfs[ptr2]]=l[a]+1;
			lv=bfs[ptr2];
			ptr2++;
		}    
		if (lv!=-1)
		{
			r[lv]=l[lv];
			for (;r[lv]<r[a];++r[lv]) pred[dfs[r[lv]]]=lv;
		}
		ptr1++;
	}
	for (int i=1;i<n;i++) cout<<p[i]+1<<" "<<i+1<<"\n";
}