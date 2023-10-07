#define _CRT_SECURE_NO_DEPRECATE
#include<cstdio>
#include<string>
#include<set>
using namespace std;

template <typename key_type,typename value_type> class mypair
{
public:
	key_type key;
	value_type val;
	mypair(void)                                    {}
	mypair(key_type k)              : key(k)        {}
	mypair(key_type k,value_type v) : key(k),val(v) {}
};

template <typename kt,typename vt> inline bool operator < (const mypair<kt,vt> &a,const mypair<kt,vt> &b)
{
	return a.key<b.key;
}

template <typename key_type,typename value_type> class mymap
{
public:
	set<mypair<key_type,value_type>> base;
public:    
	value_type & operator [] (const key_type &key)
	{
		mypair<key_type,value_type> temp(key);
		set<mypair<key_type,value_type>>::iterator it;
		if ((it=base.find(temp))==base.end()) it=base.insert(temp).first;
		return (it->val);
	}
};

mymap <string,mymap<string,string>> ini;
enum {MAXLEN=256};

int main(void)
{
	char s[MAXLEN],key[MAXLEN],val[MAXLEN];
	string sec("");
	int n;
	scanf("%d",&n);
	while(n-->0)
	{
		scanf(" ");
		if (scanf("%[[]",s)==1)
		{
			scanf(" ");
			scanf("%[^] ] ]", s);
			ini[sec=s];
		}
		else 
			if(scanf("%[;]",s)==1) scanf("%*[^\n]");else
			{
				scanf(" ");
				scanf("%[^= ]",key);
				scanf(" =");
				if (scanf("%s",val)!=-1)
					ini[sec][string(key)]=string(val);
				else break;
			}
	}
	set<mypair<string,mymap<string,string>>>::iterator sit,send;
	set<mypair<string,string>>::iterator rit,rend;
	for (sit=ini.base.begin(),send=ini.base.end();sit!=send;++sit)
	{
		if (sit->key!="") printf("[%s]\n",sit->key.c_str());
		for (rit=sit->val.base.begin(),rend=sit->val.base.end();rit!=rend;++rit)
			printf("%s=%s\n",rit->key.c_str(),rit->val.c_str());
	}
}