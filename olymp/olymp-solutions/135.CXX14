#include<bits/stdc++.h>
using namespace std;

typedef class Operation
{
public:
    char op;
    int x, y;

    Operation() : op('='), x(-1), y(-1) {}
    Operation(char op, int x, int y) : op(op), x(x), y(y) {}

    bool operator < (Operation b) const
    {
        if (op != b.op)
        {
            return op < b.op;
        }
        if (x != b.x)
        {
            return x < b.x;
        }
        return y < b.y;
    }
} Operation;

int n, m;
bool is_op[256];
map<string, int> val;
map<int, string> org;
vector<string> result;
map<int, Operation> val_to_op;
map<Operation, int> op_to_val;
map<int, string> new_var;

void add(string x)
{
    org[m] = x;
    val[x] = m++;
}

string make_new()
{
    string s = "aaaa";
    do
    {
        s[rand() % 4] = rand() % 26 + 'a';
    }
    while (val.count(s));
    val[s] = -1;
    return s;
}

void dfs(int v, bool top = false)
{
    if (org.count(v))
    {
        if (top && org[v] != "res")
        {
            result.push_back("res=" + org[v]);
        }
        new_var[v] = org[v];
        return;
    }
    if (new_var.count(v))
    {
        return;
    }
    Operation op = val_to_op[v];
    dfs(op.x);
    dfs(op.y);
    result.push_back((new_var[v] = (top ? ("res") : (make_new()))) + "=" + new_var[op.x] + op.op + new_var[op.y]);
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    srand(time(NULL));
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    is_op['$'] = is_op['^'] = is_op['#'] = is_op['&'] = true;
    string str, a, b, c;
    cin >> n;
    while (n--)
    {
        cin >> str;
        int idx = str.find('='), idx1;
        a = str.substr(0, idx);
        for (idx1 = idx; idx < (signed)str.size() && !is_op[str[idx]]; idx++);
        if (idx == (signed)str.size())
        {
            b = str.substr(idx1 + 1);
            if (!val.count(b))
            {
                add(b);
            }
            val[a] = val[b];
        }
        else
        {
            b = str.substr(idx1 + 1, idx - idx1 - 1), c = str.substr(idx + 1);
            if (!val.count(b))
            {
                add(b);
            }
            if (!val.count(c))
            {
                add(c);
            }
            Operation op(str[idx], val[b], val[c]);
            if (!op_to_val.count(op))
            {
                op_to_val[op] = m, val_to_op[m] = op, val[a] = m++;
            }
            else
            {
                val[a] = op_to_val[op];
            }
        }
    }
    if (!val.count("res"))
    {
        puts("0");
    }
    else
    {
        dfs(val["res"], true);
        cout << result.size() << endl;
        for (auto& s : result)
        {
            cout << s << endl;
        }
    }
}