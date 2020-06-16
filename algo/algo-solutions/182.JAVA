import java.util.*;

public class Solution {
    private final static int INF = 1000 * 1000 * 1000;

    private class To_Cost_Id {
        int v, c, id;

        To_Cost_Id(int v, int c, int id) {
            this.v = v;
            this.c = c;
            this.id = id;
        }
    }

    private class GraphRib {
        int a, b, c;

        GraphRib(int a, int b, int c) {
            this.a = a;
            this.b = b;
            this.c = c;
        }
    }

    private void inverseMST() {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int m = in.nextInt();
        List<List<To_Cost_Id>> g = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            g.add(new ArrayList<>());
        }
        GraphRib[] ribs = new GraphRib[m];
        for (int i = 0; i < m; i++) {
            int x = in.nextInt();
            int y = in.nextInt();
            int c = in.nextInt();
            --x;
            --y;
            ribs[i] = new GraphRib(x, y, c);
            g.get(x).add(new To_Cost_Id(y, c, i));
            g.get(y).add(new To_Cost_Id(x, c, i));
        }
        int nn = m + 2, s = nn - 2, tt = nn - 1;
        int[][] f = new int[nn][nn];
        int[][] u = new int[nn][nn];
        int[][] c = new int[nn][nn];
        for (int i = n - 1; i < m; ++i) {
            int[] q = new int[n];
            int h = 0, t = 0;
            GraphRib cur = ribs[i];
            q[t++] = cur.a;
            int[] rib_id = new int[n];
            Arrays.fill(rib_id, -1);
            rib_id[cur.a] = -2;
            while (h < t) {
                int v = q[h++];
                for (int j = 0; j < g.get(v).size(); j++) {
                    if (g.get(v).get(j).id >= n - 1) {
                        break;
                    } else {
                        if (rib_id[g.get(v).get(j).v] == -1) {
                            rib_id[g.get(v).get(j).v] = g.get(v).get(j).id;
                            q[t++] = g.get(v).get(j).v;
                        }
                    }
                }
            }
            for (int v = cur.b, pv; v != cur.a; v = pv) {
                int r = rib_id[v];
                pv = (v != ribs[r].a) ? ribs[r].a : ribs[r].b;
                u[r][i] = n;
                c[r][i] = ribs[i].c - ribs[r].c;
                c[i][r] = -c[r][i];
            }
        }
        u[s][tt] = n + 1;
        for (int i = 0; i < n - 1; ++i) {
            u[s][i] = 1;
        }
        for (int i = n - 1; i < m; ++i) {
            u[i][tt] = 1;
        }
        int[] pi = new int[nn];
        pi[s] = INF;
        for (int i = 0; i < n - 1; ++i) {
            pi[i] = INF;
            for (int j = n - 1; j < m; ++j) {
                if (u[i][j] != 0) {
                    pi[i] = Math.min(pi[i], ribs[j].c - ribs[i].c);
                }
            }
            pi[s] = Math.min(pi[s], pi[i]);
        }
        for (;;) {
            int[] d = new int[nn];
            Arrays.fill(d, INF);
            d[s] = 0;
            int[] p = new int[nn];
            Arrays.fill(p, -1);
            boolean[] used = new boolean[nn];
            for (int i = 0; i < nn; i++) {
                int v = -1;
                for (int j = 0; j < nn; j++) {
                    if (!used[j] && (v == -1 || d[j] < d[v])) {
                        v = j;
                    }
                }
                if (d[v] == INF) {
                    break;
                }
                used[v] = true;
                for (int j = 0; j < nn; j++) {
                    if (f[v][j] < u[v][j]) {
                        int new_d = d[v] + c[v][j] - pi[v] + pi[j];
                        if (new_d < d[j]) {
                            d[j] = new_d;
                            p[j] = v;
                        }

                    }
                }
            }
            for (int i = 0; i < nn; ++i) {
                pi[i] -= d[i];
            }
            for (int v = tt; v != s; v = p[v]) {
                int pv = p[v];
                f[pv][v]++;
                f[v][pv]--;
            }
            if (p[tt] == s) {
                break;
            }
        }
        for (int i = 0; i < m; ++i) {
            pi[i] -= pi[s];
        }
        for (int i = 0; i < n - 1; ++i) {
            if (f[s][i] != 0) {
                ribs[i].c += pi[i];
            }
        }
        for (int i = n - 1; i < m; ++i) {
            if (f[i][tt] != 0) {
                ribs[i].c += pi[i];
            }
        }
        System.out.println(n + " " + m);
        for (int i = 0; i < m; i++) {
            System.out.println((ribs[i].a + 1) + " " + (ribs[i].b + 1) + " " + ribs[i].c);
        }
    }

    public static void main(String[] args) {
        new Solution().inverseMST();
    }
}