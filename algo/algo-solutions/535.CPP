#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include<algorithm>
using namespace std;
char expr[1111];

struct subexpr {
	int start, end, length;
};

bool cmp(const subexpr a, const subexpr b) {
	if (a.length != b.length) {
		return a.length < b.length;
	}
	return a.start < b.start;
}

int getflag(int index) {
	if (expr[index] == '+') {
		return 1;
	}
	else if (expr[index] == '-') {
		return 2;
	}
	else if (expr[index] == '*') {
		return 3;
	}
	else if (expr[index] == '/') {
		return 4;
	}
	else {
		return -1;
	}
}

string simplify(string s) {
	memset(expr, 0, sizeof expr);
	for (size_t i = 0; i < s.size(); i++) {
		expr[i + 1] = s[i];
	}
	vector<subexpr> sects;
	int L = strlen(expr + 1);
	stack<int> st;
	for (int i = 1; i <= L; i++) {
		if (expr[i] == '(') {
			st.push(i);
		}
		if (expr[i] == ')') {
			int x = st.top();
			st.pop();
			subexpr temp;
			temp.start = x, temp.end = i, temp.length = i - x + 1;
			sects.push_back(temp);
		}
	}
	sort(sects.begin(), sects.end(), cmp);
	int used[1111] = { 0 };
	for (size_t i = 0; i < sects.size(); i++) {
		int lflag = getflag(sects[i].start - 1), rflag = getflag(sects[i].end + 1);
		bool flag = true;
		if (lflag == 3 || lflag == 4 || rflag == 3 || rflag == 4) {
			for (int j = sects[i].start + 1; j < sects[i].end; j++) {
				if (used[j] == -1) {
					continue;
				}
				if (expr[j] == '+' || expr[j] == '-') {
					flag = false;
					break;
				}
			}
			if (!flag) {
				for (int j = sects[i].start; j <= sects[i].end; j++) {
					if (used[j] == 0) {
						used[j] = -1;
					}
				}
			}
		}
		if ((lflag == 1 || lflag == -1) && flag) {
			used[sects[i].start] = used[sects[i].end] = 1;
		}
		if (lflag == 2 && flag) {
			used[sects[i].start] = used[sects[i].end] = 1;
			for (int j = sects[i].start + 1; j < sects[i].end; j++) {
				if (used[j] != -1 && expr[j] == '+') {
					expr[j] = '-';
				}
				else if (used[j] != -1 && expr[j] == '-') {
					expr[j] = '+';
				}
			}
		}
		if (lflag == 3 && flag) {
			used[sects[i].start] = used[sects[i].end] = 1;
		}
		if (lflag == 4 && flag) {
			used[sects[i].start] = used[sects[i].end] = 1;
			for (int j = sects[i].start; j <= sects[i].end; j++) {
				if (used[j] != -1 && expr[j] == '/') {
					expr[j] = '*';
				}
				else if (used[j] != -1 && expr[j] == '*') {
					expr[j] = '/';
				}
			}
		}
	}
	string res = "";
	for (int i = 1; i <= L; i++) {
		if (used[i] != 1) {
			res += expr[i];
		}
	}
	return res;
}

int main() {
	string s;
	cin >> s;
	cout << simplify(s);
}