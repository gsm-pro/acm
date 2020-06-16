#include<map>
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
#define mp make_pair
#define PP pair<pair<int,int>,pair<int,string>>
#define fs first
#define sd second

bool cmp(PP a,PP b)
{
	if ((a.fs.fs<b.fs.fs) || 
	    (a.fs.fs==b.fs.fs && a.fs.sd<b.fs.sd) ||
	    (a.fs.fs==b.fs.fs && a.fs.sd==b.fs.sd && a.sd.fs<b.sd.fs) ||
	    (a.fs.fs==b.fs.fs && a.fs.sd==b.fs.sd && a.sd.fs==b.sd.fs && a.sd.sd>b.sd.sd)) return 0;
	return 1;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	map<string,int> m;
	string g,s,b;
	cin>>g;
	while (cin>>g>>s>>b) m[g]+=1000000,m[s]+=1000,m[b]+=1;
	vector<PP> z;
	for (map<string,int>::iterator I=m.begin();I!=m.end();I++)
	{
		int sc=I->sd;
		z.push_back(mp(mp(sc/1000000,(sc%1000000)/1000),mp(sc%1000,I->fs)));
	}
	sort(z.begin(),z.end(),cmp);
	int n=(int)z.size(),pn=1,fn=1;
	for (int i=0;i<n;i++)
	{
		if (i>0 && z[i-1].fs.fs==z[i].fs.fs && z[i-1].fs.sd==z[i].fs.sd && z[i-1].sd.fs==z[i].sd.fs);else pn=fn;
		cout<<pn<<". "<<z[i].sd.sd<<" "<<z[i].fs.fs<<" "<<z[i].fs.sd<<" "<<z[i].sd.fs<<endl;
		fn++;
	}
}