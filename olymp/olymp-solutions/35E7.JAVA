import java.io.*;
import java.math.*;
import java.util.*;

public class Solution {
    public static void main(String[] args) throws Exception {
        BigInteger[] F = new BigInteger[30];
        F[0] = BigInteger.ONE;
        for (int i = 1; i < 30; i++) F[i] = F[i - 1].multiply(BigInteger.valueOf(i));
        Scanner in = new Scanner(new File("input.txt"));
        try (PrintWriter out = new PrintWriter("output.txt")) {
            int n = in.nextInt();
            BigInteger k = in.nextBigInteger();
            int left = in.nextInt(), right = in.nextInt();
            if (k.compareTo(F[n]) >= 0 || right > ((1 << n) - 1)) return;
            Integer[] P = new Integer[n];
            for (int i = 0; i < n; i++) {
                P[i] = k.divide(F[n - i - 1]).intValue();
                k = k.remainder(F[n - i - 1]);
            }
            for (int i = n - 2; i >= 0; i--)
                for (int j = i + 1; j < n; j++)
                    if (P[j] >= P[i]) P[j]++;
            for (int i = left; i < right; i++)
                out.print((char) (P[Integer.toString((i + 1) ^ i, 2).length() - 1] + 65));
        }
    }
}