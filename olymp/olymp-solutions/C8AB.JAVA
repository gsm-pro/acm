import java.io.*;
import java.nio.file.Paths;
import java.util.AbstractMap.SimpleEntry;
import java.util.*;
import java.util.Map.Entry;
import java.util.concurrent.atomic.AtomicInteger;

import static java.lang.Integer.*;
import static java.lang.System.lineSeparator;
import static java.nio.file.Files.*;
import static java.time.temporal.ValueRange.of;
import static java.util.Comparator.comparingInt;
import static java.util.Objects.hash;
import static java.util.function.Function.identity;
import static java.util.stream.Collectors.*;

public class Solution {
    public static void main(String... args) throws Exception {
        try (BufferedReader in = new BufferedReader(
                new InputStreamReader(newInputStream(Paths.get("input.txt"))))) {
            try (BufferedWriter out = new BufferedWriter(
                    new OutputStreamWriter(newOutputStream(Paths.get("output.txt"))))) {
                new Solution().solve(in, out);
            }
        }
    }

    private void solve(BufferedReader in, BufferedWriter out) throws Exception {
        String[] items = in.readLine().split(" ");
        int n = parseInt(items[0]), m = parseInt(items[1]);
        char[][] c = new char[n][];
        for (int i = 0; i < n; i++) c[i] = in.readLine().toCharArray();
        out.write(solve(n, m, c));
    }

    private String solve(int n, int m, char[]... c) {
        final int[] D = {-1, 0, 1};
        Set<Stripe> $ = new TreeSet<>(comparingInt(Stripe::getCoordsHash));
        boolean[][] used = new boolean[n][m];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (!used[i][j]) {
                    Queue<SimpleEntry<Integer, Integer>> q = new LinkedList<>();
                    List<SimpleEntry<Integer, Integer>> comp = new ArrayList<>();
                    q.add(new SimpleEntry<>(i, j));
                    used[i][j] = true;
                    while (!q.isEmpty()) {
                        int x = q.peek().getKey(), y = q.peek().getValue();
                        comp.add(q.poll());
                        for (int dx : D)
                            for (int dy : D)
                                if (dx + dy == -1 || dx + dy == 1) {
                                    int xx = x + dx, yy = y + dy;
                                    if (xx >= 0 && xx < n && yy >= 0 && yy < m
                                            && !used[xx][yy] && c[i][j] == c[xx][yy]) {
                                        used[xx][yy] = true;
                                        q.add(new SimpleEntry<>(xx, yy));
                                    }
                                }
                    }
                    Set<Stripe> hStripes = new HashSet<>(), vStripes = new HashSet<>();
                    if (comp.size() == 1) {
                        $.add(new Stripe(Dir.H, i, j, 1, c[i][j], -1));
                        continue;
                    }
                    Map<Integer, List<SimpleEntry<Integer, Integer>>>
                            byX = comp.stream().collect(groupingBy(SimpleEntry::getKey)),
                            byY = comp.stream().collect(groupingBy(SimpleEntry::getValue));
                    for (int xKey : byX.keySet()) {
                        byX.get(xKey).add(new SimpleEntry<>(xKey, MAX_VALUE));
                        List<Integer> ys = byX.get(xKey).stream()
                                .map(SimpleEntry::getValue)
                                .sorted()
                                .collect(toList());
                        for (int k = 1, len = 1; k < ys.size(); k++)
                            if (ys.get(k) == ys.get(k - 1) + 1)
                                len++;
                            else {
                                if (len > 1)
                                    hStripes.add(new Stripe(
                                            Dir.H, xKey, ys.get(k - 1) - len + 1,
                                            len, c[i][j], hStripes.size()));
                                len = 1;
                            }
                    }
                    for (int yKey : byY.keySet()) {
                        byY.get(yKey).add(new SimpleEntry<>(MAX_VALUE, yKey));
                        List<Integer> xs = byY.get(yKey).stream()
                                .map(SimpleEntry::getKey)
                                .sorted()
                                .collect(toList());
                        for (int k = 1, len = 1; k < xs.size(); k++)
                            if (xs.get(k) == xs.get(k - 1) + 1)
                                len++;
                            else {
                                if (len > 1)
                                    vStripes.add(new Stripe(
                                            Dir.V, xs.get(k - 1) - len + 1, yKey,
                                            len, c[i][j], vStripes.size()));
                                len = 1;
                            }
                    }
                    if (hStripes.size() > 0 && vStripes.size() == 0) {
                        $.addAll(hStripes);
                        continue;
                    }
                    if (hStripes.size() == 0 && vStripes.size() > 0) {
                        $.addAll(vStripes);
                        continue;
                    }
                    for (Stripe hStripe : hStripes)
                        for (Stripe vStripe : vStripes)
                            if (hStripe.intersect(vStripe)) {
                                hStripe.incCoverage();
                                vStripe.incCoverage();
                                hStripe.addConnId(vStripe.id);
                                vStripe.addConnId(hStripe.id);
                            }
                    hStripes.stream()
                            .filter(Stripe::isNotCovered)
                            .forEach(hStripe -> {
                                $.add(hStripe);
                                vStripes.stream()
                                        .filter(vStripe -> vStripe.deleteConnId(hStripe.id))
                                        .forEach(vStripe -> hStripe.deleteConnId(vStripe.id));
                            });
                    vStripes.stream()
                            .filter(Stripe::isNotCovered)
                            .forEach(vStripe -> {
                                $.add(vStripe);
                                hStripes.stream()
                                        .filter(hStripe -> hStripe.deleteConnId(vStripe.id))
                                        .forEach(hStripe -> vStripe.deleteConnId(hStripe.id));
                            });
                    hStripes.stream()
                            .filter(Stripe::emptyConnIds)
                            .collect(toList())
                            .forEach(hStripes::remove);
                    vStripes.stream()
                            .filter(Stripe::emptyConnIds)
                            .collect(toList())
                            .forEach(vStripes::remove);
                    Set<Integer> hVisited = new HashSet<>(), vVisited = new HashSet<>();
                    Map<Integer, Integer> match = new HashMap<>();
                    Map<Integer, Stripe> hToId = hStripes.stream()
                            .collect(toMap(
                                    Stripe::getId,
                                    identity()));
                    Map<Integer, Stripe> vToId = vStripes.stream()
                            .collect(toMap(
                                    Stripe::getId,
                                    identity()));
                    for (Integer hId : hToId.keySet()) {
                        hVisited.clear();
                        kuhn(hId, hToId, hVisited, match);
                    }
                    hVisited.clear();
                    for (Entry<Integer, Stripe> h : hToId.entrySet()) {
                        Iterator<Integer> it = h.getValue().connIds.iterator();
                        Integer from = h.getKey();
                        while (it.hasNext()) {
                            Integer to = it.next();
                            if (Objects.equals(match.get(to), from)) it.remove();
                        }
                    }
                    Set<Integer> startPoints = new HashSet<>(hToId.keySet());
                    for (Entry<Integer, Stripe> v : vToId.entrySet()) {
                        Iterator<Integer> it = v.getValue().connIds.iterator();
                        Integer to = v.getKey();
                        while (it.hasNext()) {
                            Integer from = it.next();
                            if (!Objects.equals(match.get(to), from)) it.remove();
                            else startPoints.remove(from);
                        }
                    }
                    for (Integer startPoint : startPoints) {
                        hVisited.add(startPoint);
                        dfs(startPoint, 0, hToId, vToId, hVisited, vVisited);
                    }
                    $.addAll(hToId.keySet().stream()
                            .filter(h -> !hVisited.contains(h))
                            .map(hToId::get)
                            .collect(toList()));
                    $.addAll(vToId.keySet().stream()
                            .filter(vVisited::contains)
                            .map(vToId::get)
                            .collect(toList()));
                }
        return $.size()
                + lineSeparator()
                + $.stream()
                .map(Stripe::toString)
                .collect(joining(lineSeparator()));
    }

    private boolean kuhn(int id, Map<Integer, Stripe> hToId,
                         Set<Integer> hVisited, Map<Integer, Integer> match) {
        if (!hVisited.contains(id)) {
            hVisited.add(id);
            for (Integer conn : hToId.get(id).connIds)
                if (match.get(conn) == null || kuhn(match.get(conn), hToId, hVisited, match)) {
                    match.put(conn, id);
                    return true;
                }
        }
        return false;
    }

    private void dfs(int id, int side,
                     Map<Integer, Stripe> hToId, Map<Integer, Stripe> vToId,
                     Set<Integer> hVisited, Set<Integer> vVisited) {
        if (side == 0) {
            if (hToId.get(id) == null) return;
            for (Integer conn : hToId.get(id).connIds)
                if (!vVisited.contains(conn)) {
                    vVisited.add(conn);
                    dfs(conn, side ^ 1, hToId, vToId, hVisited, vVisited);
                }
        } else {
            if (vToId.get(id) == null) return;
            for (Integer conn : vToId.get(id).connIds)
                if (!hVisited.contains(conn)) {
                    hVisited.add(conn);
                    dfs(conn, side ^ 1, hToId, vToId, hVisited, vVisited);
                }
        }
    }

    static class Stripe {
        private final Dir d;
        private final int x, y, z, id;
        private final char c;
        private final Set<Integer> connIds;
        private final AtomicInteger coverage = new AtomicInteger();

        public Stripe(Dir d, int x, int y, int z, char c, int id) {
            this.d = d;
            this.x = x;
            this.y = y;
            this.z = z;
            this.c = c;
            this.id = id;
            this.connIds = new HashSet<>();
        }

        int getCoordsHash() {
            return (x << 20) + (y << 10) + (d == Dir.H ? 0 : 1);
        }

        public int getId() {
            return id;
        }

        boolean intersect(Stripe x) {
            if (this.d == Dir.H && x.d == Dir.V)
                return of(x.x, x.x + x.z - 1).isValidValue(this.x)
                        && of(this.y, this.y + this.z - 1).isValidValue(x.y);
            if (this.d == Dir.V && x.d == Dir.H)
                return of(this.x, this.x + this.z - 1).isValidValue(x.x)
                        && of(x.y, x.y + x.z - 1).isValidValue(this.y);
            throw new RuntimeException();
        }

        void incCoverage() {
            coverage.incrementAndGet();
        }

        boolean isNotCovered() {
            return z != coverage.get();
        }

        void addConnId(int id) {
            connIds.add(id);
        }

        boolean deleteConnId(int id) {
            return connIds.remove(id);
        }

        boolean emptyConnIds() {
            return connIds.size() == 0;
        }

        @Override
        public String toString() {
            return String.format("%s %d %d %d %c", d, x + 1, y + 1, z, c);
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Stripe stripe = (Stripe) o;
            return d == stripe.d
                    && x == stripe.x
                    && y == stripe.y
                    && z == stripe.z
                    && c == stripe.c;
        }

        @Override
        public int hashCode() {
            return hash(d, x, y, z, c);
        }
    }

    enum Dir {
        H, V
    }
}