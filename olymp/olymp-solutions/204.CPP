#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int zeros[35]={
	193,170,118,139,135,50,97,
	124,86,144,73,41,87,53,65,
	42,93,75,25,32,30,48,29,37,
	16,19,23,11,15,10,7,5,3,2,1};
int BASE=2;
vector<int> a;

void mul_inv(vector<int> &a,vector<int> &c)
{
	vector<int> b(a.rbegin(),a.rend());
	c.resize(2*a.size()+7);
	for (size_t i=0;i<a.size();i++)
		for (size_t j=0;j<a.size();j++)
			c[i+j]+=a[i]*b[j];
}

bool check(vector<int> &a)
{
	vector<int> c;
	mul_inv(a,c);
	for (size_t i=0;i<2*a.size()+3;i++)
	{
		c[i+1]+=c[i]/BASE,c[i]%=BASE;
		if (c[i]!=0 && c[i]!=1) return false;			
	}
	return true;
}

void print(vector<int> a)
{
	while (a.back()==0) a.pop_back();
	for (int i=(int)a.size()-1;i>=0;--i) cout<<a[i];	
}

int main()
{                        
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int Z;
	cin>>Z;
	if (Z<=18)
	{
		a.push_back(1);
		a.push_back(0);
		for (;BASE<=Z;)
		{
			a.push_back(1);
			check(a) ? ++BASE : a.back()=0;
		}
	} else {
		a.push_back(1);
		for (int i=36-Z;i<35;i++)
		{
			for (int j=1;j<=zeros[i];j++) a.push_back(0);
			a.push_back(1);
		}
	}
	BASE=Z;
	vector<int> b(a.rbegin(),a.rend());
	vector<int> c;
	mul_inv(a,c);
	for (size_t i=0;i<2*a.size()+3;i++) c[i+1]+=c[i]/BASE,c[i]%=BASE;
	print(a);
	cout<<"*";
	print(b);
	cout<<"=";
	print(c);
}