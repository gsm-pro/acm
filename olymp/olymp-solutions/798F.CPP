#include<string>
#include<iostream>
#include<vector>
using namespace std;

bool isLetter(char c)
{
	return ('a'<=c && c<='z') || ('A'<=c && c<='Z') || ('0'<=c && c<='9') || (c=='_');
}

bool isInteger(string r,int lo,int hi)
{
	if (r.length()<1 || r.length()>5) return false;
	int res=0;
	for (int i=0;i<(int)r.length();i++)
	{
		if (r[i]<'0' || r[i]>'9') return false;
		res=res*10+r[i]-'0';
	}
	if (res<lo || res>hi) return false;
	return (r=="0" || r[0]!='0');
}

vector<string> split(string d,char c)
{
	vector<string> res;
	string part;
	d+=c;                                        
	for (int i=0;i<(int)d.length();i++)
	{
		if (d[i]==c)
		{
			res.push_back(part);
			part="";
		} else part+=d[i];
	}
	return res;
}

bool isIp(string ip)
{
	vector<string> sep=split(ip,'.');
	if (sep.size()!=4) return false;
	for (int i=0;i<4;i++)
		if (!isInteger(sep[i],0,255)) return false;
	return true;
}

bool isWord(string w)
{
	for (int i=0;i<(int)w.length();i++)
		if (!('a'<=w[i] && w[i]<='z') && !('A'<=w[i] && w[i]<='Z')) return false;
	return true;
}

bool isAddress(string name)
{
	vector<string> sep=split(name,'.');
	if (sep.size()>1 && (sep[sep.size()-1].length()==2 || sep[sep.size()-1].length()==3))
		return isWord(sep[sep.size() - 1]);else return false;
}

bool isName(string name)
{
	vector<string> sep=split(name,'.');
	return sep.size()==1;
}

bool isHost(string host)
{
	if (host.length()<1) return false;
	if (host.find("..")!=string::npos) return false;
	if (host[0] == '.' || host[host.length()-1]=='.') return false;
	for (int i=0;i<(int)host.length();i++)
		if (host[i]!='.' && !isLetter(host[i])) return false;
	return isIp(host) || isName(host) || isAddress(host);
}

bool isHostWithPort(string host)
{
	int nD=0;
	for (int i=0;i<(int)host.length();i++)
		if (host[i]==':') nD++;
	if (nD>1) return false;
	if (nD==0) return isHost(host);else
		return isHost(host.substr(0,host.find(":"))) && isInteger(host.substr(host.find(":")+1),0,65535);
}

bool isPath(string path)
{
	if (path=="") return true;
	if (path.find("//")!=string::npos) return false;
	vector<string> sep=split(path,'/');
	if (sep[0]!="") return false;
	for (int i=1;i<(int)sep.size();i++)
	{
		if (sep[i].find('.')!=string::npos)
		{
			if (i+1!=sep.size()) return false;
			if (sep[i].find("..")!=string::npos) return false;
			if (sep[i].length()<2) return false;
			if (sep[i][0]=='.' || sep[i][sep[i].length()-1]=='.') return false;
			vector<string> fw=split(sep[i],'.');
			for (int j=0;j<(int)fw.size();j++)
			{
				if (fw[j].size()<1) return false;
				for (int k=0;k<(int)fw[j].length();k++)
					if (!isLetter(fw[j][k])) return false;
			}
			return true;
		}
		else
		{
			for (int j=0;j<(int)sep[i].length();j++)
				if (!isLetter(sep[i][j])) return false;
		}
	}
	return true;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	string url;
	while (cin>>url)
	{
		if (url.substr(0,((string)"http://").length())=="http://")
			url.erase(0,((string)"http://").length());
		string host;
		while (url!="" && url[0]!='/')
		{
			host+=url[0];
			url.erase(0,1);
		}
		if (isHostWithPort(host) && isPath(url)) cout<<"YES\n";else cout<<"NO\n";
	}
}