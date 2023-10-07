import java.math.BigInteger;
import java.util.Scanner;

public class Solution {
    private static BigInteger[] F = new BigInteger[101];

    private static BigInteger c(int n, int k) {
        if (n - k < 0) {
            return BigInteger.ZERO;
        }
        return (F[n].divide(F[k])).divide(F[n - k]);
    }

    private static BigInteger pow(int n, int k) {
        return BigInteger.valueOf(n).pow(k);
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

    public static void main(String[] args) {
        F[0] = F[1] = BigInteger.ONE;
        for (int i = 2; i <= F.length - 1; i++)
            F[i] = F[i - 1].multiply(BigInteger.valueOf(i));
        int n = new Scanner(System.in).nextInt();
        System.out.println(mul(BigInteger.valueOf(9), c(2 * n - 1, n - 1), pow(5, n - 1), pow(5, n)));
    }
}