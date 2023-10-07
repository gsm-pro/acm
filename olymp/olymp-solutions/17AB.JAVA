import java.util.*;
import java.io.*;
import java.math.*;

public class Solution {
    public static void main(String[] args) throws Exception {
        Scanner s = new Scanner(new File("input.txt"));
        PrintWriter writer = new PrintWriter("output.txt");
        int q = 0, position, chislo;
        int b[] = new int[50000];
        int ch[] = new int[500];
        int n = s.nextInt();
        for (int i = 1; i <= n; i++) {
            int a = s.nextInt();
            ch[a]++;
        }
        while (ch[0] != n) {
            position = 0;
            chislo = 0;
            for (int i = 1; i <= 300; i++)
                if ((ch[i] > chislo) && (ch[i] != 0)) {
                    position = i;
                    chislo = ch[i];
                }
            q++;
            b[q] = position;
            ch[position - 1] += chislo;
            ch[position] -= chislo;
        }
        writer.println(q);
        for (int i = 1; i <= q; i++) writer.print(b[i] + " ");
        writer.close();
    }
}