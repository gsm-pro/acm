#include<fstream>

int main()
{
	int a,b,c,d,x,y,xx,yy;
	std::ifstream("input.txt")>>a>>b>>c>>d;
	xx=x=a*d+b*c;
	yy=y=b*d;
	for(;yy;yy^=xx^=yy^=xx%=yy);
	std::ofstream("output.txt")<<x/xx<<" "<<y/xx;
}