import java.awt.geom.Point2D.Double;
import java.io.*;
import java.util.*;

public class Solution {
    static int N;
    static int Radius;
    static Double[] p;

    static double f(double fi) {
        double result = 0;
        Double tmp = new Double(Radius * Math.cos(fi), Radius * Math.sin(fi));
        for (int i = 0; i < N; i++) result += tmp.distance(p[i].x, p[i].y);
        return result;
    }

    static double ternary(double L, double R) {
        int iters = 100;
        while (iters-- > 0) {
            double ml = L + (R - L) / 3;
            double mr = R - (R - L) / 3;
            if (f(ml) > f(mr))
                L = ml;
            else
                R = mr;
        }
        return (L + R) / 2;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);
        N = in.nextInt();
        Radius = in.nextInt();
        p = new Double[N];
        for (int i = 0; i < N; i++) p[i] = new Double(in.nextDouble(), in.nextDouble());
        double bestAngle = 0;
        for (int i = 0; i <= 499; i++) {
            double angle = ternary(i * 2 * Math.PI / 500, (i + 1) * 2 * Math.PI / 500);
            if (f(angle) < f(bestAngle)) bestAngle = angle;
        }
        out.printf("%.9f\n", f(bestAngle));
        out.printf("%.9f %.9f", Radius * Math.cos(bestAngle), Radius * Math.sin(bestAngle));
        out.close();
    }
}