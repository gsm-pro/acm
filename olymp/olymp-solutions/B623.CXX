#include<bits/stdc++.h>
using namespace std;
map<int, int> y2Delta;
vector<pair<int, int>> $;
int cuts = 1, ans, i = -1, n, a, b;

int main() {
	ifstream I("input.txt");
	I >> n;
	while (++i < n + 5) {
		if (i < n) I >> a >> b; else a = $[i - n].first, b = $[i - n].second;
		if ($.size() <= 1) $.push_back({ a, b });
		else if ($[$.size() - 2].second == b && $.back().second == b) $.back().first = a;
		else $.push_back({ a, b });
	}
	$.erase($.begin(), $.begin() + 5);
	long long sq = 0, dt;
	for (i = 0; i < (n = $.size()); i++) {
		auto pre = i ? $[i - 1] : $.back();
		sq += (long long)(pre.first - $[i].first) * (pre.second + $[i].second);
	}
	if (sq > 0) reverse($.begin(), $.end());
	for (i = 0; i < n; i++) {
		int nxt = (i + 1 + ($[i].second == $[(i + 1) % n].second)) % n, pre = (i + n - 1) % n,
			curY = $[i].second, nxtY = $[nxt].second, preY = $[pre].second;
		y2Delta[curY] += (((dt = (long long)($[i].first - $[pre].first) * (nxtY - preY)
			- (long long)(curY - preY) * ($[nxt].first - $[pre].first)) > 0) & (b = curY < nxtY && curY < preY))
			- ((dt < 0) & (a = curY > nxtY && curY > preY));
		y2Delta[curY + 1] += ((dt < 0) & b) - ((dt > 0) & a);
	}
	for (auto& kv : y2Delta)
		if ((cuts += kv.second) > ans) ans = cuts, b = kv.first;
	ofstream("output.txt") << ans << endl << b;
}