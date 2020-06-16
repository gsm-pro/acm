import java.io.*;
import java.util.*;

public class Solution {
    private static int n;
    private static int[][] g;
    private static int[] matching;
    private static int[] matchingInv;
    private static int num;
    private static int visitTop;
    private static int[] visitNum;
    private static int[] visitStack;
    private static int[] mark;
    private static int[] componentNum;
    private static int componentCnt;
    private static boolean[] inStack;

    private static void read() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
        n = Integer.parseInt(in.readLine().trim());
        g = new int[n][];
        for (int i = 0; i < n; i++) {
            StringTokenizer st = new StringTokenizer(in.readLine());
            int k = Integer.parseInt(st.nextToken());
            g[i] = new int[k];
            for (int j = 0; j < k; j++) {
                g[i][j] = Integer.parseInt(st.nextToken()) - 1;
            }
        }
        matching = new int[n];
        matchingInv = new int[n];
        componentNum = new int[n];
        StringTokenizer st = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++) {
            matching[i] = Integer.parseInt(st.nextToken()) - 1;
            matchingInv[matching[i]] = i;
        }
        in.close();
    }

    private static void go(int i) {
        visitNum[i] = ++num;
        visitStack[visitTop++] = i;
        inStack[i] = true;
        int j = matchingInv[i];
        mark[i] = num;
        for (int k = 0; k < g[j].length; k++) {
            int other = g[j][k];
            if (other != i) {
                if (visitNum[other] == 0) {
                    go(other);
                    mark[i] = Math.min(mark[i], mark[other]);
                } else if (visitNum[other] < visitNum[i] && inStack[other]) {
                    mark[i] = Math.min(mark[i], visitNum[other]);
                }
            }
        }
        if (mark[i] == visitNum[i]) {
            componentCnt++;
            int x;
            do {
                x = visitStack[--visitTop];
                componentNum[x] = componentCnt;
                inStack[x] = false;
            } while (x != i);
        }
    }

    private static void solve() {
        visitNum = new int[n];
        visitStack = new int[n];
        mark = new int[n];
        componentNum = new int[n];
        inStack = new boolean[n];
        for (int i = 0; i < n; i++) {
            if (visitNum[i] == 0) {
                go(i);
            }
        }
    }

    private static void write() throws IOException {
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("output.txt")));
        int[] list = new int[n];
        for (int i = 0; i < n; i++) {
            int cnt = 0;
            for (int j = 0; j < g[i].length; j++) {
                int one = matching[i];
                int other = g[i][j];
                if (componentNum[one] == componentNum[other]) {
                    list[cnt++] = other;
                }
            }
            out.write("" + cnt);
            Arrays.sort(list, 0, cnt);
            for (int k = 0; k < cnt; k++) {
                out.write(" " + (list[k] + 1));
            }
            out.newLine();
        }
        out.close();
    }

    public static void main(String[] args) throws Exception {
        read();
        solve();
        write();
    }
}