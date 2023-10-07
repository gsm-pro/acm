import java.math.BigInteger;
import java.util.Scanner;

public class Solution {
    class Pair {
        long x, y;
    }

    int extendedGcd(int a, int b, Pair res) {
        if (b == 0) {
            res.x = 1;
            res.y = 0;
            return a;
        } else {
            int result = extendedGcd(b, a % b, res);
            long t = res.x;
            res.x = res.y;
            res.y = t - res.y * (a / b);
            return result;
        }
    }

    BigInteger garner(int n, int[] m, int[] r) {
        long[] c = new long[n];
        Pair pair = new Pair();
        for (int i = 1; i < n; i++) {
            c[i] = 1;
            for (int j = 0; j < i; j++) {
                extendedGcd(m[j], m[i], pair);
                c[i] = (c[i] * pair.x) % m[i];
                c[i] = (c[i] + m[i]) % m[i];
            }
        }
        BigInteger p = BigInteger.ONE;
        BigInteger ans = BigInteger.valueOf(r[0]);
        for (int i = 1; i < n; i++) {
            p = p.multiply(BigInteger.valueOf(m[i - 1]));
            BigInteger t = BigInteger.valueOf(r[i]).subtract(ans);
            BigInteger u = t.multiply(BigInteger.valueOf(c[i])).mod(BigInteger.valueOf(m[i]));
            ans = ans.add(u.multiply(p));
        }
        return ans;
    }

    void solve() {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int[] m = new int[n];
        long c = 1L;
        for (int i = 0; i < n; i++) {
            m[i] = in.nextInt();
            c *= m[i];
        }
        int r[] = new int[n];
        for (int i = 0; i < n; i++) r[i] = in.nextInt();
        long k = in.nextLong();
        long day = garner(n, m, r).longValue();
        if (day > k) {
            System.out.print(day);
        } else {
            long nth = (k - day) / c;
            while (day + (nth - 1) * c <= k) nth++;
            System.out.print(day + (nth - 1) * c);
        }
    }

    public static void main(String[] args) {
        Solution s = new Solution();
        s.solve();
    }
}