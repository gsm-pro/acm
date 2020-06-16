#include<iostream>
#include<cmath>

int main()
{
	double x1,y1,x2,y2;
	std::cin>>x1>>y1>>x2>>y2;
	std::cout.precision(9);
	std::cout<<std::fixed<<atan2(fabs(x1*y2-y1*x2),(x1*x2+y1*y2));
}