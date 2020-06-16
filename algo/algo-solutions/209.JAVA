import java.util.Scanner;

public class Solution {
    private static final int N = 100;
    private static final double EPS = 1e-8;

    public static void main(String[] args) throws Exception {
        new Solution().solve();
    }

    private double det(double x11, double x12, double x21, double x22) {
        return x11 * x22 - x12 * x21;
    }

    private double vec(double x11, double x12, double x21, double x22) {
        return x11 * x21 + x12 * x22;
    }

    private boolean isBetween(double z0, double z1, double z2) {
        return z1 < z2 ? z0 > z1 - EPS && z0 < z2 + EPS :
                z0 > z2 - EPS && z0 < z1 + EPS;
    }

    private boolean isOnEdge(double x0, double y0, double x1, double y1, double x2, double y2) {
        return Math.abs(det(x0 - x1, y0 - y1, x2 - x1, y2 - y1)) < EPS &&
                isBetween(x0, x1, x2) && isBetween(y0, y1, y2);
    }

    private double angle(double xc, double yc, double xp, double yp, double xq, double yq) {
        double sin = det(xp - xc, yp - yc, xq - xc, yq - yc);
        double cos = vec(xp - xc, yp - yc, xq - xc, yq - yc);
        if (Math.abs(sin) < EPS && cos > -EPS) {
            return Double.POSITIVE_INFINITY;
        }
        double a = Math.atan2(sin, cos);
        return a < 0 ? 2 * Math.PI + a : a;
    }

    private int findMostRight(int n, int[] x, int[] y, double xc, double yc, double xp, double yp) {
        int result = -1;
        double best = Double.POSITIVE_INFINITY;
        for (int i = 0; i < n; i++)
            if (isOnEdge(xc, yc, x[i], y[i], x[(i + 1) % n], y[(i + 1) % n])) {
                double a = angle(xc, yc, xp, yp, x[i], y[i]);
                if (a < best) {
                    best = a;
                    result = i;
                }
                a = angle(xc, yc, xp, yp, x[(i + 1) % n], y[(i + 1) % n]);
                if (a < best) {
                    best = a;
                    result = (i + 1) % n;
                }
            }
        if (result < 0) {
            throw new RuntimeException();
        }
        return result;
    }

    private double[] realloc(double[] a) {
        double[] a_new = new double[a.length * 2];
        System.arraycopy(a, 0, a_new, 0, a.length);
        return a_new;
    }

    private void solve() {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        if (n < 3 || n > N) {
            throw new RuntimeException();
        }
        int[] x = new int[n];
        int[] y = new int[n];
        for (int i = 0; i < n; i++) {
            x[i] = in.nextInt();
            y[i] = in.nextInt();
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (x[i] == x[j] && y[i] == y[j]) {
                    throw new RuntimeException();
                }
            }
        }
        double[] answer_x = new double[n];
        double[] answer_y = new double[n];
        answer_x[0] = x[0];
        answer_y[0] = y[0];
        for (int i = 1; i < n; i++) {
            if (x[i] < answer_x[0] || x[i] == answer_x[0] && y[i] < answer_y[0]) {
                answer_x[0] = x[i];
                answer_y[0] = y[i];
            }
        }
        double xp = answer_x[0] - 1;
        double yp = answer_y[0];
        int m = 0;
        while (true) {
            double xc = answer_x[m];
            double yc = answer_y[m];
            int i = findMostRight(n, x, y, xc, yc, xp, yp);
            double xq = x[i];
            double yq = y[i];
            for (int j = 0; j < n; j++) {
                double x1 = x[j];
                double y1 = y[j];
                double x2 = x[(j + 1) % n];
                double y2 = y[(j + 1) % n];
                double M = det(xq - xc, x1 - x2, yq - yc, y1 - y2);
                if (Math.abs(M) < EPS) {
                    continue;
                }
                double tcp = det(x1 - xc, x1 - x2, y1 - yc, y1 - y2) / M;
                double t12 = det(xq - xc, x1 - xc, yq - yc, y1 - yc) / M;
                if (tcp < EPS || tcp > 1 - EPS || t12 < EPS || t12 > 1 - EPS) {
                    continue;
                }
                xq = x1 + t12 * (x2 - x1);
                yq = y1 + t12 * (y2 - y1);
            }
            m++;
            if (Math.abs(answer_x[0] - xq) < EPS && Math.abs(answer_y[0] - yq) < EPS) {
                break;
            }
            if (m >= answer_x.length) {
                answer_x = realloc(answer_x);
                answer_y = realloc(answer_y);
            }
            answer_x[m] = xq;
            answer_y[m] = yq;
            xp = xc;
            yp = yc;
        }
        System.out.println(m);
        for (int i = 0; i < m; i++) {
            String line = String.format("%.6f %.6f", answer_x[i], answer_y[i]);
            System.out.println(line.replaceAll(",", "."));
        }
    }
}