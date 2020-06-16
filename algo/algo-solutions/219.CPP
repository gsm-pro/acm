#include<iostream>
#include<string>
#include<cassert>
#include<map>
#include<stack>
using namespace std;
#define forn(i,n) for(int i=0;i<n;i++)
#define sz(a) int((a).size())
#define pb push_back
string code;
int p=0,next[500000];
map<string,int> z;

bool read(string s,int idx)
{
	if (idx+sz(s)>sz(code)) return false;
	forn(i,sz(s)) if (code[i+idx]!=s[i]) return false;
	return true;
}

void skip()
{
	while (p<sz(code) && (isspace(code[p]) || code[p]=='\n')) p++;
}

int nextInt()
{
	string ans;
	while (p<sz(code) && isdigit(code[p])) ans.pb(code[p++]);
	return atoi(ans.c_str());
}

string getVarName()
{
	string ans;
	skip();
	while (p<sz(code) && (isalpha(code[p]) || isdigit(code[p]) || code[p]=='_')) ans.pb(code[p++]);
	return ans;
}

int add();

int unary()
{
	skip();
	if (code[p]=='(')
	{
		p++;
		int ans=add();
		skip();
		assert(code[p]==')'),p++;
		return ans;
	}
	if (code[p]=='-')
	{
		p++;
		return -unary();
	}
	if (code[p]=='+')
	{
		p++;
		return unary();
	}
	if (isdigit(code[p])) return nextInt();
	return z[getVarName()];
}

int mul()
{
	int ans=unary();
	while (p<sz(code))
	{
		skip();
		if (read("*",p)) p++,ans*=unary();else 
			if (read("div",p)) p+=3,ans/=unary();else
				if (read("mod",p)) p+=3,ans%=unary();else break;
	}
	return ans;
}

int add()
{
	int ans=mul();
	while (p<sz(code))
	{
		skip();
		if (read("+",p)) p++,ans+=mul();else
			if (read("-",p)) p++,ans-=mul();else break;
	}
	return ans;
}

bool _COND()
{
	int a=add();
	skip();
	char t=code[p++];
	int b=add();
	return (t=='<') ? (a<b) : ((t=='=') ? (a==b) : (a>b));
}

bool LAdd();

bool LUnary()
{
	skip();
	int old=p;
	if (code[p]=='(')
	{
		p=next[p]+1;
		skip();
		if (read("or",p) || read("and",p) || read("then",p) || read(")",p))
		{
			p=old;
			skip();
			p++;
			bool ans=LAdd();
			skip();
			assert(code[p]==')'),p++;
			return ans;
		} else p=old;
	}
	if (read("not",p))
	{
		p+=3;
		return !LUnary();
	}
	return _COND();
}

bool LMul()
{
	bool ans=LUnary();
	while (p<sz(code))
	{
		skip();
		if (read("and",p)) p+=3,ans=LUnary() && ans;else break;
	}
	return ans;
}

bool LAdd()
{
	bool ans=LMul();
	while (p<sz(code))
	{
		skip();
		if (read("or",p)) p+=2,ans=LMul() || ans;else break;
	}
	return ans;
}

bool _ASSIGN(bool c)
{
	int old=p;
	skip();
	string n=getVarName();
	skip();
	if (read(":=",p))
	{
		p+=2;
		int val=add();
		if (c) z[n]=val;
		return true;
	}
	p=old;
	return false;
}

bool _WRITELN(bool c)
{
	int old=p;
	skip();
	if (!read("writeln",p))
	{
		p=old;
		return false;
	}
	p+=7;
	skip();
	if (code[p]!='(')
	{
		p=old;
		return false;
	}
	p++;
	int val=add();
	if (c) cout<<val<<endl;
	skip();
	if (!(code[p]==')'))
	{
		p=old;
		return false;
	} else p++;
	return true;
}

bool process(bool);

bool _FOR_TO_DO(bool c)
{
	int old=p;
	skip();
	if (!read("for",p))
	{
		p=old;
		return false;
	}
	p+=3;
	if (!isspace(code[p]))
	{
		p=old;
		return false;
	}
	string n=getVarName();
	skip();
	if (!read(":=",p))
	{
		p=old;
		return false;
	} else p+=2;
	z[n]=add();
	skip();
	if (!read("to",p))
	{
		p=old;
		return false;
	} else p+=2;
	int end=add();
	skip();
	if (!read("do",p))
	{
		p=old;
		return false;
	} else p+=2;
	old=p;
	for (;z[n]<=end;z[n]++)
	{
		p=old;
		process(c);
	}
	p=old;
	process(false);
	return true;
}

bool _IF_THEN(bool c)
{
	int old=p;
	skip();
	if (!read("if",p))
	{
		p=old;
		return false;
	}
	p+=2;
	if (!isspace(code[p]))
	{
		p=old;
		return false;
	}
	c=LAdd() && c;
	skip();
	if (!read("then",p))
	{
		p=old;
		return false;
	} else p+=4;
	process(c);
	return true;
}

void seq(bool);

bool process(bool c)
{
	skip();
	if (!_IF_THEN(c) && !_FOR_TO_DO(c) && !_WRITELN(c) && !_ASSIGN(c))
	{
		if (read("begin",p) && isspace(code[p+5]))
		{
			int old=p;
			p+=5;
			seq(c);
			skip();
			if (!read("end",p))
			{
				p=old;
				return false;
			} else p+=3;
		} else return false;
	}
	return true;
}

void seq(bool c)
{
	skip();
	while (process(c))
	{
		skip();
		if (code[p]!=';') break;
		p++;
	}
}

string toLower(string s)
{
	string ans;
	forn(i,sz(s)) ans.pb(tolower(s[i]));
	return ans;
}

int main()
{
	string t,tt="";
	bool flag=false;
	while (cin>>t)
	{
		if (toLower(t)=="begin") flag=true;
		if (flag) tt+=(t+" ");
	}
	tt=toLower(tt);
	char prev=tt[0];
	code+=tt[0];
	for (int i=1;i<sz(tt);i++)
	{
		if (!(tt[i]==';' && prev==';')) code+=tt[i];
		if (tt[i]!=' ') prev=tt[i];
	}
	stack<int> s;
	forn(i,sz(code))
	{
		if (code[i]=='(') s.push(i);else 
			if (code[i]==')') next[s.top()]=i,s.pop();
	}
	process(true);
}