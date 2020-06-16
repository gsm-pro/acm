import java.io.File;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.Scanner;

class Solution {
    private static final BigInteger INF = BigInteger.ONE.shiftLeft(666);

    public static void main(String[] args) throws Exception {
        try (PrintWriter w = new PrintWriter(new File("output.txt"))) {
            Scanner s = new Scanner(new File("input.txt"));
            BigInteger ans = new Solution().solve(s.nextLong(), s.nextLong(),
                    s.nextLong(), s.nextLong(), s.nextLong());
            w.print(ans.compareTo(BigInteger.ONE.shiftLeft(66)) > 0 ? -1 : ans);
        }
    }

    class GCDExtResult {
        long x, y, g;

        GCDExtResult(long x, long y, long g) {
            this.x = x;
            this.y = y;
            this.g = g;
        }
    }

    class FindAnySolutionResult {
        boolean result;
        GCDExtResult gcdER;

        FindAnySolutionResult(boolean result, GCDExtResult gcdER) {
            this.result = result;
            this.gcdER = gcdER;
        }
    }

    class XY {
        BigInteger x, y;

        XY(long x, long y) {
            this.x = BigInteger.valueOf(x);
            this.y = BigInteger.valueOf(y);
        }
    }

    class XYRange {
        BigInteger minX, maxX, minY, maxY;

        XYRange(BigInteger minX, BigInteger maxX, BigInteger minY, BigInteger maxY) {
            this.minX = minX;
            this.maxX = maxX;
            this.minY = minY;
            this.maxY = maxY;
        }
    }

    private GCDExtResult gcdExt(long a, long b) {
        if (a == 0) {
            return new GCDExtResult(0L, 1L, b);
        }
        GCDExtResult d = gcdExt(b % a, a);
        return new GCDExtResult(d.y - (b / a) * d.x, d.x, d.g);
    }

    private FindAnySolutionResult findAnySolution(long a, long b, long c) {
        GCDExtResult d = gcdExt(Math.abs(a), Math.abs(b));
        if (c % d.g != 0) {
            return new FindAnySolutionResult(false, null);
        }
        long x = d.x * c / d.g;
        long y = d.y * c / d.g;
        if (a < 0) {
            x *= -1;
        }
        if (b < 0) {
            y *= -1;
        }
        return new FindAnySolutionResult(true, new GCDExtResult(x, y, d.g));
    }

    private void shiftSolution(XY z, long a, long b, BigInteger cnt) {
        z.x = z.x.add(toBI(b).multiply(cnt));
        z.y = z.y.subtract(toBI(a).multiply(cnt));
    }

    private boolean sgn(long x) {
        return x > 0;
    }

    private BigInteger zeroOrINF(boolean b) {
        return b ? INF : BigInteger.ZERO;
    }

    private BigInteger toBI(long b) {
        return BigInteger.valueOf(b);
    }

    private BigInteger findAllSolutionsCount(long a, long b, long c, XYRange xyr) {
        FindAnySolutionResult fasResult = findAnySolution(a, b, c);
        if (!fasResult.result) {
            return BigInteger.ZERO;
        }
        GCDExtResult gcd = fasResult.gcdER;
        a /= gcd.g;
        b /= gcd.g;
        BigInteger signA = (a > 0) ? BigInteger.ONE : BigInteger.ONE.negate();
        BigInteger signB = (b > 0) ? BigInteger.ONE : BigInteger.ONE.negate();
        XY xy = new XY(gcd.x, gcd.y);
        shiftSolution(xy, a, b, xyr.minX.subtract(xy.x).divide(toBI(b)));
        if (xy.x.compareTo(xyr.minX) < 0) {
            shiftSolution(xy, a, b, signB);
        }
        if (xy.x.compareTo(xyr.maxX) > 0) {
            return BigInteger.ZERO;
        }
        BigInteger lx1 = xy.x;
        shiftSolution(xy, a, b, xyr.maxX.subtract(xy.x).divide(toBI(b)));
        if (xy.x.compareTo(xyr.maxX) > 0) {
            shiftSolution(xy, a, b, signB.negate());
        }
        BigInteger rx1 = xy.x;
        shiftSolution(xy, a, b, xyr.minY.subtract(xy.y).divide(toBI(a)).negate());
        if (xy.y.compareTo(xyr.minY) < 0) {
            shiftSolution(xy, a, b, signA.negate());
        }
        if (xy.y.compareTo(xyr.maxY) > 0) {
            return BigInteger.ZERO;
        }
        BigInteger lx2 = xy.x;
        shiftSolution(xy, a, b, xyr.maxY.subtract(xy.y).divide(toBI(a)).negate());
        if (xy.y.compareTo(xyr.maxY) > 0) {
            shiftSolution(xy, a, b, signA);
        }
        BigInteger rx2 = xy.x;
        if (lx2.compareTo(rx2) > 0) {
            BigInteger t = lx2;
            lx2 = rx2;
            rx2 = t;
        }
        BigInteger lx = lx1.max(lx2);
        BigInteger rx = rx1.min(rx2);
        return BigInteger.ZERO.max(rx.subtract(lx).divide(toBI(Math.abs(b))).add(BigInteger.ONE));
    }

    private BigInteger solve(long X, long A, @SuppressWarnings("unused") long B, long C, long Y) {
        long diff = Y - X;
        if (A == 0 && C == 0) {
            if (diff == 0) {
                return INF;
            }
            return BigInteger.ZERO;
        }
        if (A == 0) {
            if (diff == 0) {
                return INF;
            }
            return sgn(C) ^ sgn(diff) ? BigInteger.ZERO : zeroOrINF(Math.abs(diff) % Math.abs(C) == 0);
        }
        if (C == 0) {
            if (diff == 0) {
                return INF;
            }
            return sgn(A) ^ sgn(diff) ? BigInteger.ZERO : zeroOrINF(Math.abs(diff) % Math.abs(A) == 0);
        }
        return findAllSolutionsCount(A, C, diff, new XYRange(BigInteger.ZERO, INF, BigInteger.ZERO, INF));
    }
}