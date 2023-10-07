#include<iostream>
#include<vector>
#include<map>
#include<set>
using namespace std;
map<int,int> pos;
vector<int> a,nums;
int n,d,p1;
set<int> ss;

template <typename typed> typed byval(typed a)
{
	return a;
}

bool check_set()
{
	for (set<int>::iterator it=ss.begin();it!=(--ss.end());it++)
		if (a[*++byval(it)]-a[*it]!=a[*(++ss.begin())]-a[*ss.begin()])
			return false;
	return true;
}

void check(int x,int y)
{
	nums.clear();
	ss.clear();
	d=a[x]-a[y];
	nums.push_back(y);
	nums.push_back(x);
	for (int i=0;i<n;i++) ss.insert(i);
	ss.erase(x);
	ss.erase(y);
	while (true)
	{
		if (ss.size()==2) break;
		if (pos.count(::a[nums.back()]+d)==0) break;
		p1=pos[::a[nums.back()]+d];
		if (p1>nums.back()) nums.push_back(p1);else break;
		ss.erase(p1);
	}
	if (!check_set())
	{
		ss.insert(nums.back());
		nums.pop_back();
	}
	if (!check_set()) return;
	for (int i=0;i<(int)nums.size();i++) 
		printf("%d ",a[nums[i]]);
	printf("\n");
	for (set<int>::iterator it=ss.begin();it!=ss.end();it++)
		printf("%d ",a[*it]);
	exit(0);
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d",&n);
	a.resize(n);
	for (int i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
		pos[a[i]]=i;
	}
	if (n<=4)
	{
		int q=n/2;
		for (int i=0;i<q;i++) printf("%d ",a[i]);
		printf("\n");		
		for (int i=q;i<n;i++) printf("%d ",a[i]);
		return 0;
	}
	check(1,0);
	check(2,0);
	check(2,1);
	printf("No solution");
}