#include<iostream>
#include<cmath>
#include<set>
using namespace std;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	set<double> r;
	double a,b,c,d;
	cin>>a>>b>>c;
	if (a*a+b*b+c*c==0) cout<<"INFINITE";else
	{
		if (a==0 && b!=0) (c!=0) ? r.insert(-c/b) : r.insert(0);
		if (a!=0)
		{
			d=b*b-4*a*c;
			if (d>=0) r.insert((-b-sqrt(d))/2/a),r.insert((-b+sqrt(d))/2/a);
		}
		cout<<(int)r.size();
		cout.precision(6);
		for (set<double>::iterator it=r.begin();it!=r.end();it++) cout<<endl<<*it;
	}
}