#include<bits/stdc++.h>
using namespace std;
int n, i, c, a[22], k[22], minOnes = 9999, bestMask = -1;

int main()
{
    cin >> n >> c;
    for (i = 0; i < n; i++)
    {
        cin >> a[i];
        k[i] = __builtin_popcount(a[i]);
    }
    int m = 1 << n;
    while (m--)
    {
        int res = 0, ones = 0;
        for (i = 0; i < n; i++)
            if ((m >> i) & 1)
                res ^= a[i], ones += k[i];
        if (res == c && ones < minOnes)
            bestMask = m, minOnes = ones;
    }
    if (bestMask == -1)
        return cout << -1, 0;
    for (i = 0; i < n; i++)
        if ((bestMask >> i) & 1)
            cout << a[i] << " ";
}