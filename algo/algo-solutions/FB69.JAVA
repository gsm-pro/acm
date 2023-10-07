import java.util.*;

import static java.lang.Math.*;

public class Solution {
    private int curValue;

    private int genNextRandom() {
        curValue = (curValue * 1999 + 17) % 1000003;
        return curValue;
    }

    private long process(int N, int M, int startValue, int maxValue, int maxHeight) {
        curValue = startValue;
        Node[] nodes = new Node[N];
        nodes[0] = new Node(0, 0);
        for (int i = 1; i < N; i++) {
            int value = genNextRandom() % maxValue;
            Node p = nodes[max(0, i - 1 - (genNextRandom() % maxHeight))];
            nodes[i] = new Node(i, value);
            link(p, nodes[i]);
        }
        long ans = 0;
        for (int i = 0; i < M; i++) {
            int x = genNextRandom() % N;
            int y = genNextRandom() % N;
            ans += query(nodes[min(x, y)], nodes[max(x, y)]);
        }
        return ans;
    }

    private void recalculate(Node u) {
        u.maxEdgeCost = u.realParentCost;
        if (u.left != null) {
            u.maxEdgeCost = max(u.maxEdgeCost, u.left.maxEdgeCost);
        }
        if (u.right != null) {
            u.maxEdgeCost = max(u.maxEdgeCost, u.right.maxEdgeCost);
        }
    }

    private long query(Node u, Node v) {
        if (u == v) {
            return -1;
        }
        access(u);
        Node t = u.left;
        while (t != null && t.right != null) {
            t = t.right;
        }
        if (t != null) {
            cut(u);
        }
        Node ur = findRoot(u);
        Node vr = findRoot(v);
        if (ur != vr) {
            link(v, u);
            return 0;
        }
        access(v);
        splay(u);
        int cost = 0;
        if (u.right != null) {
            cost = u.right.maxEdgeCost;
        }
        if (t != null) {
            link(t, u);
        }
        return cost;
    }

    public class Node {
        Node left, right, parent, pathParent;
        int idx, maxEdgeCost, realParentCost;

        Node(int idx, int realParentCost) {
            this.idx = idx;
            this.realParentCost = realParentCost;
            this.maxEdgeCost = realParentCost;
        }
    }

    private Node findRoot(Node x) {
        access(x);
        Node root = x;
        while (root.left != null) {
            root = root.left;
        }
        access(root);
        return root;
    }

    private void link(Node x, Node y) {
        access(x);
        access(y);
        y.left = x;
        x.parent = y;
        y.pathParent = x.pathParent;
        x.pathParent = null;
        recalculate(y);
    }

    private void cut(Node x) {
        access(x);
        if (x.left != null) {
            x.left.parent = null;
            x.left = null;
        }
        recalculate(x);
    }

    private void access(Node x) {
        Node prev = null;
        for (Node t = x; t != null; t = t.pathParent) {
            splay(t);
            if (t.right != null) {
                t.right.pathParent = t;
                t.right.parent = null;
            }
            t.right = prev;
            if (prev != null) {
                prev.parent = t;
                prev.pathParent = null;
            }
            prev = t;
            recalculate(t);
        }
        splay(x);
    }

    private void splay(Node x) {
        while (x.parent != null) {
            if (isLeftChild(x)) {
                if (x.parent.parent != null && isLeftChild(x.parent)) {
                    rotateLeft(x.parent);
                }
                rotateLeft(x);
            } else {
                if (x.parent.parent != null && !isLeftChild(x.parent)) {
                    rotateRight(x.parent);
                }
                rotateRight(x);
            }
        }
    }

    private boolean isLeftChild(Node x) {
        return x.parent.left == x;
    }

    private void rotateLeft(Node x) {
        Node p = x.parent;
        Node c = x.right;
        updateParent(x, p);
        updateRight(x, p);
        updateLeft(p, c);
        recalculate(p);
        recalculate(x);
    }

    private void rotateRight(Node x) {
        Node p = x.parent;
        Node c = x.left;
        updateParent(x, p);
        updateLeft(x, p);
        updateRight(p, c);
        recalculate(p);
        recalculate(x);
    }

    private void updateLeft(Node x, Node n) {
        if (x != null) {
            x.left = n;
        }
        if (n != null) {
            n.parent = x;
        }
    }

    private void updateRight(Node x, Node n) {
        if (x != null) {
            x.right = n;
        }
        if (n != null) {
            n.parent = x;
        }
    }

    private void updateParent(Node x, Node p) {
        Node g = p.parent;
        if (g != null) {
            if (isLeftChild(p)) {
                g.left = x;
            } else {
                g.right = x;
            }
        } else {
            x.pathParent = p.pathParent;
            p.pathParent = null;
        }
        x.parent = g;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.print(new Solution().process(in.nextInt(), in.nextInt(),
                in.nextInt(), in.nextInt(), in.nextInt()));
    }
}