#include<fstream>
#include<string>
using namespace std;
int one = 0, two = 0, i;
string s;

int main() {
	ifstream("input.txt") >> s;
	for (i = 0; i < s.size(); i++)
		if (s[i] >= 'a') one = min(one, two), two++;
		else one = min(one, two) + 1;
	ofstream("output.txt") << min(one, two);
}