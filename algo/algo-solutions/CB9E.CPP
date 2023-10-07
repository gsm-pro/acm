#include<iostream>
#include<vector>
#include<algorithm>
#define FORAB(Z,A,B) for(int(Z)=(A);(Z)<(B);(Z)++)
#define sz(a) (int)(a).size()
#define INF (1<<30)
using namespace std;

bool first_greater(vector<int> &a, vector<int> &b) {
	for (int i = 0; i < min(sz(a), sz(b)); i++) {
		if (a[i] > b[i]) {
			return true;
		}
		if (a[i] < b[i]) {
			return false;
		}
	}
	return sz(a) > sz(b);
}

int main() {
	int n;
	cin >> n;
	vector<int> s, s_copy, t(n), ans, rr;
	for (int i = 0; i < n; i++) {
		s.push_back(i);
		cin >> t[i];
	}
	s_copy = s;
	FORAB(i, 0, sz(t)) {
		int minF = INF, minE = INF;
		int i1, i2;
		FORAB(j, 0, sz(s)) {
			if (s[j] > t[i]) {
				if (minF > s[j]) {
					minF = s[j];
					i1 = j;
				}
			}
			else {
				if (s[j] >= t[i]) {
					if (minE > s[j]) {
						minE = s[j];
						i2 = j;
					}
				}
			}
		}
		if (minF < INF) {
			vector<int> tmp = s;
			tmp.erase(tmp.begin() + i1);
			sort(tmp.begin(), tmp.end());
			vector<int> t = rr;
			t.push_back(minF);
			t.insert(t.end(), tmp.begin(), tmp.end());
			if (ans.size() == 0 || first_greater(ans, t)) {
				ans = t;
			}
		}
		if (minE < minF) {
			minF = minE;
			i1 = i2;
		}
		if (minF != INF) {
			rr.push_back(minF);
			s.erase(s.begin() + i1);
		}
		else {
			break;
		}
	}
	sort(s.begin(), s.end());
	rr.insert(rr.end(), s.begin(), s.end());
	if (first_greater(rr, t)) {
		if (ans.size() == 0 || first_greater(ans, rr)) {
			ans = rr;
		}
	}
	if (ans.size() == 0) {
		ans = s_copy;
		sort(ans.begin(), ans.end());
		reverse(ans.begin(), ans.end());
		if (first_greater(t, ans)) {
			for (int i = 0; i < sz(ans); i++) {
				cout << ans[i] << " ";
			}
			return 0;
		}
		if (!prev_permutation(ans.begin(), ans.end())) {
			cout << -1;
			return 0;
		}
		for (int i = 0; i < sz(ans); i++) {
			cout << ans[i] << " ";
		}
		return 0;
	}
	if (!prev_permutation(ans.begin(), ans.end())) {
		cout << -1;
		return 0;
	}
	if (first_greater(t, ans)) {
		for (int i = 0; i < sz(ans); i++) {
			cout << ans[i] << " ";
		}
		return 0;
	}
	if (!prev_permutation(ans.begin(), ans.end())) {
		cout << -1;
		return 0;
	}
	for (int i = 0; i < sz(ans); i++) {
		cout << ans[i] << " ";
	}
}