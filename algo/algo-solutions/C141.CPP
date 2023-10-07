#define _USE_MATH_DEFINES
#include<iostream>
#include<cmath>

int main()
{
    	double x,y;
	std::cin>>x>>y;
	std::cout<<std::fixed<<atan2(y,x)*180/M_PI+(y<0)*360;
}