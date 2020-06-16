#include<iostream>
#include<algorithm>
using namespace std;
#define NMAX 111111

struct TNode {
	int l, r;
} nodes[NMAX];

bool cmp(TNode a, TNode b) {
	return a.l == b.l ? a.r < b.r : a.l < b.l;
}

int main() {
	int total = 1, M;
	scanf_s("%d", &M);
	scanf_s("%d%d", &nodes[total].l, &nodes[total].r);
	if (nodes[total].l == 0 && nodes[total].r == 0) {
		return printf("No solution"), 0;
	}
	while (nodes[total].l || nodes[total].r) {
		total++;
		scanf_s("%d%d", &nodes[total].l, &nodes[total].r);
	}
	sort(nodes + 1, nodes + total, cmp);
	int num = 0, cur = 0, next_ans_index = 0;
	nodes[0].l = nodes[0].r = -NMAX;
	bool flag = true;
	while (true) {
		if (cur >= M) {
			break;
		}
		int right = cur;
		for (int i = next_ans_index; i + 1 < total; i++) {
			if (nodes[i + 1].l <= cur && nodes[i + 1].r > right) {
				next_ans_index = i + 1;
				right = nodes[next_ans_index].r;
			}
		}
		if (nodes[next_ans_index].r <= cur) {
			flag = false;
			break;
		}
		else {
			num++;
			cur = nodes[next_ans_index].r;
		}
	}
	if (!flag) {
		return printf("No solution"), 0;
	}
	printf("%d", num);
}