import java.io.*;
import java.util.*;

public class Solution {
    public static void main(String[] args) throws Exception {
        int e1[] = new int[50000];
        int e2[] = new int[50000];
        int e3[] = new int[50000];
        int e4[] = new int[50000];
        int cnt = 0;
        int n, xr1, yr1, xr2, yr2;
        int xg1[] = new int[101];
        int yg1[] = new int[101];
        int xg2[] = new int[101];
        int yg2[] = new int[101];
        int x[] = new int[2500];
        int y[] = new int[2500];
        int cx[] = new int[6000];
        int cy[] = new int[6000];
        final int Z = 3000;
        Scanner in = new Scanner(new File("input.txt"));
        PrintWriter out = new PrintWriter(new File("output.txt"));
        xr1 = in.nextInt();
        yr1 = in.nextInt();
        xr2 = in.nextInt();
        yr2 = in.nextInt();
        n = in.nextInt();
        cx[xr1 + Z] = cy[yr1 + Z] = cx[xr2 + Z] = cy[yr2 + Z] = 1;
        for (int i = 0; i < n; i++) {
            xg1[i] = in.nextInt();
            yg1[i] = in.nextInt();
            xg2[i] = in.nextInt();
            yg2[i] = in.nextInt();
            cx[xg1[i] + Z] = cy[yg1[i] + Z] = cx[xg2[i] + Z] = cy[yg2[i] + Z] = 1;
        }
        int kx = -1;
        for (int i = 0; i < 6000; i++)
            if (cx[i] == 1)
                x[++kx] = i - Z;
        kx++;
        int ky = -1;
        for (int i = 0; i < 6000; i++)
            if (cy[i] == 1)
                y[++ky] = i - Z;
        ky++;
        int ix1 = 0, ix2 = 0, iy1 = 0, iy2 = 0;
        for (int i = 0; i < kx; i++) {
            if (xr1 == x[i])
                ix1 = i;
            if (xr2 == x[i])
                ix2 = i;
        }
        for (int i = 0; i < ky; i++) {
            if (yr1 == y[i])
                iy1 = i;
            if (yr2 == y[i])
                iy2 = i;
        }
        for (int ii = ix1; ii <= ix2 - 1; ii++) {
            for (int jj = iy1; jj <= iy2 - 1; jj++) {
                int a = x[ii], b = y[jj];
                int c = x[ii + 1], d = y[jj + 1];
                boolean ok = true;
                for (int i = 0; i < n; i++)
                    if (a >= xg1[i] && c <= xg2[i] && b >= yg1[i]
                            && d <= yg2[i])
                        ok = false;
                if (ok) {
                    ++cnt;
                    e1[cnt] = a;
                    e2[cnt] = b;
                    e3[cnt] = c;
                    e4[cnt] = d;
                }
            }
        }
        out.println(cnt);
        for (int i = 1; i <= cnt; i++)
            out.println(e1[i] + " " + e2[i] + " " + e3[i] + " " + e4[i]);
        out.close();
    }
}