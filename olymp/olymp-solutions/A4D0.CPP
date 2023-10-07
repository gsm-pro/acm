#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> ans,b,tmp;
int k,n=99;
vector<vector<int>> all;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>k;
	for (int i=0;i<k;i++) 
	{
		int w;
		cin>>w;
		b.push_back(w);
	}
	while (n>=0)
		if (n*(n-1)==2*k) break;else --n;
	if (n==0)
	{
		cout<<-1;
		return 0;
	}
	sort(b.begin(),b.end());
	for (int q=b[k-1];q>=0;q--)
	{
		ans.clear();
		tmp=b;
		ans.push_back(q);
		int z=b[k-1]-q;
		if (q>=z)
		{
			RET:;
			ans.push_back(z);
			for (int i=0;i<(int)ans.size()-1;i++)
			{
				vector<int>::iterator it=find(tmp.begin(),tmp.end(),ans[i]+ans.back());
				if (it==tmp.end()) goto NOWAY;
				tmp.erase(it);
			}
			if (!tmp.empty())
			{
				z=tmp.back()-ans[0];
				goto RET;
			}
		}
		sort(ans.begin(),ans.end());
		if ((int)ans.size()==n) all.push_back(ans);
		NOWAY:;
	}
	if ((int)all.size()==1)
	{
		cout<<n<<endl;
		for (int i=0;i<n;i++) cout<<all[0][i]<<" ";
	} else cout<<"NO SOLUTION";
}