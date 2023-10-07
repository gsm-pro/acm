#include<bits/stdc++.h>
using namespace std;
set<int> $;
set<pair<int, int>> $$;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, m, curI = 0, curFloor = 1;
	__int64 curTime = 0;
	scanf("%d%d", &n, &m);
	vector<int> t(n), a(n);
	for (int i = 0; i < n; i++) scanf("%d%d", &t[i], &a[i]);
	auto addAll = [&]() {
		while (curI < n && t[curI] <= curTime) {
			$.insert(curI);
			$$.insert({ a[curI], curI });
			curI++;
		}
	};
	vector<__int64> ans(n, -1);
	while (true) {
		if ($.empty()) {
			if (curI == n) break;
			curTime = t[curI];
		}
		addAll();
		int id = *$.begin();
		curTime += a[id] - 1;
		curFloor = a[id];
		while (curFloor != 1) {
			addAll();
			while (true) {
				auto it = $$.lower_bound({ curFloor, -1 });
				if (it != $$.end() && it->first == curFloor) {
					int cid = it->second;
					ans[cid] = curTime + curFloor - 1;
					$.erase(cid);
					$$.erase(it);
				}
				else break;
			}
			int nextEvent = curFloor - 1;
			if (curI < n) nextEvent = min((__int64)nextEvent, t[curI] - curTime);
			auto it = $$.lower_bound({ curFloor, -1 });
			if (it != $$.begin()) nextEvent = min(nextEvent, curFloor - (--it)->first);
			curTime += nextEvent;
			curFloor -= nextEvent;
		}
	}
	for (int i = 0; i < n; i++) printf("%lld\n", ans[i]);
}