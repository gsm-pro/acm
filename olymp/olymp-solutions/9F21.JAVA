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
        if (k.compareTo(d[n * 2][0]) > 0)
            ans = "No solution for this testcase.";
        else {
            int depth = 0;
            for (int i = n * 2 - 1; i >= 0; --i)
                if (depth + 1 <= n && d[i][depth + 1].compareTo(k) >= 0) {
                    ans += '(';
                    ++depth;
                } else {
                    ans += ')';
                    if (depth + 1 <= n)
                        k = k.subtract(d[i][depth + 1]);
                    --depth;
                }
        }
        out.write(ans);
        out.close();
    }
}