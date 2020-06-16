#define _CRT_SECURE_NO_DEPRECATE
#include<cmath>
#include<iostream>
#include<vector>
using namespace std;
#define PI acos((double)(-1.0))
#define PI_TWO (2.0 * PI)
#define FOR(i,a,b) for(int (i)=(a);i<(b);(i)++)
typedef long long LL;
int N;
LL A[1 << 21];
double X[1 << 23], Y[1 << 23];

void fft(double data[], int nn, int isign) {
	int n, mmax, m, j, istep, i;
	double wtemp, wr, wpr, wpi, wi, theta, tempr, tempi;
	n = nn << 1;
	j = 1;
	for (i = 1; i < n; i += 2) {
		if (j > i) {
			tempr = data[j];
			data[j] = data[i];
			data[i] = tempr;
			tempr = data[j + 1];
			data[j + 1] = data[i + 1];
			data[i + 1] = tempr;
		}
		m = n >> 1;
		while (m >= 2 && j > m) {
			j -= m;
			m >>= 1;
		}
		j += m;
	}
	mmax = 2;
	while (n > mmax) {
		istep = 2 * mmax;
		theta = PI_TWO / (isign * mmax);
		wtemp = sin(0.5 * theta);
		wpr = -2.0 * wtemp * wtemp;
		wpi = sin(theta);
		wr = 1.0;
		wi = 0.0;
		for (m = 1; m < mmax; m += 2) {
			for (i = m; i <= n; i += istep) {
				j = i + mmax;
				tempr = wr * data[j] - wi * data[j + 1];
				tempi = wr * data[j + 1] + wi * data[j];
				data[j] = data[i] - tempr;
				data[j + 1] = data[i + 1] - tempi;
				data[i] += tempr;
				data[i + 1] += tempi;
			}
			wr = (wtemp = wr) * wpr - wi * wpi + wr;
			wi = wi * wpr + wtemp * wpi + wi;
		}
		mmax = istep;
	}
}

int main() {
	scanf("%d", &N);
	FOR(i, 1, N + 1) {
		scanf("%I64d", &A[i]);
	}
	int su = 0;
	FOR(i, 1, N + 1) {
		su += (int)A[i];
	}
	FOR(i, 0, 1 << 23) {
		X[i] = Y[i] = 0;
	}
	X[1] = Y[2 * su + 1] = 1;
	int t = 0;
	FOR(i, 1, N + 1) {
		t += (int)A[i];
		X[2 * t + 1]++;
		Y[2 * (su - t) + 1]++;
	}
	int lim = su;
	while (su & (su - 1)) {
		su &= su - 1;
	}
	su <<= 1;
	fft(X, su * 2, 1);
	fft(Y, su * 2, 1);
	FOR(i, 0, su * 2) {
		int p = 2 * i + 1, q = 2 * i + 2;
		double a = X[p] * Y[p] - X[q] * Y[q], b = X[p] * Y[q] + X[q] * Y[p];
		X[p] = a;
		X[q] = b;
	}
	fft(X, su * 2, -1);
	vector<pair<int, LL>> ans;
	LL total = (((LL)N) + 1LL) * ((LL)N) / 2;
	FOR(i, lim + 1, lim * 2 + 1) {
		LL val = ((LL)((X[2 * i + 1]) / (su * 2.0) + .5));
		if (val != 0) {
			ans.push_back(make_pair(i - lim, val));
			total -= ans.back().second;
		}
	}
	if (total > 0) {
		printf("%d - %I64d\n", 0, total);
	}
	for (size_t i = 0; i < ans.size(); i++) {
		printf("%d - %I64d\n", ans[i].first, ans[i].second);
	}
}