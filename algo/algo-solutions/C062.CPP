#include<cstdio>
#include<vector>
using namespace std;
int s=0;

void downHeap(int a[],int k,int n)
{
	while(true)
	{
		int left=(2*k)+2;
		int right=(2*k)+1;
		int largest;
		if (left<n && a[left]>a[k]) largest=left;else largest=k;
		if (right<n && a[right]>a[largest]) largest=right;
		if (largest==k) break;
		swap(a[k],a[largest]);
		k=largest;
		s++;
	}
}

void heapSort(int a[],int size)
{
	for (int i=(size-1)/2;i>=0;i--) downHeap(a,i,size);
	for (int i=size-1;i>=1;i--)
	{
		swap(a[i],a[0]);
		downHeap(a,0,i);
	}
}

void main()
{
	int a[50000];
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d",&a[i]);
	heapSort(a,n);
	printf("%d",s);
}