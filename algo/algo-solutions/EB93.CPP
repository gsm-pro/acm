#include<queue>
#include<iostream>
#include<sstream>
#include<map>
#include<cassert>
using namespace std;
int amounts[256] = { 0 }, z;
map<string, string> m;

struct Node {
	string value, code;
	int amount;
	Node * left;
	Node * right;

	bool operator() (const Node& x, const Node& y) const {
		return x.amount > y.amount;
	}

	Node(const string& value = "", int amount = 0, Node * left = 0, Node * right = 0) {
		this->value = value;
		this->code = "";
		this->amount = amount;
		this->left = left;
		this->right = right;
	}

	void to_map() {
		m[value] = code;
		if (left != 0 || right != 0) {
			left->to_map();
			right->to_map();
		}
	}

	Node * join(Node x) {
		return new Node(x.value + value, x.amount + amount, new Node(x), this);
	}

	void build_code(string code) {
		this->code = code;
		if (left != 0 || right != 0) {
			left->build_code(code + "1");
			right->build_code(code + "0");
		}
	}

	static Node * build(priority_queue<Node, vector<Node>, Node> graph) {
		while (graph.size() > 1) {
			Node *n = new Node(graph.top());
			graph.pop();
			graph.push(*n->join(*new Node(graph.top())));
			graph.pop();
		}
		return new Node(graph.top());
	}
};

int main() {
	string s;
	cin >> z >> s;
	assert(z <= 26);
	for (int i = 0; i < (int)s.length(); i++) amounts[(char)s[i]]++;
	priority_queue<Node, vector<Node>, Node> graph;
	for (int i = 'a'; i <= ('a' + z - 1); i++) {
		graph.emplace(*new Node(s = (char)i, amounts[i]));
	}
	Node *n = Node::build(graph);
	n->build_code(z == 1 ? "0" : "");
	n->to_map();
	for (int i = 'a'; i <= ('a' + z - 1); i++) {
		cout << m[s = (char)i] << endl;
	}
}