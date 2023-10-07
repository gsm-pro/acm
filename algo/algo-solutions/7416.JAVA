import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.math.BigDecimal;
import java.math.MathContext;
import java.text.NumberFormat;
import java.util.LinkedList;
import java.util.Locale;
import java.util.Queue;

import static java.lang.Math.*;

public class Solution {
    public static void main(String[] args) throws Exception {
        new Solution().run();
    }

    private static final BigDecimal EPS = BigDecimal.ONE.divide(BigDecimal.TEN.pow(8), MathContext.DECIMAL64);
    private static final double THRESHOLD = 0.1;
    private static final double HUNDRED = 100.0;
    private static final Locale US = Locale.US;

    private void run() throws Exception {
        final NumberFormat nf = NumberFormat.getInstance(US);
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out));
        String tmp;
        Queue<Double> data = new LinkedList<>();
        while ((tmp = in.readLine()) != null) {
            String[] t = tmp.split(" ");
            for (String a : t) {
                if (!a.isEmpty()) {
                    Number number = nf.parse(a);
                    data.add(number.doubleValue());
                }
            }
        }
        in.close();
        int N = data.size();
        for (int i = 0; i < N; i += 7) {
            double x = data.poll(), y = data.poll(), r = data.poll();
            double x1 = data.poll(), y1 = data.poll(), x2 = data.poll(), y2 = data.poll();
            x1 -= x;
            x2 -= x;
            y1 -= y;
            y2 -= y;
            if (x1 == x2 && y1 == y2) {
                if (x1 == 0 && y1 == 0 && r > 0) {
                    out.write("0\n\n");
                    continue;
                }
                if ((x1 == 0 && y1 == 0 && r == 0) || abs(x1 * x1 + y1 * y1 - r * r) == 0) {
                    out.write(String.format(US, "1\n%.12f %.12f\n\n", x1 + x, y1 + y));
                    continue;
                }
                out.write("0\n\n");
                continue;
            }
            if (max(x1, x2) < -r || min(x1, x2) > r || max(y1, y2) < -r || min(y1, y2) > r) {
                out.write("0\n\n");
                continue;
            }
            double power = 1.0;
            if (r > 0) {
                while (r < THRESHOLD) {
                    r *= HUNDRED;
                    x1 *= HUNDRED;
                    y1 *= HUNDRED;
                    x2 *= HUNDRED;
                    y2 *= HUNDRED;
                    power *= HUNDRED;
                }
            }
            double a = y1 - y2, b = x2 - x1;
            if (a != 0 && b != 0) {
                while (abs(a) < THRESHOLD || abs(b) < THRESHOLD) {
                    a *= HUNDRED;
                    b *= HUNDRED;
                }
            }
            double c = -a * x1 - b * y1;
            BigDecimal CsQ = BigDecimal.valueOf(c * c);
            BigDecimal AsQPlusBsQ = BigDecimal.valueOf(a).pow(2).add(BigDecimal.valueOf(b).pow(2));
            BigDecimal abr = AsQPlusBsQ.multiply(BigDecimal.valueOf(r * r));
            int cmp = CsQ.compareTo(abr);
            if (cmp > 0) {
                out.write("0\n\n");
                continue;
            }
            BigDecimal x0 = BigDecimal.valueOf(-a * c).divide(AsQPlusBsQ, MathContext.DECIMAL64);
            BigDecimal y0 = BigDecimal.valueOf(-b * c).divide(AsQPlusBsQ, MathContext.DECIMAL64);
            BigDecimal minX1X2 = BigDecimal.valueOf(min(x1, x2)).subtract(EPS);
            BigDecimal maxX1X2 = BigDecimal.valueOf(max(x1, x2)).add(EPS);
            BigDecimal minY1Y2 = BigDecimal.valueOf(min(y1, y2)).subtract(EPS);
            BigDecimal maxY1Y2 = BigDecimal.valueOf(max(y1, y2)).add(EPS);
            if (cmp == 0) {
                if (x0.compareTo(minX1X2) >= 0 && x0.compareTo(maxX1X2) <= 0 &&
                        y0.compareTo(minY1Y2) >= 0 && y0.compareTo(maxY1Y2) <= 0) {
                    out.write(String.format(US, "1\n%.12f %.12f\n\n", x0.doubleValue() / power + x, y0.doubleValue() / power + y));
                    continue;
                }
                out.write("0\n\n");
                continue;
            }
            double d = -(c / (a * a + b * b)) * c + r * r;
            double m = sqrt(d / (a * a + b * b));
            BigDecimal Ax = x0.add(BigDecimal.valueOf(b * m));
            BigDecimal Ay = y0.subtract(BigDecimal.valueOf(a * m));
            BigDecimal Bx = x0.subtract(BigDecimal.valueOf(b * m));
            BigDecimal By = y0.add(BigDecimal.valueOf(a * m));
            if (Ax.compareTo(Bx) > 0 || (Ax.compareTo(Bx) == 0 && Ay.compareTo(By) > 0)) {
                BigDecimal s = Ax;
                Ax = Bx;
                Bx = s;
                s = Ay;
                Ay = By;
                By = s;
            }
            double[] ptsX = new double[2];
            double[] ptsY = new double[2];
            int cnt = 0;
            if (Ax.compareTo(minX1X2) >= 0 && Ax.compareTo(maxX1X2) <= 0 &&
                    Ay.compareTo(minY1Y2) >= 0 && Ay.compareTo(maxY1Y2) <= 0) {
                ptsX[cnt] = Ax.doubleValue() / power + x;
                ptsY[cnt] = Ay.doubleValue() / power + y;
                cnt++;
            }
            if (Bx.compareTo(minX1X2) >= 0 && Bx.compareTo(maxX1X2) <= 0 &&
                    By.compareTo(minY1Y2) >= 0 && By.compareTo(maxY1Y2) <= 0) {
                ptsX[cnt] = Bx.doubleValue() / power + x;
                ptsY[cnt] = By.doubleValue() / power + y;
                cnt++;
            }
            if (cnt == 0) {
                out.write("0\n\n");
                continue;
            }
            out.write(cnt + "\n");
            if (cnt >= 1) {
                out.write(String.format(US, "%.12f %.12f\n", ptsX[0], ptsY[0]));
                if (cnt == 1) {
                    out.write("\n");
                    continue;
                }
            }
            if (cnt == 2) {
                out.write(String.format(US, "%.12f %.12f\n\n", ptsX[1], ptsY[1]));
            }
        }
        out.close();
    }
}