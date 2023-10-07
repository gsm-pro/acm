import java.math.BigInteger;
import java.util.*;

public class Solution {
    private static BigInteger[] F = new BigInteger[251];

    private static BigInteger C(int n, int k) {
        if (n - k < 0) {
            return BigInteger.ZERO;
        }
        return (F[n].divide(F[k])).divide(F[n - k]);
    }

    public static void main(String[] args) throws Exception {
        F[0] = BigInteger.ONE;
        F[1] = BigInteger.ONE;
        for (int i = 2; i <= 250; i++)
            F[i] = F[i - 1].multiply(BigInteger.valueOf(i));
        int c = new Scanner(System.in).nextInt();
        System.out.print(C(c, 8).multiply(F[8].divide(BigInteger.valueOf(24L))));
    }
}