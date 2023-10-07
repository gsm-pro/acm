#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,x[1001],b[1001],d[1001],maxlen=-1,st=-1,fin=-1,cur_d,cur_len,start;
vector<int> dd,dd1;

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) scanf("%d",&x[i]);
	for (int i=0;i<m;i++) 
	{
		scanf("%d",&d[i]);
		dd.push_back(d[i]);
	}
	for (int i=0;i<n-1;i++) b[i]=x[i+1]-x[i];
	sort(dd.begin(),dd.end());
	for (start=0;start<n-1;start++)
	{
		dd1=dd,cur_d=cur_len=0;
		while (start+cur_d<n-1)
		{
			vector<int>::iterator it=lower_bound(dd1.begin(),dd1.end(),b[start+cur_d]);
			if (it==dd1.end()) break;
			dd1.erase(it);
			cur_len+=b[start+cur_d];
			cur_d++;
		}
		if (cur_len>maxlen) maxlen=cur_len,st=start+1,fin=start+1+cur_d;
	}
	cout<<st<<" "<<fin;
}