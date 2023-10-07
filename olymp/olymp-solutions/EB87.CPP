#include<fstream>

int main()
{
	std::ifstream I("input.txt");
	std::ofstream O("output.txt");
	int a,b;
	I>>a>>b;
	int c=a,d=b,s=1,t=1;
	while (d--) s*=a;
	while (c--) t*=b;
	(s==t) ? O<<"EQUAL" : (s<t) ? O<<"LESS" : O<<"GREATER";
}