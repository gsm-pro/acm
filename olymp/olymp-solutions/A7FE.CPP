#include<fstream>
#include<string>
#include<map>
using namespace std;

int main()
{
	ifstream I("input.txt");
	ofstream O("output.txt");
	string a,b;
	int n,x;
	map<string,int> m;
	I>>n;
	while (n-->0) I>>a,m[a]=0;
	I>>n;
	while (n-->0) I>>a>>b>>x,m[a]+=x,m[b]-=x;
	for (map<string,int>::iterator it=m.begin();it!=m.end();it++)
		O<<it->first<<" "<<it->second<<endl;
}