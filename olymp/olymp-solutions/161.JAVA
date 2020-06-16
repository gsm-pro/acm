import java.io.*;
import java.util.*;
import java.math.*;

class Solution {
    public static BigInteger C(int n, int k) {
        BigInteger res = BigInteger.ONE;
        for (int i = 1; i <= k; i++)
            res = res.multiply(BigInteger.valueOf(n - k + i)).divide(
                    BigInteger.valueOf(i));
        return res;
    }

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("input.txt"));
        PrintWriter out = new PrintWriter(new File("output.txt"));
        int p = in.nextInt(), q = in.nextInt(), k = in.nextInt();
        out.println((C(p, k).multiply(C(q, k))).toString());
        out.close();
    }
}