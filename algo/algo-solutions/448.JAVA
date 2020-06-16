import java.math.BigInteger;
import java.util.Scanner;

public class Solution {
    private static BigInteger[] F = new BigInteger[99];

    private static BigInteger C(int n, int k) {
        if (n - k < 0) {
            return BigInteger.ZERO;
        }
        return (F[n].divide(F[k])).divide(F[n - k]);
    }

    private static BigInteger mul(BigInteger... v) {
        if (v == null || v.length == 0) {
            return BigInteger.ZERO;
        }
        BigInteger m = BigInteger.ONE;
        for (BigInteger b : v) {
            m = m.multiply(b);
        }
        return m;
    }

    private static BigInteger add(BigInteger... v) {
        if (v == null || v.length == 0) {
            return BigInteger.ZERO;
        }
        BigInteger m = BigInteger.ZERO;
        for (BigInteger b : v) {
            m = m.add(b);
        }
        return m;
    }

    public static void main(String[] args) {
        F[0] = F[1] = BigInteger.ONE;
        for (int i = 2; i <= F.length - 1; i++) {
            F[i] = F[i - 1].multiply(BigInteger.valueOf(i));
        }
        Scanner in = new Scanner(System.in);
        int k = in.nextInt(), a = in.nextInt(), b = in.nextInt(), c = in.nextInt();
        BigInteger result = BigInteger.ZERO;
        for (int left = 0; left <= Math.min(a, k); left++) {
            for (int right = 0; right <= Math.min(b, k); right++) {
                result = add(result, mul(C(a, left), C(b, right), C(c, 2 * k - left - right)));
            }
        }
        System.out.println(result);
    }
}