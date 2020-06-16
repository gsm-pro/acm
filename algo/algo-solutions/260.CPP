#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<strstream>
#define forn(i,n) for(int (i)=0;i<(n);i++)
using namespace std;
vector<string>title,crits;
vector<bool>order;
vector<vector<string>>data;

bool cmp(vector<string>&a,vector<string>&b)
{
	forn(crit,(int)crits.size()) 
	{
		int column=find(title.begin(),title.end(),crits[crit])-title.begin();
		if (a[column]!=b[column]) return (a[column]<b[column])==order[crit];
	}
	return false;
}

int main()
{
	string buf,s;
	getline(cin,buf);
	istrstream stream(buf.c_str());
	while (!getline(stream,s,' ').fail()) title.push_back(s);
	getline(cin,buf);
	istrstream stream2(buf.c_str());
	while (!getline(stream2,s,',').fail()) 
	{
		if (s[0]==' ') s.erase(0,1);
		int space=(int)s.find(' ');
		crits.push_back(s.substr(0, space));
		order.push_back(s[space + 1]=='A');
	}
	while (!getline(cin,buf).fail()) 
	{
		istrstream stream3(buf.c_str());
		data.resize(data.size()+1);
		while(!getline(stream3,s,' ').fail()) data.back().push_back(s);
	}
	sort(data.begin(),data.end(),cmp);
	forn(i,(int)data.size()) 
	{
		copy(data[i].begin(),data[i].end(),ostream_iterator<string>(cout," "));
		cout<<endl;
	}
}