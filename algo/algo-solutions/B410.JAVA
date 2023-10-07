import java.math.BigInteger;
import java.util.Scanner;

public class Solution {
    private static BigInteger f(int n) {
        return n < 2 ? BigInteger.ONE :
                java.util.stream.IntStream.rangeClosed(2, n)
                        .mapToObj(BigInteger::valueOf)
                        .reduce(BigInteger::multiply)
                        .get();
    }

    private static BigInteger C(int n, int k) {
        if (n - k < 0) {
            return BigInteger.ZERO;
        }
        return f(n).divide(f(k)).divide(f(n - k));
    }

    public static void main(String[] args) {
        Scanner in = new java.util.Scanner(System.in);
        int k = in.nextInt(), a = in.nextInt();
        BigInteger num = C(a, k).multiply(C(a * a - a, a - k));
        BigInteger den = C(a * a, a);
        BigInteger gcd = num.gcd(den);
        System.out.print(num.divide(gcd) + "/" + den.divide(gcd));
    }
}