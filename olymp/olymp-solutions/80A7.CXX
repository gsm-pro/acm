#include<bits/stdc++.h>
using namespace std;
const int N = 10010;
ifstream I("input.txt");
ofstream O("output.txt");
pair<int, int> boxes[N];
int boxescnt, contcnt, contszs[N], L[N], T1[N], T2[N], contsz, contmaxsz = 0,
ptr = 1, ans = 0, i, j;

void merge(int* a, int* b, int* r) {
	int n1 = *a, n2 = *b, p1 = 1, p2 = 1;
	*r = 0, a[++n1] = b[++n2] = -(1 << 30);
	while (p1 < n1 || p2 < n2) r[++*r] = a[p1] > b[p2] ? a[p1++] : b[p2++];
	a[n1--] = b[n2--] = 0;
}

int main() {
	I >> boxescnt;
	for (i = 1; i <= boxescnt; i++) I >> boxes[i].first >> boxes[i].second;
	sort(boxes + 1, boxes + boxescnt + 1);
	I >> contcnt;
	for (i = 1; i <= contcnt; i++)
		I >> contsz, I >> contszs[contsz], contmaxsz = max(contmaxsz, contsz);
	for (i = 0; i <= contmaxsz; i++, *T2 = 0) {
		while (boxes[ptr].first == i) T2[++*T2] = boxes[ptr++].second;
		reverse(T2 + 1, T2 + *T2 + 1);
		merge(L, T2, T1);
		for (j = 0; j <= *T1; j++) L[j] = T1[j];
		if (contszs[i] > *L) return O << "NO", 0;
		for (j = 1; j <= contszs[i]; j++) ans += L[*L - j + 1];
		*L -= contszs[i], *T2 = 0;
		for (j = *L; j && j - 1; j -= 2) T2[++*T2] = L[j] + L[j - 1];
		for (j = 0; j <= *T2; j++) L[j] = T2[j];
		reverse(L + 1, L + *L + 1);
	}
	O << "YES\n" << ans;
}