import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class Solution {
    class Segment {
        private long x1, y1, x2, y2;

        public Segment(String source) {
            StringTokenizer st = new StringTokenizer(source);
            x1 = Long.parseLong(st.nextToken());
            y1 = Long.parseLong(st.nextToken());
            x2 = Long.parseLong(st.nextToken());
            y2 = Long.parseLong(st.nextToken());
        }

        public boolean hasIntersectionWith(Segment s2) {
            Segment s1 = this;
            return intersect(s1.x1, s1.x2, s2.x1, s2.x2) && intersect(s1.y1, s1.y2, s2.y1, s2.y2) &&
                    vector(s1.x1, s1.y1, s1.x2, s1.y2, s2.x1, s2.y1) * vector(s1.x1, s1.y1, s1.x2, s1.y2, s2.x2, s2.y2) <= 0 &&
                    vector(s2.x1, s2.y1, s2.x2, s2.y2, s1.x1, s1.y1) * vector(s2.x1, s2.y1, s2.x2, s2.y2, s1.x2, s1.y2) <= 0;
        }

        private long vector(long ax, long ay, long bx, long by, long cx, long cy) {
            return (bx - ax) * (cy - ay) - (cx - ax) * (by - ay);
        }

        private boolean intersect(long a, long b, long c, long d) {
            return Math.max(Math.min(a, b), Math.min(c, d)) <= Math.min(Math.max(a, b), Math.max(c, d));
        }
    }

    public void start() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        List<Segment> segments = new ArrayList<Segment>(n);
        for (int i = 0; i < n; i++) {
            String t = in.readLine();
            segments.add(new Segment(t));
        }
        int result = 0;
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (segments.get(i).hasIntersectionWith(segments.get(j))) {
                    result++;
                }
            }
        }
        System.out.println(result);
    }

    public static void main(String[] args) throws IOException {
        new Solution().start();
    }
}