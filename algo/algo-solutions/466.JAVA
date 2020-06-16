import java.util.Scanner;

class Solution {
    public static void main(String[] args) throws Exception {
        new Solution().start();
    }

    private void start() throws Exception {
        SegmentTree3D segmentTree3D = new SegmentTree3D();
        Scanner in = new Scanner(System.in);
        int n = in.nextInt() << 1;
        long[][][] t = new long[n][n][n];
        while (true) {
            int type = in.nextInt();
            if (type == 3) {
                break;
            }
            if (type == 1) {
                segmentTree3D.add(t, in.nextInt(), in.nextInt(), in.nextInt(), in.nextInt());
            }
            if (type == 2) {
                System.out.println(segmentTree3D.get(t, in.nextInt(), in.nextInt(), in.nextInt(),
                        in.nextInt(), in.nextInt(), in.nextInt()));
            }
        }
    }

    class SegmentTree3D {
        private long fNeutral() {
            return 0L;
        }

        private long f(long a, long b) {
            return a + b;
        }

        long get(long[][][] t, int x1, int y1, int z1, int x2, int y2, int z2) {
            int n = t.length >> 1;
            x1 += n;
            x2 += n;
            int m = t[0].length >> 1;
            y1 += m;
            y2 += m;
            int k = t[0][0].length >> 1;
            z1 += k;
            z2 += k;
            long res = fNeutral();
            for (int lx = x1, rx = x2; lx <= rx; lx = (lx + 1) >> 1, rx = (rx - 1) >> 1) {
                for (int ly = y1, ry = y2; ly <= ry; ly = (ly + 1) >> 1, ry = (ry - 1) >> 1) {
                    for (int lz = z1, rz = z2; lz <= rz; lz = (lz + 1) >> 1, rz = (rz - 1) >> 1) {
                        if ((lx & 1) != 0 && (ly & 1) != 0 && (lz & 1) != 0) {
                            res = f(res, t[lx][ly][lz]);
                        }
                        if ((lx & 1) != 0 && (ly & 1) != 0 && (rz & 1) == 0) {
                            res = f(res, t[lx][ly][rz]);
                        }
                        if ((lx & 1) != 0 && (ry & 1) == 0 && (lz & 1) != 0) {
                            res = f(res, t[lx][ry][lz]);
                        }
                        if ((lx & 1) != 0 && (ry & 1) == 0 && (rz & 1) == 0) {
                            res = f(res, t[lx][ry][rz]);
                        }
                        if ((rx & 1) == 0 && (ly & 1) != 0 && (lz & 1) != 0) {
                            res = f(res, t[rx][ly][lz]);
                        }
                        if ((rx & 1) == 0 && (ly & 1) != 0 && (rz & 1) == 0) {
                            res = f(res, t[rx][ly][rz]);
                        }
                        if ((rx & 1) == 0 && (ry & 1) == 0 && (lz & 1) != 0) {
                            res = f(res, t[rx][ry][lz]);
                        }
                        if ((rx & 1) == 0 && (ry & 1) == 0 && (rz & 1) == 0) {
                            res = f(res, t[rx][ry][rz]);
                        }
                    }
                }
            }
            return res;
        }

        void add(long[][][] t, int x, int y, int z, int value) {
            x += t.length >> 1;
            y += t[0].length >> 1;
            z += t[0][0].length >> 1;
            t[x][y][z] += value;
            for (int tx = x; tx > 0; tx >>= 1) {
                for (int ty = y; ty > 0; ty >>= 1) {
                    for (int tz = z; tz > 0; tz >>= 1) {
                        if (tx > 1) {
                            t[tx >> 1][ty][tz] = f(t[tx][ty][tz], t[tx ^ 1][ty][tz]);
                        }
                        if (ty > 1) {
                            t[tx][ty >> 1][tz] = f(t[tx][ty][tz], t[tx][ty ^ 1][tz]);
                        }
                        if (tz > 1) {
                            t[tx][ty][tz >> 1] = f(t[tx][ty][tz], t[tx][ty][tz ^ 1]);
                        }
                    }
                }
            }
        }
    }
}