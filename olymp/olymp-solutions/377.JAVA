import java.util.*;
import java.io.*;

public class Solution {
    public static long calc(long k, long a1, long a2) {
        long s = (a2 - a1) / 2;
        if ((a1 - k) % 2 == 0 || (a2 - k) % 2 == 0)
            s++;
        return s;
    }

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("input.txt"));
        PrintWriter out = new PrintWriter(new File("output.txt"));
        int INF = 1000000000;
        long x[] = new long[1002];
        long y[] = new long[1002];
        int n = in.nextInt();
        for (int i = 0; i < n; i++) {
            x[i] = in.nextInt();
            y[i] = in.nextInt();
        }
        x[n] = x[0];
        y[n] = y[0];
        long a, b, c, d, x1, y1, x2, y2, q, B = 0, W = 0, S = 0, T;
        for (int i = 0; i < n; i++)
            S += (x[i + 1] - x[i]) * (y[i + 1] + y[i]);
        S = Math.abs(S) / 2;
        for (int i = 0; i < n; i++) {
            x1 = x[i];
            y1 = y[i];
            x2 = x[i + 1];
            y2 = y[i + 1];
            boolean fl = false;
            if (y1 == y2) {
                if (x1 > x2) {
                    q = x1;
                    x1 = x2;
                    x2 = q;
                    fl = true;
                }
                a = x1;
                b = y1;
                c = x2 - 1;
                d = y2;
                if (!fl) {
                    if (y1 % 2 != 0) {
                        B += calc(-INF - 1, a, c);
                        W += calc(-INF - 2, a, c);
                    } else {
                        B += calc(-INF - 2, a, c);
                        W += calc(-INF - 1, a, c);
                    }
                } else {
                    if (y1 % 2 == 0) {
                        B += calc(-INF - 1, a, c);
                        W += calc(-INF - 2, a, c);
                    } else {
                        B += calc(-INF - 2, a, c);
                        W += calc(-INF - 1, a, c);
                    }
                }
            }
            if (x1 == x2) {
                if (y1 > y2) {
                    q = y1;
                    y1 = y2;
                    y2 = q;
                    fl = true;
                }
                a = x1 - 1;
                b = y1;
                c = x2 - 1;
                d = y2 - 1;
                if (!fl) {
                    if (x1 % 2 == 0) {
                        B += calc(-INF - 1, b, d);
                        W += calc(-INF - 2, b, d);
                    } else {
                        B += calc(-INF - 2, b, d);
                        W += calc(-INF - 1, b, d);
                    }
                } else {
                    if (x1 % 2 != 0) {
                        B += calc(-INF - 1, b, d);
                        W += calc(-INF - 2, b, d);
                    } else {
                        B += calc(-INF - 2, b, d);
                        W += calc(-INF - 1, b, d);
                    }
                }
            }
        }
        T = (B - W) / 4;
        out.print((S + T) / 2 + " " + (S - T) / 2);
        in.close();
        out.close();
    }
}