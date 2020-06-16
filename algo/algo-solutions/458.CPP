#include<iostream>
using namespace std;
int a[55555], X = 0, n;
const int A = 1009;
const int B = 1013;
const int M = 1046527;

inline int rnd(int N) {
	X = (A * X + B) % M;
	return X % N;
}

void partition(int left, int right, int &x, int &y) {
	x = left, y = right;
	int p = a[left + rnd(right - left + 1)];
	printf("partitioning segment [%d, %d] around %d\n", left, right, p);
label:
	if (x > y) {
		printf("segment [%d, %d] partitioned around %d\n", left, right, p);
		return;
	}
	while (a[x] < p) {
		x++;
	}
	while (a[y] > p) {
		y--;
	}
	if (x <= y) {
		swap(a[x++], a[y--]);
	}
	goto label;
}

void sort(int left, int right) {
	printf("sorting segment [%d, %d]\n", left, right);
	if (left == right) {
		printf("segment [%d, %d] sorted\n", left, right);
		return;
	}
	if (left + 1 == right) {
		if (a[left] > a[right]) {
			swap(a[left], a[right]);
		}
		printf("segment [%d, %d] sorted\n", left, right);
		return;
	}
	int x, y;
	partition(left, right, x, y);
	if (left <= y) {
		sort(left, y);
	}
	if (x <= right) {
		sort(x, right);
	}
	printf("segment [%d, %d] sorted\n", left, right);
}

int main() {
	scanf_s("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf_s("%d", &a[i]);
	}
	sort(1, n);
	printf("result: ");
	for (int i = 1; i <= n; i++) {
		printf("%d ", a[i]);
	}
}