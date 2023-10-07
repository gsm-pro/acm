#include<iostream>
using namespace std;
int n, k, lf = 0, rg = (1 << 30), mid, job[111], sum_cur_friend, used_friends;

int main() {
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> job[i];
	}
	while (lf <= rg) {
		mid = (lf + rg) >> 1;
		bool can = true;
		for (int i = 0; i < n; i++) {
			if (job[i] > mid) {
				can = false;
			}
		}
		if (can) {
			sum_cur_friend = 0;
			used_friends = 1;
			for (int i = 0; i < n; i++) {
				if (sum_cur_friend + job[i] <= mid) {
					sum_cur_friend += job[i];
				}
				else {
					used_friends++;
					sum_cur_friend = job[i];
				}
			}
		}
		if (!can || k < used_friends) {
			lf = mid + 1;
			continue;
		}
		if (k >= used_friends) {
			rg = mid - 1;
		}
	}
	cout << lf;
}