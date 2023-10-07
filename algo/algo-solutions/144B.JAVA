import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

public class Solution {
    public static void main(String[] args) throws IOException {
        new Solution().solve();
    }

    void solve() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        List<Long> ans = new ArrayList<>();
        while (n-- > 0) ans.add(solveCase(in.readLine().split("\\s+")));
        try (BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out))) {
            out.write(ans.stream().map(Object::toString).collect(Collectors.joining("\n")));
        }
    }

    long solveCase(String[] line) {
        long X1 = Long.parseLong(line[0]), X2 = Long.parseLong(line[1]),
                Y1 = Long.parseLong(line[2]), Y2 = Long.parseLong(line[3]);
        Point p1 = Point.of(Long.parseLong(line[4]), Long.parseLong(line[5])),
                p2 = Point.of(Long.parseLong(line[6]), Long.parseLong(line[7]));
        long xx = p1.fs - p2.fs, yy = p1.sc - p2.sc;
        if (xx == 0) {
            if (X1 <= p1.fs && p2.fs <= X2) return Y2 - Y1 + 1;
            return 0;
        }
        if (yy == 0) {
            if (Y1 <= p1.sc && p2.sc <= Y2) return X2 - X1 + 1;
            return 0;
        }
        long x1 = X1, x2 = X2, y1 = Y1, y2 = Y2;
        if (xx * yy < 0) {
            x1 = Math.min(Y1, Y2);
            y1 = Math.min(-X1, -X2);
            x2 = Math.max(Y1, Y2);
            y2 = Math.max(-X1, -X2);
            p1.rotateCw();
            p2.rotateCw();
        }
        if (p1.fs > p2.fs && p1.sc > p2.sc) p1.swapWith(p2);
        long a = p1.sc - p2.sc, b = p2.fs - p1.fs, c = p1.fs * p2.sc - p2.fs * p1.sc;
        long dx = Math.abs(b), dy = Math.abs(a), gcd = gcd(dx, dy), value;
        dx /= gcd;
        dy /= gcd;
        Set<PPair> set = new HashSet<>();
        value = -a * x1 - c;
        if (isBetween(b * y1, value, b * y2)) set.add(PPair.of(Pair.of(x1, 1), Pair.normOf(value, b)));
        value = -a * x2 - c;
        if (isBetween(b * y1, value, b * y2)) set.add(PPair.of(Pair.of(x2, 1), Pair.normOf(value, b)));
        value = -b * y1 - c;
        if (isBetween(a * x1, value, a * x2)) set.add(PPair.of(Pair.normOf(value, a), Pair.of(y1, 1)));
        value = -b * y2 - c;
        if (isBetween(a * x1, value, a * x2)) set.add(PPair.of(Pair.normOf(value, a), Pair.of(y2, 1)));
        if (set.size() == 0) return 0;
        Iterator<PPair> iter = set.iterator();
        PPair t1 = iter.next();
        if (set.size() == 1) return t1.p.sc == 1 && t1.q.sc == 1 ? 1 : 0;
        PPair t2 = iter.next();
        p1.moveOutsideArea(dx, dy);
        return Math.min(
                inRange(moveUp(min(t1.p, t2.p)), moveDown(max(t1.p, t2.p)), p1.fs, dx),
                inRange(moveUp(min(t1.q, t2.q)), moveDown(max(t1.q, t2.q)), p1.sc, dy));
    }

    static boolean isBetween(long a, long z, long b) {
        return Math.min(a, b) <= z && z <= Math.max(a, b);
    }

    static long gcd(long a, long b) {
        a = Math.abs(a);
        b = Math.abs(b);
        while (b != 0) {
            a %= b;
            b ^= a;
            a ^= b;
            b ^= a;
        }
        return a;
    }

    static double div(Pair a) {
        return ((double) a.fs) / ((double) a.sc);
    }

    static long moveUp(Pair a) {
        if (a.sc == 1) return a.fs;
        return a.fs > 0 ? a.fs / a.sc + 1 : a.fs / a.sc;
    }

    static long moveDown(Pair a) {
        if (a.sc == 1) return a.fs;
        return a.fs > 0 ? a.fs / a.sc : a.fs / a.sc - 1;
    }

    static Pair min(Pair p, Pair q) {
        return div(p) < div(q) ? p : q;
    }

    static Pair max(Pair p, Pair q) {
        return div(p) > div(q) ? p : q;
    }

    static long inRange(long from, long to, long start, long step) {
        from += (-start);
        to += (-start);
        long i1 = from / step, i2 = to / step, res = i2 - i1;
        if (from % step == 0) res++;
        return res;
    }

    static class Pair {
        long fs, sc;

        Pair(long fs, long sc) {
            this.fs = fs;
            this.sc = sc;
        }

        static Pair of(long fs, long sc) {
            return new Pair(fs, sc);
        }

        static Pair normOf(long fs, long sc) {
            if (fs == 0 && sc < 0) sc = -sc;
            if (fs < 0 && sc < 0) {
                fs = -fs;
                sc = -sc;
            }
            if (fs > 0 && sc < 0) {
                fs = -fs;
                sc = -sc;
            }
            long gcd = gcd(fs, sc);
            return Pair.of(fs / gcd, sc / gcd);
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Pair pair = (Pair) o;
            return fs == pair.fs && sc == pair.sc;
        }

        @Override
        public int hashCode() {
            return Objects.hash(fs, sc);
        }
    }

    static class Point extends Pair {
        Point(long fs, long sc) {
            super(fs, sc);
        }

        static Point of(long fs, long sc) {
            return new Point(fs, sc);
        }

        void swapWith(Point o) {
            long a = fs, b = sc;
            fs = o.fs;
            sc = o.sc;
            o.fs = a;
            o.sc = b;
        }

        void rotateCw() {
            long t = fs;
            fs = sc;
            sc = -t;
        }

        void moveOutsideArea(long dx, long dy) {
            long stepX = (long) Math.ceil(Math.abs((-5000000 - fs) / dx));
            long stepY = (long) Math.ceil(Math.abs((-5000000 - sc) / dy));
            long maxStep = Math.max(stepX, stepY) + 1;
            fs = fs - dx * maxStep;
            sc = sc - dy * maxStep;
        }
    }

    static class PPair {
        Pair p, q;

        public PPair(Pair p, Pair q) {
            this.p = p;
            this.q = q;
        }

        static PPair of(Pair p, Pair q) {
            return new PPair(p, q);
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            PPair ppair = (PPair) o;
            return ppair.p.equals(p) && ppair.q.equals(q);
        }

        @Override
        public int hashCode() {
            return p.hashCode() ^ q.hashCode();
        }
    }
}