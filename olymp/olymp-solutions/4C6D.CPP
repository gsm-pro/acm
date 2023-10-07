#include<string>
#include<iostream>
#include<vector>
using namespace std;

bool isPalin(string &w)
{
	size_t l=w.size();
	for (size_t i=0;i<l/2;i++) if (w[i]!=w[l-i-1]) return false;
	return true;
}

int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	string s,t;
	vector<int> p;
	while (cin>>s)
	{
		for (int i=(int)s.length()-1;i>=0;i--)
		{
			t=s;
			t.erase(i,1);
			if (isPalin(t))
			{
				p.push_back(i+1);
				break;
			}
		}
	}
	cout<<p.size()<<endl;
	copy(p.begin(),p.end(),ostream_iterator<int>(cout," "));
}