#include<list>

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int h,m,s,x,y,z;
	scanf("%d:%d:%d\n%d:%d:%d",&h,&m,&s,&x,&y,&z);
	s+=z,m+=y+(s>=60),h+=x+(m>=60);
	printf("%02d:%02d:%02d",h%24,m%60,s%60);
}