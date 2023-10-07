#define _USE_MATH_DEFINES
#include<iostream>
#include<cmath>

int main()
{
	double x1,y1,x2,y2,a;
	std::cin>>x1>>y1>>x2>>y2;
	a=atan2((x1*y2-y1*x2),(x1*x2+y1*y2));
	if (a<0) a+=2*M_PI;
	std::cout.precision(9);
	std::cout<<std::fixed<<a;
}