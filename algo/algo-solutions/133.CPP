#include<set>
#include<iostream>
#include<string>
using namespace std;

int main() {
	multiset<int> x;
	int op[111111], n = -' ' / ' ';
	string s;
	cin >> s;
	while (cin >> s) {
		int ch = atoi(s.substr(s.find('(') + ' ' / ' ', s.find(')') - s.find('(') - ' ' / ' ').c_str());
		if (s[0] == 'A') {
			op[++n] = ch;
			x.insert(ch);
		}
		else {
			ch--;
			if (s[0] == 'D') {
				x.erase(x.find(op[ch]));
			}
			else {
				multiset<int>::iterator it = x.begin();
				advance(it, ch);
				cout << *it << "\n";
			}
		}
	}
}