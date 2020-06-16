#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;
#define LD long double
#define ZURUCK 3000
#define NMAX 100001
#define LEAP 3000
#define TIMER 0.5

struct item {
	LD ratio;
	int a, b, v;
} P[NMAX];

struct el {
	int prev, info, next;
} EL[NMAX];

bool used[NMAX];
int equiClasses[NMAX];

bool cmp_T1(const item &t1, const item &t2) {
	return t1.ratio > t2.ratio || (t1.ratio == t2.ratio && t1.a < t2.a);
}

bool cmp_T2(const item &t1, const item &t2) {
	return t1.a < t2.a;
}

bool cmp_T3(const item &t1, const item &t2) {
	return t1.ratio > t2.ratio || (t1.ratio == t2.ratio && t1.a > t2.a);
}

int gcd(int a, int b) {
	for (; b;) b ^= a ^= b ^= a %= b;
	return a;
}

double solve(int n, int k, item P[], int zuruck, LD &val, vector<int> &ans) {
	double tstart = clock();
	ans.clear();
	LD u = 0, v = 0;
	for (int i = 0; i < k; i++) {
		u += P[i].a, v += P[i].b;
		used[i] = true;
	}
	for (int i = 0; i < n; i++) {
		EL[i].prev = i - 1, EL[i].info = i, EL[i].next = i + 1;
		if (i) {
			if (P[i].ratio == P[i - 1].ratio) {
				equiClasses[i] = equiClasses[i - 1];
			}
			else {
				equiClasses[i] = equiClasses[i - 1] + 1;
			}
		}
		else {
			equiClasses[0] = 1;
		}
	}
	LD best_u = u, best_v = v;
	for (int current = k; current < n; current++) {
		int worst_index = -1, iters = 0, try_worst = EL[current].prev;
		LD upa = u + P[current].a, vpb = v + P[current].b, cur_best_u = best_u, cur_best_v = best_v;
		for (;;) {
			LD cur_u = upa - P[try_worst].a, cur_v = vpb - P[try_worst].b;
			if (cur_u * cur_best_v > cur_v * cur_best_u) {
				cur_best_u = cur_u, cur_best_v = cur_v, worst_index = try_worst;
			}
			bool canJump = (try_worst > LEAP && equiClasses[try_worst] == equiClasses[try_worst - LEAP]);
			if (canJump) {
				while ((try_worst > LEAP && equiClasses[try_worst] == equiClasses[try_worst - LEAP])) {
					try_worst = EL[try_worst - LEAP].info;
				}
			}
			else {
				try_worst = EL[try_worst].prev;
			}
			if (try_worst == -1 || iters == zuruck) {
				break;
			}
			iters++;
		}
		if (worst_index == -1) {
			worst_index = current;
		}
		else {
			u = upa - P[worst_index].a, v = vpb - P[worst_index].b;
			best_u = cur_best_u, best_v = cur_best_v;
			used[current] = true;
		}
		used[worst_index] = false;
		EL[EL[worst_index].prev].next = EL[worst_index].next;
		EL[EL[worst_index].next].prev = EL[worst_index].prev;
	}
	val = best_u / best_v;
	for (int i = 0; i < n; i++) {
		if (used[i]) {
			ans.push_back(P[i].v + 1);
		}
	}
	return (clock() - tstart) / CLOCKS_PER_SEC;
}

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	vector<item> T1, T2, T3;
	for (int i = 0; i < n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		int d = gcd(x, y);
		item nxt;
		nxt.a = x, nxt.b = y;
		x /= d, y /= d, nxt.ratio = ((LD)x) / ((LD)y), nxt.v = i;
		if (x > y) {
			T1.push_back(nxt);
		}
		if (x == y) {
			T2.push_back(nxt);
		}
		if (x < y) {
			T3.push_back(nxt);
		}
	}
	n = 0;
	sort(T1.begin(), T1.end(), cmp_T1);
	for (size_t i = 0; i < T1.size(); i++) {
		P[n++] = T1[i];
	}
	sort(T2.begin(), T2.end(), cmp_T2);
	for (size_t i = 0; i < T2.size(); i++) {
		P[n++] = T2[i];
	}
	sort(T3.begin(), T3.end(), cmp_T3);
	for (size_t i = 0; i < T3.size(); i++) {
		P[n++] = T3[i];
	}
	LD maxValue;
	vector<int> ans;
	double timer = solve(n, k, P, ZURUCK, maxValue, ans);
	if (timer < TIMER) {
		solve(n, k, P, ZURUCK * 3, maxValue, ans);
	}
	printf("%.9lf\n", maxValue);
	for (size_t i = 0; i < ans.size(); i++) {
		printf("%d ", ans[i]);
	}
}