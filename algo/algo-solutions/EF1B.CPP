#include<cmath>
#include<iostream>

int main() 
{
	double x1,y1,x2,y2,x3,y3,u;
	std::cin>>x1>>y1>>x2>>y2>>x3>>y3;
	u=(atan2(y2-y1,x2-x1)+atan2(y3-y1,x3-x1))/2;
	std::cout.precision(9);
	std::cout<<sin(u)<<" "<<-cos(u)<<" "<<-sin(u)*x1+cos(u)*y1;
}