#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main() {
	int N, BS = 0;
	scanf_s("%d\n", &N);
	vector<int> V;
	for (int i = 0; i < N; i++) {
		V.push_back(getchar() - 'A');
		BS += V.back();
	}
	int cur = 0, L = 0, R = BS;
	for (int i = L; i < R; i++) {
		cur += V[i];
	}
	int ans = BS - cur, steps = 888888;
	while (steps--) {
		L = (L + 1) % N, R = (R + 1) % N;
		cur = cur - V[(L - 1 + N) % N] + V[(R - 1 + N) % N];
		ans = min(ans, BS - cur);
	}
	cout << ans;
}