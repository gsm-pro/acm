#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<set>
using namespace std;
set<int> x;

typedef struct {
	int num;
} BSTItem;

typedef struct BSTNode {
	BSTItem info;
	struct BSTNode* left;
	struct BSTNode* right;
} BST;

BST* bst_add(BST* nod, int number) {
	if (nod == NULL) {
		nod = (BST*)malloc(sizeof(BST));
		if (nod == NULL) {
			return NULL;
		}
		nod->info.num = number;
		nod->left = NULL;
		nod->right = NULL;
		return nod;
	}
	if (nod->info.num > number) {
		nod->left = bst_add(nod->left, number);
	}
	else {
		nod->right = bst_add(nod->right, number);
	}
	return nod;
}

int bst_rank(BST* nod, int val) {
	if (nod == NULL) {
		return 0;
	}
	if (nod->info.num == val) {
		return 1;
	}
	if (nod->info.num > val) {
		return bst_rank(nod->left, val) + 1;
	}
	return bst_rank(nod->right, val) + 1;
}

BST* bst_find(BST* nod, int val) {
	if (nod == NULL) {
		return NULL;
	}
	if (nod->info.num == val) {
		return nod;
	}
	if (nod->info.num > val) {
		return bst_find(nod->left, val);
	}
	return bst_find(nod->right, val);
}

int main() {
	BST* bst = NULL;
	int n, type, v;
	cin >> n;
	while (n--) {
		cin >> type >> v;
		if (type == 1) {
			if (bst_find(bst, v) == NULL) {
				x.insert(v);
				cout << "1 ";
				bst = bst_add(bst, v);
			}
			else {
				cout << "0 ";
			}
		}
		if (type == 2) {
			if (bst_find(bst, v) == NULL) {
				cout << "0 ";
			}
			else {
				cout << "1 ";
			}
		}
	}
	int maxh = 0;
	double sumh = 0;
	for (set<int>::iterator it = x.begin(); it != x.end(); it++) {
		int r = bst_rank(bst, *it);
		maxh = max(maxh, r);
		sumh += r;
	}
	cout << endl << maxh << endl;
	if (!x.size()) {
		cout << 0;
	}
	else {
		cout.precision(8);
		cout << fixed << sumh / x.size();
	}
}