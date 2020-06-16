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

    private static BigInteger bi(int n) {
        return BigInteger.valueOf(n);
    }

    public static void main(String[] args) {
        F[0] = F[1] = BigInteger.ONE;
        for (int i = 2; i <= F.length - 1; i++) {
            F[i] = F[i - 1].multiply(BigInteger.valueOf(i));
        }
        int n = new Scanner(System.in).nextInt();
        BigInteger result;
        switch (n) {
            case 1:
                result = mul(bi(9), c(1, 0), pow(5, 0), pow(5, 1));
                break;
            case 2:
                result = mul(bi(9), c(3, 1), pow(5, 1), pow(5, 2));
                break;
            case 3:
                result = mul(bi(9), c(5, 2), pow(5, 2), pow(5, 3));
                break;
            case 4:
                result = mul(bi(9), c(7, 3), pow(5, 3), pow(5, 4));
                break;
            case 5:
                result = mul(bi(9), c(9, 4), pow(5, 4), pow(5, 5));
                break;
            case 6:
                result = mul(bi(9), c(11, 5), pow(5, 5), pow(5, 6));
                break;
            case 7:
                result = mul(bi(9), c(13, 6), pow(5, 6), pow(5, 7));
                break;
            case 8:
                result = mul(bi(9), c(15, 7), pow(5, 7), pow(5, 8));
                break;
            case 9:
                result = mul(bi(9), c(17, 8), pow(5, 8), pow(5, 9));
                break;
            default:
                result = mul(bi(9), c(2 * n - 1, n - 1), pow(5, n - 1), pow(5, n));
                break;
        }
        System.out.println(result);
    }
}