#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define MAX 1<<25
vector<int> f;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,m,a;
	cin>>n>>m;
	f.push_back(-MAX);
	f.push_back(MAX);
	for (int i=0;i<n;i++)
	{
		cin>>a;
		f.push_back(a);
	}
	sort(f.begin(),f.end());
	for (int i=0;i<m;i++)
	{
		cin>>a;
		if (binary_search(f.begin(),f.end(),a)!=NULL) cout<<"0";else
		{
			int l=*(--upper_bound(f.begin(),f.end(),a));
			int r=*(lower_bound(f.begin(),f.end(),a));
			if (l==-MAX) cout<<r-a;else
				if (r==MAX) cout<<a-l;else
					cout<<min(r-a,a-l);
		}
		cout<<" ";
	}
}