import java.io.*;
import java.util.*;

public class Solution {
    public static void main(String[] args) throws Exception {
        new Solution().solve();
    }

    private int[] eAdj, eLast, ePrev, eCost;
    private int eIdx;

    class Edge implements Comparable<Edge> {
        int to, weight;

        Edge(int to, int weight) {
            this.to = to;
            this.weight = weight;
        }

        @Override
        public int compareTo(Edge other) {
            return weight - other.weight;
        }
    }

    private void addEdge(int a, int b, int c) {
        eAdj[eIdx] = b;
        eCost[eIdx] = c;
        ePrev[eIdx] = eLast[a];
        eLast[a] = eIdx++;
        eAdj[eIdx] = a;
        eCost[eIdx] = c;
        ePrev[eIdx] = eLast[b];
        eLast[b] = eIdx++;
    }

    private int findTime(int a, int b) {
        for (int e = eLast[a]; e != -1; e = ePrev[e]) {
            if (eAdj[e] == b) {
                return eCost[e];
            }
        }
        return -1;
    }

    private void solve() throws Exception {
        Scanner in = new Scanner(new File("input.txt"));
        PrintWriter out = new PrintWriter(new File("output.txt"));
        int N = in.nextInt(), M = in.nextInt();
        int A = in.nextInt(), B = in.nextInt(), K = in.nextInt(), G = in.nextInt();
        A--;
        B--;
        eAdj = new int[2 * M];
        eLast = new int[N];
        ePrev = new int[2 * M];
        eCost = new int[2 * M];
        Arrays.fill(eLast, -1);
        eIdx = 0;
        int[] path = new int[G];
        int[] time = new int[G];
        int[] sumTime = new int[G];
        for (int i = 0; i < G; i++) {
            path[i] = in.nextInt() - 1;
        }
        for (int i = 0; i < M; i++) {
            int a = in.nextInt(), b = in.nextInt(), c = in.nextInt();
            a--;
            b--;
            addEdge(a, b, c);
        }
        for (int i = 0; i < G - 1; i++) {
            time[i] = findTime(path[i], path[i + 1]);
        }
        sumTime[0] = time[0];
        for (int i = 1; i < G - 1; i++) {
            sumTime[i] = sumTime[i - 1] + time[i];
        }
        int[] dist = new int[N];
        Arrays.fill(dist, Integer.MAX_VALUE >> 2);
        PriorityQueue<Edge> pq = new PriorityQueue<>();
        pq.add(new Edge(A, dist[A] = K));
        int idx = 0;
        while (pq.size() > 0) {
            Edge deq = pq.poll();
            if (deq.weight != dist[deq.to]) {
                continue;
            }
            while (idx < G - 2 && sumTime[idx] < deq.weight) {
                idx++;
            }
            int first = path[idx], second = path[idx + 1];
            for (int e = eLast[deq.to]; e != -1; e = ePrev[e]) {
                int wait;
                if ((first == deq.to && second == eAdj[e]) ||
                        (second == deq.to && first == eAdj[e])) {
                    wait = Math.max(0, sumTime[idx] - deq.weight);
                } else {
                    wait = 0;
                }
                if (eCost[e] + wait + deq.weight < dist[eAdj[e]]) {
                    pq.add(new Edge(eAdj[e], dist[eAdj[e]] = eCost[e] + wait + deq.weight));
                }
            }
        }
        out.print(dist[B] - K);
        out.close();
    }
}