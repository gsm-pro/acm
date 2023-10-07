#include<set>
#include<iostream>
#include<string>
using namespace std;

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	string s,t;
	char k;
	cin>>k>>s;
	int n=(int)s.length();
	if (s.find(k)==-1)
	{
		cout<<0;
		return 0;
	}
	char min_char='A';
	int kol_min_char=0;
	for (int i=0;i<n;i++)
	{
		if (s[i]==min_char) kol_min_char++;
		if (s[i]< min_char) min_char=s[i],kol_min_char=1;
	}
	char second_min;
	if (k==min_char && kol_min_char==1)
	{
		second_min='A';
		for (int i=0;i<n;i++)
			if (s[i]<second_min && s[i]!=min_char) second_min=s[i];
		if (second_min=='A') second_min=min_char;
	} else second_min=min_char;
	set<string> st;
	for (int i=0;i<n;i++)
	{
		if (s[i]==k)
		{
			for (char j='0';j<=second_min;j++)
			{
				t=s;
				t[i]=j;
				st.insert(t);
			}
		}
	}
	int ans=(int)st.size();
	if (n==1) ans=10;
	cout<<ans;
}