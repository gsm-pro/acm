#include<iostream>
#include<vector>
#include<set>
#include<string>
using namespace std;
vector<int> a(1001),r(1001);
int n;
set<string> ans;
string q;

void rec(int x)
{
	if (n==1 && x==1 && a[0]!=r[0]) return;
	if (n==2 && x==2 && (a[1]!=r[1]+r[0] || a[0]!=r[1]+r[0])) return;
	if (x>2 && a[x-2]!=r[x-3]+r[x-2]+r[x-1]) return;  
	if (x==n)
	{
		if (a[0]!=r[0]+r[1]) return;
		if (n>1 && a[n-1]!=r[n-1]+r[n-2]) return;
		for (int i=1;i<=n-2;i++)
			if (r[i]+r[i-1]+r[i+1]!=a[i]) return;
		q="";
		for (int i=0;i<n;i++) q+=(r[i]+48);
		ans.insert(q);
		return;
	}
	r[x]=0;
	rec(x+1);
	r[x]=1;
	rec(x+1);
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	string s;
	cin>>s;
	n=(int)s.length();
	for (int i=0;i<n;i++) a[i]=s[i]-'0';
	rec(0);
	cout<<(int)ans.size()<<endl;
	for (set<string>::iterator it=ans.begin();it!=ans.end();it++) cout<<*it<<endl;
}