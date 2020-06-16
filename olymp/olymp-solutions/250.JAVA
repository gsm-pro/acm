import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

public class Solution {
    private static final int[] DX = new int[]{-1, 0, 0, 1};
    private static final int[] DY = new int[]{0, -1, 1, 0};
    private static final String DIR = "NWES";
    private int[][] TEMP_GRID = new int[5][5];
    private char[][] TEMP_MOVE = new char[5][5];
    private char[][] GRID = new char[111][111];
    private boolean[][] USED = new boolean[111][111];
    private List<Character> RES = new ArrayList<>();
    private List<Character> PATH = new ArrayList<>();
    private int N, M, SX, SY, EX, EY;

    private void clearTempGrid() {
        for (int[] a : TEMP_GRID) {
            Arrays.fill(a, -1);
        }
    }

    private void clearTempMove() {
        for (char[] a : TEMP_MOVE) {
            Arrays.fill(a, ' ');
        }
    }

    private void clearUsed() {
        for (boolean[] a : USED) {
            Arrays.fill(a, false);
        }
    }

    private boolean valid(int x, int y) {
        return x >= 0 && x < N && y >= 0 && y < M;
    }

    private boolean valid2(int x, int y) {
        return x >= 0 && x < 5 && y >= 0 && y < 5;
    }

    private void dfs(int x, int y, int t, int sx, int sy) {
        TEMP_GRID[x - sx + 2][y - sy + 2] = t;
        if (t < 3) {
            for (int i = 0; i < 4; i++) {
                int x2 = x + DX[i], y2 = y + DY[i];
                if (valid(x2, y2)
                        && valid2(x2 - sx + 2, y2 - sy + 2)
                        && TEMP_GRID[x2 - sx + 2][y2 - sy + 2] == -1
                        && GRID[x2][y2] != 'X') {
                    TEMP_MOVE[x2 - sx + 2][y2 - sy + 2] = DIR.charAt(i);
                    dfs(x2, y2, t + 1, sx, sy);
                }
            }
        }
    }

    private List<Character> back2(int x, int y) {
        if (TEMP_GRID[x][y] == 0) {
            return new ArrayList<>();
        }
        int d = 3 - DIR.indexOf(TEMP_MOVE[x][y]);
        int x2 = x + DX[d], y2 = y + DY[d];
        List<Character> res = back2(x2, y2);
        res.add(TEMP_MOVE[x][y]);
        return res;
    }

    private List<Character> getRev(List<Character> str) {
        List<Character> tmp = new ArrayList<>(str);
        Collections.reverse(tmp);
        return tmp.stream().map(x -> DIR.charAt(3 - DIR.indexOf(x))).collect(Collectors.toList());
    }

    private List<Character> isPossible(int sx, int sy, int d) {
        clearTempGrid();
        dfs(sx, sy, 0, sx, sy);
        int x = -1, y = -1;
        for (int i = 0; i <= 4; i++) {
            for (int j = 0; j <= 4; j++) {
                if (i == 0 || i == 4 || j == 0 || j == 4) {
                    if (TEMP_GRID[i][j] == -1) {
                        continue;
                    }
                    x = i;
                    y = j;
                } else if (valid(sx + i - 2, sy + j - 2) && GRID[sx + i - 2][sy + j - 2] == 'T') {
                    return new ArrayList<>();
                } else if (valid(sx + i - 2, sy + j - 2) && GRID[sx + i - 2][sy + j - 2] == 'X') {
                    if (TEMP_GRID[i][j] == -1) {
                        continue;
                    }
                    GRID[sx + i - 2][sy + i - 2] = '.';
                }
            }
        }
        if (x == -1 && y == -1) {
            return new ArrayList<>();
        }
        List<Character> str = back2(x, y);
        List<Character> rts = getRev(str);
        List<Character> res = new ArrayList<>();
        res.add('M');
        res.addAll(str);
        for (int i = 1; i <= 3 - str.size(); i++) {
            res.add('T');
        }
        res.addAll(rts);
        res.add(DIR.charAt(d));
        return res;
    }

    private void dfs(int x, int y) {
        USED[x][y] = true;
        if (x == EX && y == EY) {
            RES = PATH;
        }
        for (int i = 0; i <= 3; i++) {
            int x2 = x + DX[i], y2 = y + DY[i];
            if (valid(x2, y2) && !USED[x2][y2]) {
                if (GRID[x2][y2] != 'X') {
                    PATH.add(DIR.charAt(i));
                    dfs(x2, y2);
                    PATH.add(DIR.charAt(3 - i));
                } else {
                    List<Character> seq = isPossible(x, y, i);
                    if (seq.size() > 0) {
                        PATH.addAll(seq);
                        dfs(x2, y2);
                        PATH.add(DIR.charAt(3 - i));
                    }
                }
            }
        }
    }

    private void solve() {
        SX = SY = EX = EY = -1;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (GRID[i][j] == 'E') {
                    SX = i;
                    SY = j;
                } else if (GRID[i][j] == 'T') {
                    EX = i;
                    EY = j;
                }
            }
        }
        dfs(SX, SY);
    }

    private String cutPath(List<Character> path) {
        int curX = SX, curY = SY, z = 0;
        for (char c : path) {
            z++;
            if (c == 'N') {
                curX--;
            }
            if (c == 'S') {
                curX++;
            }
            if (c == 'W') {
                curY--;
            }
            if (c == 'E') {
                curY++;
            }
            if (curX == EX && curY == EY) {
                break;
            }
        }
        return path.subList(0, z).stream().map(Object::toString).collect(Collectors.joining());
    }

    private void exploder() throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
        String[] tokens = in.readLine().split(" ");
        N = Integer.parseInt(tokens[0]);
        M = Integer.parseInt(tokens[1]);
        for (int i = 0; i < N; i++) {
            String line = in.readLine();
            GRID[i] = line.toCharArray();
        }
        clearTempGrid();
        clearTempMove();
        clearUsed();
        solve();
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("output.txt")));
        if (RES.size() == 0) {
            out.write("No solution");
        } else {
            out.write(cutPath(RES));
        }
        out.close();
    }

    public static void main(String[] args) throws Exception {
        new Solution().exploder();
    }
}