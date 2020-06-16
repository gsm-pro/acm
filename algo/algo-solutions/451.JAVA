import java.math.*;
import java.util.*;

public class Solution {
    private static final BigInteger[] F = new BigInteger[50];

    class DivisionGenerator {
        private int number, groupsCount, curSum;
        private List<List<Integer>> div = new ArrayList<>();
        private List<Integer> cntInGroups = new ArrayList<>();

        private void rec(int remaining, int previous) {
            if (curSum > number) {
                return;
            }
            if (curSum == number) {
                if (cntInGroups.size() == groupsCount) {
                    div.add(new ArrayList<>(cntInGroups));
                }
                return;
            }
            for (int next = previous; next >= 1; next--) {
                cntInGroups.add(next);
                curSum += next;
                rec(remaining - next, next);
                curSum -= next;
                cntInGroups.remove(cntInGroups.size() - 1);
            }
        }

        List<List<Integer>> generate(int N, int K) {
            div.clear();
            number = N;
            groupsCount = K;
            curSum = 0;
            rec(number, number);
            return div;
        }
    }

    public static void main(String[] args) {
        new Solution().run();
    }

    private BigInteger C(int n, int k) {
        if (n - k < 0) {
            return BigInteger.ZERO;
        }
        return F[n].divide(F[k]).divide(F[n - k]);
    }

    private BigInteger getCombCount(List<Integer> div) {
        Map<Integer, Integer> cnts = new HashMap<>();
        for (Integer d : div) {
            if (!cnts.containsKey(d)) {
                cnts.put(d, 0);
            }
            cnts.put(d, cnts.get(d) + 1);
        }
        BigInteger res = F[div.size()];
        for (Integer d : cnts.values()) {
            res = res.divide(F[d]);
        }
        return res;
    }

    private void run() {
        F[0] = F[1] = BigInteger.ONE;
        for (int i = 2; i <= F.length - 1; i++) {
            F[i] = F[i - 1].multiply(BigInteger.valueOf(i));
        }
        Scanner in = new Scanner(System.in);
        int n = in.nextInt(), m = in.nextInt(), k = in.nextInt();
        List<List<Integer>> divs = new DivisionGenerator().generate(n + k, n);
        BigInteger X, Y, x, y;
        X = Y = BigInteger.ZERO;
        for (List<Integer> div : divs) {
            x = y = getCombCount(div);
            int M = m;
            for (Integer d : div) {
                x = x.multiply(C(m, d));
                y = y.multiply(C(M, d));
                M -= d;
            }
            X = X.add(x);
            Y = Y.add(y);
        }
        System.out.print(X + "\n" + Y);
    }
}