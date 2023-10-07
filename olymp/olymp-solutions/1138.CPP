#include<iostream>
#include<set>
#include<vector> 
#include<algorithm>
using namespace std;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int x1,y1,x2,y2,dx,dy;
	cin>>x1>>y1>>x2>>y2>>dx>>dy;
	vector<int> x,y;
	for (int i=0;i<500;i++)
	{
		x.push_back(x1*i);
		y.push_back(y1*i);
		x.push_back(dx+x2*i);
		y.push_back(dy+y2*i);
	}
	sort(x.begin(),x.end());
	sort(y.begin(),y.end());
	x.erase(unique(x.begin(),x.end()),x.end());
	y.erase(unique(y.begin(),y.end()),y.end());
	set<int> s;
	for (int i=0;i<150;i++)
		for (int j=0;j<150;j++)
			s.insert((x[i+1]-x[i])*(y[j+1]-y[j]));
	cout<<(int)s.size()<<endl;
	for (set<int>::iterator it=s.begin();it!=s.end();it++) cout<<*it<<endl;
}