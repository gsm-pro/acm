#include<stack>
#include<iostream>
using namespace std;
stack<int> st,su;
int a[44444],lf[44444],rg[44444],n,x,ans=0;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n; 
	for (int i=1;i<=n;i++) cin>>a[i];
	st.push(0);
	for (int i=1;i<=n;i++)
	{
		x=st.top();
		while (a[x]>=a[i])
		{
			x=st.top();
			if (x>0) st.pop();else break;
		}
		lf[i]=x;
		if (x>0) st.push(x);
		st.push(i);
	}
	su.push(n+1);  
	for (int i=n;i>=1;i--)
	{
		x=su.top();
		while (a[x]>=a[i])
		{
			x=su.top();
			if (x<n+1) su.pop();else break;
		}
		rg[i]=x;
		if (x<n+1) su.push(x);
		su.push(i);
	}
	for (int i=1;i<=n;i++)
		ans=max(ans,(rg[i]-lf[i]-1)*20*a[i]);
	cout<<ans;
}