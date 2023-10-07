import java.math.BigInteger;

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
        int n = new java.util.Scanner(System.in).nextInt();
        System.out.print(C(2 * n, n).pow(2));
    }
}