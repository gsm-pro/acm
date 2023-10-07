import java.util.*;
import java.io.*;

public class Solution {
    public static void main(String[] args) throws Exception {
        int[] bl = new int[21];
        int[] gmask = new int[21];
        int[] pres = new int[21];
        int n, m;
        Scanner in = new Scanner(new File("input.txt"));
        PrintWriter out = new PrintWriter(new File("output.txt"));
        n = in.nextInt();
        m = in.nextInt();
        for (int i = n - 1; i >= 0; i--)
            bl[i] = in.nextInt();
        for (int i = 0; i < m; i++) {
            int kol = in.nextInt();
            for (int j = 0; j < kol; j++) {
                int q = in.nextInt() - 1;
                gmask[i] += (1 << q);
            }
            pres[i] = in.nextInt();
        }
        int bestmask = 0, minones = 0, maxprofit = -1;
        for (int z = (1 << n) - 1; z >= 0; z--) {
            int profit = 0, ones = 0;
            for (int i = 0; i < n; i++) {
                int bit = ((z >> i) & 1);
                ones += bit;
                if (bit == 1)
                    profit -= bl[n - i - 1];
            }
            for (int i = 0; i < m; i++)
                if ((z & gmask[i]) == gmask[i])
                    profit += pres[i];
            if (profit > maxprofit || (profit == maxprofit && ones < minones)) {
                maxprofit = profit;
                minones = ones;
                bestmask = z;
            }
        }
        if (maxprofit <= 0) {
            out.println(0);
            out.println(0);
            out.close();
            return;
        }
        out.println(maxprofit);
        out.println(minones);
        for (int i = 0; i < n; i++)
            if (((bestmask >> i) & 1) == 1)
                out.print(i + 1 + " ");
        out.close();
    }
}