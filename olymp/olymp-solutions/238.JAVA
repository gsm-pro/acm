import java.awt.*;
import java.io.*;
import java.util.*;
import java.util.List;

class Solution {
    public static void main(String[] args) throws Exception {
        new Solution().solve();
    }

    private static final short VOID = 1000;
    private static final int MAX_SIZE = 111;
    private List<List<Short>> GRAPH;
    private boolean[] USED;
    private short[] MATCH;
    private Map<Point, Short> pointToId0;
    private Map<Point, Short> pointToId1;

    private void solve() throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(
                new FileInputStream("input.txt")));
        String name = in.readLine();
        String[] tokens = in.readLine().split("\\s+");
        int n = Integer.parseInt(tokens[0]),
                k = Integer.parseInt(tokens[2]),
                p = Integer.parseInt(tokens[3]),
                nameLength = name.length();
        short[][] field = new short[MAX_SIZE][MAX_SIZE];
        for (int i = 0; i < MAX_SIZE; i++) {
            for (int j = 0; j < MAX_SIZE; j++) {
                field[i][j] = VOID;
            }
        }
        String line;
        List<Short> digits = new ArrayList<>();
        while ((line = in.readLine()) != null) {
            tokens = line.split("\\s+");
            for (String t : tokens) {
                if (!t.isEmpty()) {
                    digits.add(Short.parseShort(t));
                }
            }
        }
        for (int i = 0; i < k; i++) {
            field[i / n][i % n] = digits.get(i);
        }
        in.close();
        List<Integer> erasedPairsCnt = new ArrayList<>();
        List<String> operations = new ArrayList<>();
        Character symbol = null;
        while (true) {
            pointToId0 = new HashMap<>();
            pointToId1 = new HashMap<>();
            GRAPH = new ArrayList<>();
            for (int i = 0; i < MAX_SIZE; i++) {
                GRAPH.add(new ArrayList<>());
            }
            for (int i = 0; i < MAX_SIZE; i++) {
                for (int j = 0; j < MAX_SIZE; j++) {
                    int F = field[i][j];
                    if (((i + j) % 2 == 0) && F != VOID) {
                        Point cur = new Point(i, j);
                        if (i > 0 && F + field[i - 1][j] == p) {
                            Point nxt = new Point(i - 1, j);
                            insertPair(cur, nxt);
                            GRAPH.get(pointToId0.get(cur)).add(pointToId1.get(nxt));
                        }
                        if (i < MAX_SIZE - 1 && F + field[i + 1][j] == p) {
                            Point nxt = new Point(i + 1, j);
                            insertPair(cur, nxt);
                            GRAPH.get(pointToId0.get(cur)).add(pointToId1.get(nxt));
                        }
                        if (j > 0 && F + field[i][j - 1] == p) {
                            Point nxt = new Point(i, j - 1);
                            insertPair(cur, nxt);
                            GRAPH.get(pointToId0.get(cur)).add(pointToId1.get(nxt));
                        }
                        if (j < MAX_SIZE - 1 && F + field[i][j + 1] == p) {
                            Point nxt = new Point(i, j + 1);
                            insertPair(cur, nxt);
                            GRAPH.get(pointToId0.get(cur)).add(pointToId1.get(nxt));
                        }
                    }
                }
            }
            int n0 = pointToId0.size(), n1 = pointToId1.size();
            MATCH = new short[n1];
            USED = new boolean[n0];
            Arrays.fill(MATCH, (short) -1);
            for (short v = 0; v < n0; v++) {
                Arrays.fill(USED, false);
                tryKuhn(v);
            }
            List<Point> pairs = new ArrayList<>();
            for (int v = 0; v < n1; v++) {
                if (MATCH[v] != -1) {
                    pairs.add(new Point(MATCH[v], v));
                }
            }
            if (pairs.size() > 0) {
                if (!operations.isEmpty()) {
                    operations.add("\n");
                }
                for (Point pair : pairs) {
                    Point p1 = pointToId0.entrySet().stream().filter(e -> pair.x == e.getValue()).map(Map.Entry::getKey).findFirst().orElse(null);
                    Point p2 = pointToId1.entrySet().stream().filter(e -> pair.y == e.getValue()).map(Map.Entry::getKey).findFirst().orElse(null);
                    if (p1 != null && p2 != null) {
                        operations.add(String.format("%d,%d; %d,%d\n", p1.x + 1, p1.y + 1, p2.x + 1, p2.y + 1));
                        field[p1.x][p1.y] = field[p2.x][p2.y] = VOID;
                    }
                }
            }
            List<Short> remaining = new ArrayList<>();
            for (int i = 0; i < MAX_SIZE; i++) {
                for (int j = 0; j < MAX_SIZE; j++) {
                    if (field[i][j] != VOID) {
                        remaining.add(field[i][j]);
                    }
                }
            }
            if (pairs.size() == 0 && !remaining.isEmpty()) {
                if (nameLength != 0) {
                    symbol = name.charAt((remaining.stream().mapToInt(Short::shortValue).sum() - 1) % nameLength);
                } else {
                    symbol = Character.OTHER_SYMBOL;
                }
                break;
            }
            erasedPairsCnt.add(pairs.size());
            if (remaining.isEmpty()) {
                break;
            }
            if (nameLength == 0) {
                symbol = Character.OTHER_SYMBOL;
                break;
            }
            field = new short[MAX_SIZE][MAX_SIZE];
            for (int i = 0; i < MAX_SIZE; i++) {
                for (int j = 0; j < MAX_SIZE; j++) {
                    field[i][j] = VOID;
                }
            }
            for (int i = 0; i < remaining.size(); i++) {
                field[i / nameLength][i % nameLength] = remaining.get(i);
            }
        }
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(
                new FileOutputStream("output.txt")));
        if (symbol == null) {
            out.write("It is your best friend!");
        } else {
            if (symbol != Character.OTHER_SYMBOL) {
                out.write(symbol);
            }
        }
        out.write("\n");
        for (Integer e : erasedPairsCnt) {
            out.write(e + " ");
        }
        out.write("\n");
        for (String op : operations) {
            out.write(op);
        }
        out.close();
    }

    private boolean tryKuhn(short v) {
        if (USED[v]) {
            return false;
        }
        USED[v] = true;
        for (Short to : GRAPH.get(v)) {
            if (MATCH[to] == -1 || tryKuhn(MATCH[to])) {
                MATCH[to] = v;
                return true;
            }
        }
        return false;
    }

    private void insertPair(Point cur, Point nxt) {
        if (!pointToId0.containsKey(cur)) {
            pointToId0.put(cur, (short) pointToId0.size());
        }
        if (!pointToId1.containsKey(nxt)) {
            pointToId1.put(nxt, (short) pointToId1.size());
        }
    }
}