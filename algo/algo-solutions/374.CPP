#include<cstdio>
#include<stack>
using namespace std;

int main()
{
	stack<int> s;
	int v[100000],n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d",&v[i]);
	for (int i=n-1;i>=0;i--)
	{
		while (!s.empty() && v[i]>=s.top()) s.pop();
		if (s.empty())
		{
			s.push(v[i]);
			v[i]=0;
		} 
		else
		{
			int t=s.top();
			s.push(v[i]);
			v[i]=t;
		}
	}
	for (int i=0;i<n;i++) printf("%d ",v[i]);
}