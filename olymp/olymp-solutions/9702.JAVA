import java.io.*;
import java.math.*;
import java.util.*;

public class Solution {
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(new File("input.txt"));
        PrintWriter out = new PrintWriter("output.txt");
        int n = in.nextInt();
        BigInteger k = in.nextBigInteger();
        BigInteger d[][] = new BigInteger[n * 2 + 1][n + 1];
        for (int i = 0; i <= n * 2; ++i)
            Arrays.fill(d[i], BigInteger.ZERO);
        d[0][0] = BigInteger.ONE;
        for (int i = 0; i < n * 2; ++i)
            for (int j = 0; j <= n; ++j) {
                if (j + 1 <= n)
                    d[i + 1][j + 1] = d[i + 1][j + 1].add(d[i][j]);
                if (j > 0)
                    d[i + 1][j - 1] = d[i + 1][j - 1].add(d[i][j]);
            }
        String ans = new String();
        int depth = 0;
        Stack<Character> st = new Stack<Character>();
        for (int i = n * 2 - 1; i >= 0; --i) {
            BigInteger cur;
            if (depth + 1 <= n)
                cur = d[i][depth + 1].shiftLeft((i - depth - 1) / 2);
            else
                cur = BigInteger.ZERO;
            if (cur.compareTo(k) >= 0) {
                ans += '(';
                st.add('(');
                ++depth;
                continue;
            }
            k = k.subtract(cur);
            if (st.size() > 0 && st.elementAt(st.size() - 1) == '('
                    && depth - 1 >= 0)
                cur = d[i][depth - 1].shiftLeft((i - depth + 1) / 2);
            else
                cur = BigInteger.ZERO;
            if (cur.compareTo(k) >= 0) {
                ans += ')';
                st.pop();
                --depth;
                continue;
            }
            k = k.subtract(cur);
            if (depth + 1 <= n)
                cur = d[i][depth + 1].shiftLeft((i - depth - 1) / 2);
            else
                cur = BigInteger.ZERO;
            if (cur.compareTo(k) >= 0) {
                ans += '[';
                st.add('[');
                ++depth;
                continue;
            }
            k = k.subtract(cur);
            ans += ']';
            st.pop();
            --depth;
        }
        out.write(ans);
        out.close();
    }
}