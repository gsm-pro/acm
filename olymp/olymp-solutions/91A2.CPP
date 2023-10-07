#include<iostream>
#include<string>
#include<set>
using namespace std;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	set<pair<int,int>> st;
	st.insert(make_pair(0,0));
	string s;
	cin>>s;
	int x=0,y=0,h=0;
	while (cin>>s)
	{
		h++;
		if (s=="L") x--;
		if (s=="R") x++;
		if (s=="U") y++;
		if (s=="D") y--;
		if (s=="LU") x--,y++;
		if (s=="LD") x--,y--;
		if (s=="RU") x++,y++;
		if (s=="RD") x++,y--;
		pair<int,int> r=make_pair(x,y);
		if (st.count(r))
		{
			cout<<"YES"<<endl<<h;
			return 0;
		}
		st.insert(r);
	}
	cout<<"NO";
}