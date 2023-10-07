import java.awt.*;
import java.io.*;
import java.util.List;
import java.util.*;

class Solution {
    public static void main(String[] args) throws Exception {
        new Solution().solve();
    }

    private static final int INF = 22222;
    private static final int SIZE = 22;
    private static final int SIZE_SQ = SIZE * SIZE;
    private boolean[][] field = new boolean[SIZE][SIZE];
    private int[][] floyd = new int[SIZE_SQ][SIZE_SQ];
    private int[][] next = new int[SIZE_SQ][SIZE_SQ];
    private Random rnd = new Random(System.currentTimeMillis());
    private int N;

    private void solve() throws Exception {
        for (int i = 0; i < SIZE_SQ; i++) {
            for (int j = 0; j < SIZE_SQ; j++) {
                floyd[i][j] = INF;
                next[i][j] = j;
            }
        }
        BufferedReader in = new BufferedReader(new InputStreamReader(
                new FileInputStream("input.txt")));
        N = Integer.parseInt(in.readLine());
        for (int i = 1; i <= N; i++) {
            char[] line = in.readLine().toCharArray();
            for (int j = 1; j <= N; j++) {
                field[i][j] = (line[j - 1] == '.');
            }
        }
        in.close();
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (field[i][j]) {
                    floyd[i * SIZE + j][i * SIZE + j] = 0;
                    if (field[i][j - 1]) {
                        floyd[i * SIZE + j][i * SIZE + (j - 1)] = 1;
                    }
                    if (field[i][j + 1]) {
                        floyd[i * SIZE + j][i * SIZE + (j + 1)] = 1;
                    }
                    if (field[i - 1][j]) {
                        floyd[i * SIZE + j][(i - 1) * SIZE + j] = 1;
                    }
                    if (field[i + 1][j]) {
                        floyd[i * SIZE + j][(i + 1) * SIZE + j] = 1;
                    }
                }
            }
        }
        for (int k = 1; k < SIZE_SQ; k++) {
            for (int i = 1; i < SIZE_SQ; i++) {
                for (int j = 1; j < SIZE_SQ; j++) {
                    if (floyd[i][j] > floyd[i][k] + floyd[k][j]) {
                        floyd[i][j] = floyd[i][k] + floyd[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(
                new FileOutputStream("output.txt")));
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (field[i][j]) {
                    for (int k = i + 1; k <= N; k++) {
                        for (int l = j + 1; l <= N; l++) {
                            if (field[k][l]) {
                                if (floyd[i * SIZE + j][k * SIZE + l] == INF) {
                                    out.write("IMPOSSIBLE");
                                    out.close();
                                    System.exit(0);
                                }
                            }
                        }
                    }
                }
            }
        }
        StringBuilder accumulatedSequence = new StringBuilder();
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (field[i][j]) {
                    boolean[][] f = getFieldCopy();
                    Point stopHere = goAccumulated(f, new Point(i, j), accumulatedSequence);
                    StringBuilder extendedMoves = goStillUnvisited(f, stopHere);
                    accumulatedSequence.append(extendedMoves);
                }
            }
        }
        out.write(accumulatedSequence.toString());
        out.close();
    }

    private List<Point> getPathAsList(Point p1, Point p2) {
        int cx = p1.x, cy = p1.y;
        List<Point> ans = new ArrayList<>();
        while (cx != p2.x || cy != p2.y) {
            ans.add(new Point(cx, cy));
            int flatNumber = next[cx * SIZE + cy][p2.x * SIZE + p2.y];
            cx = flatNumber / SIZE;
            cy = flatNumber % SIZE;
        }
        ans.add(p2);
        return ans;
    }

    private StringBuilder getPathAsSequence(Point p1, Point p2) {
        List<Point> points = getPathAsList(p1, p2);
        StringBuilder seq = new StringBuilder();
        for (int i = 1; i < points.size(); i++) {
            Point cur = points.get(i), prev = points.get(i - 1);
            if (cur.x + 1 == prev.x && cur.y == prev.y) {
                seq.append("T");
            }
            if (cur.x - 1 == prev.x && cur.y == prev.y) {
                seq.append("B");
            }
            if (cur.x == prev.x && cur.y - 1 == prev.y) {
                seq.append("R");
            }
            if (cur.x == prev.x && cur.y + 1 == prev.y) {
                seq.append("L");
            }
        }
        return seq;
    }

    private boolean[][] getFieldCopy() {
        boolean[][] f = new boolean[SIZE][SIZE];
        for (int k = 0; k < SIZE; k++) {
            System.arraycopy(field[k], 0, f[k], 0, SIZE);
        }
        return f;
    }

    private StringBuilder goStillUnvisited(boolean[][] f, Point startPoint) {
        List<Point> pointsToVisit = new ArrayList<>();
        pointsToVisit.add(startPoint);
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (f[i][j] && field[i][j]) {
                    Point p = new Point(i, j);
                    if (!p.equals(startPoint)) {
                        pointsToVisit.add(p);
                    }
                }
            }
        }
        List<MazeWay> edges = new ArrayList<>();
        int pointsSize = pointsToVisit.size();
        for (int c1 = 0; c1 < pointsSize; c1++) {
            for (int c2 = c1 + 1; c2 < pointsSize; c2++) {
                Point p1 = pointsToVisit.get(c1), p2 = pointsToVisit.get(c2);
                edges.add(new MazeWay(floyd[p1.x * SIZE + p1.y][p2.x * SIZE + p2.y], c1, c2));
            }
        }
        Collections.sort(edges);
        int[] p = new int[pointsSize];
        for (int i = 0; i < pointsSize; i++) {
            p[i] = i;
        }
        List<List<Integer>> tree = new ArrayList<>();
        for (int i = 0; i < pointsSize; i++) {
            tree.add(new ArrayList<>());
        }
        for (MazeWay e : edges) {
            if (dsuGet(e.c1, p) != dsuGet(e.c2, p)) {
                tree.get(e.c1).add(e.c2);
                tree.get(e.c2).add(e.c1);
                dsuUnite(e.c1, e.c2, p);
            }
        }
        List<Point> ordered = new ArrayList<>();
        Stack<Integer> st = new Stack<>();
        boolean[] visited = new boolean[pointsSize];
        st.push(0);
        while (!st.empty()) {
            int s = st.peek();
            st.pop();
            if (!visited[s]) {
                ordered.add(pointsToVisit.get(s));
                visited[s] = true;
            }
            for (Integer nxt : tree.get(s)) {
                if (!visited[nxt]) {
                    st.push(nxt);
                }
            }
        }
        StringBuilder result = new StringBuilder();
        for (int i = 1; i < ordered.size(); i++) {
            result.append(getPathAsSequence(ordered.get(i - 1), ordered.get(i)));
        }
        return result;
    }

    private int dsuGet(int v, int[] p) {
        return v == p[v] ? v : (p[v] = dsuGet(p[v], p));
    }

    private void dsuUnite(int u, int v, int[] p) {
        u = dsuGet(u, p);
        v = dsuGet(v, p);
        if (rnd.nextBoolean()) {
            int c = u;
            u = v;
            v = c;
        }
        if (u != v) {
            p[u] = v;
        }
    }

    private Point goAccumulated(boolean[][] f, Point start, StringBuilder sequence) {
        int x = start.x, y = start.y;
        f[x][y] = false;
        for (int i = 0; i < sequence.length(); i++) {
            char move = sequence.charAt(i);
            if (move == 'T' && field[x - 1][y]) {
                x--;
                f[x][y] = false;
            }
            if (move == 'B' && field[x + 1][y]) {
                x++;
                f[x][y] = false;
            }
            if (move == 'L' && field[x][y - 1]) {
                y--;
                f[x][y] = false;
            }
            if (move == 'R' && field[x][y + 1]) {
                y++;
                f[x][y] = false;
            }
        }
        return new Point(x, y);
    }

    class MazeWay implements Comparable<MazeWay> {
        int length, c1, c2;

        MazeWay(int length, int c1, int c2) {
            this.length = length;
            this.c1 = c1;
            this.c2 = c2;
        }

        @Override
        public int compareTo(MazeWay mwp) {
            return this.length - mwp.length;
        }
    }
}