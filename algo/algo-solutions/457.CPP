#include<iostream>
using namespace std;
int a[55555], b[55555], X = 0, n;

inline bool lessOrEqual(int u, int v) {
	printf("comparing %d and %d\n", u, v);
	return u <= v;
}

inline bool greater(int u, int v) {
	printf("comparing %d and %d\n", u, v);
	return u > v;
}

void merge(int left1, int right1, int left2, int right2) {
	printf("merging segments [%d, %d] and [%d, %d]\n", left1, right1, left2, right2);
	int i = left1, j = left2, k = left1;
step2:
	if (i <= right1 && j <= right2) {
		goto step3;
	}
	else {
		goto step6;
	}
step3:
	if (lessOrEqual(a[i], a[j])) {
		goto step4;
	}
	else {
		goto step5;
	}
step4:
	b[k++] = a[i++];
	goto step2;
step5:
	b[k++] = a[j++];
	goto step2;
step6:
	while (i <= right1) {
		b[k++] = a[i++];
	}
	while (j <= right2) {
		b[k++] = a[j++];
	}
	for (int ii = left1; ii <= right2; ii++) {
		a[ii] = b[ii];
	}
	printf("segments [%d, %d] and [%d, %d] merged\n", left1, right1, left2, right2);
}

void sort(int left, int right) {
	printf("sorting segment [%d, %d]\n", left, right);
	if (left == right) {
		printf("segment [%d, %d] sorted\n", left, right);
		return;
	}
	if (left + 1 == right) {
		if (greater(a[left], a[right])) {
			swap(a[left], a[right]);
		}
		printf("segment [%d, %d] sorted\n", left, right);
		return;
	}
	int mid = (left + right) >> 1;
	sort(left, mid);
	sort(mid + 1, right);
	merge(left, mid, mid + 1, right);
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