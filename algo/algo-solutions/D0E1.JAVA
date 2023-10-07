import java.io.*;
import java.util.*;
import java.lang.reflect.Array;

public class Solution {
    public static void main(String[] args) throws Exception {
        new Solution().doSQL();
    }

    private void doSQL() throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        while (true) {
            String query = in.readLine();
            if (query == null) {
                break;
            }
            query = query.trim();
            if (query.isEmpty()) {
                break;
            }
            query = query.substring(0, query.length() - 1);
            query = query.trim().toLowerCase().replaceAll("\\s{2,}", " ").trim();
            List<String> tokens = new ArrayList<>();
            char[] queryChars = query.toCharArray();
            StringBuilder curToken = new StringBuilder();
            for (int i = 0; i < queryChars.length; i++) {
                if (i == 0) {
                    curToken.append(queryChars[i]);
                    continue;
                }
                if (queryChars[i] == ' ' || queryChars[i] == ',') {
                    String curS = curToken.toString().trim();
                    if (!curS.isEmpty()) {
                        tokens.add(curS);
                    }
                    curToken = new StringBuilder();
                    continue;
                }
                if (queryChars[i] == '(' || queryChars[i] == ')') {
                    String curS = curToken.toString().trim();
                    if (!curS.isEmpty()) {
                        tokens.add(curS);
                    }
                    tokens.add("" + queryChars[i]);
                    curToken = new StringBuilder();
                    continue;
                }
                curToken.append(queryChars[i]);
                if (i == queryChars.length - 1) {
                    String curS = curToken.toString().trim();
                    if (!curS.isEmpty()) {
                        tokens.add(curS);
                    }
                }
            }
            if (tokens.isEmpty()) {
                break;
            }
            if ("select".equals(tokens.get(0))) {
                executeSelect(tokens, out);
            } else if ("create".equals(tokens.get(0))) {
                executeCreate(tokens);
            } else if ("insert".equals(tokens.get(0))) {
                executeInsert(tokens);
            } else {
                break;
            }
        }
        out.close();
    }

    private void executeSelect(List<String> tokens, PrintWriter out) {
        List<String> what = new ArrayList<>();
        List<String> from = new ArrayList<>();
        List<String> where = new ArrayList<>();
        boolean isWhat = false;
        boolean isFrom = false;
        boolean isWhere = false;
        for (String t : tokens) {
            if ("select".equals(t)) {
                isWhat = true;
                continue;
            }
            if ("from".equals(t)) {
                isWhat = false;
                isFrom = true;
                continue;
            }
            if ("where".equals(t)) {
                isFrom = false;
                isWhere = true;
                continue;
            }
            if (isWhat) {
                what.add(t);
            }
            if (isFrom) {
                from.add(t);
            }
            if (isWhere) {
                where.add(t);
            }
        }
        Table cart = null;
        if (from.size() == 1) {
            cart = oneTableCartesian(tables.get(from.get(0)));
        }
        if (from.size() == 2) {
            cart = twoTablesCartesian(tables.get(from.get(0)), tables.get(from.get(1)));
        }
        if (from.size() == 3) {
            cart = threeTablesCartesian(tables.get(from.get(0)), tables.get(from.get(1)), tables.get(from.get(2)));
        }
        if (cart == null) {
            return;
        }
        List<Integer> columnsToSelect = new ArrayList<>();
        for (String w : what) {
            for (int i = 0; i < cart.getQHeaders().size(); i++) {
                String qHeader = cart.getQHeaders().get(i);
                if (w.equals(qHeader)) {
                    columnsToSelect.add(i);
                }
            }
        }
        List<List<String>> orConditions = new ArrayList<>();
        orConditions.add(new ArrayList<>());
        for (String w : where) {
            if ("or".equals(w)) {
                orConditions.add(new ArrayList<>());
                continue;
            }
            int last = orConditions.size() - 1;
            orConditions.get(last).add(w);
        }
        List<List<List<String>>> andOrConditions = new ArrayList<>();
        for (List<String> oc : orConditions) {
            andOrConditions.add(new ArrayList<>());
            int lastOr = andOrConditions.size() - 1;
            andOrConditions.get(lastOr).add(new ArrayList<>());
            for (String w : oc) {
                if ("and".equals(w)) {
                    andOrConditions.get(lastOr).add(new ArrayList<>(new ArrayList<>()));
                    continue;
                }
                andOrConditions.get(lastOr).get(andOrConditions.get(lastOr).size() - 1).add(w);
            }
        }
        Map<String, Integer> qHeader2ColNum = new HashMap<>();
        for (int i = 0; i < cart.getQHeaders().size(); i++) {
            qHeader2ColNum.put(cart.getQHeaders().get(i), i);
        }
        final int Q = columnsToSelect.size();
        List<String[]> z = new ArrayList<>();
        for (String[] row : cart.getData()) {
            if (checkCondition(andOrConditions, row, qHeader2ColNum)) {
                String[] x = new String[Q];
                for (int i = 0; i < Q; i++) {
                    x[i] = row[columnsToSelect.get(i)];
                }
                z.add(x);
            }
        }
        z.sort((o1, o2) -> {
            int res = 0;
            for (int i = 0; i < Q; i++) {
                res = o1[i].compareTo(o2[i]);
                if (res != 0) {
                    break;
                }
            }
            return res;
        });
        for (String[] row : z) {
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < Q; i++) {
                sb.append(row[i]).append(" ");
            }
            out.println(sb.toString().trim());
        }
        out.println("---");
        out.flush();
    }

    private boolean checkCondition(List<List<List<String>>> andOrConditions,
                                   String[] row,
                                   Map<String, Integer> qHeader2ColNum) {
        boolean resultOr = false;
        for (List<List<String>> andConditions : andOrConditions) {
            boolean resultAnd = true;
            for (List<String> andCondition : andConditions) {
                int col1 = qHeader2ColNum.get(andCondition.get(0));
                int col2 = qHeader2ColNum.get(andCondition.get(2));
                resultAnd = (row[col1].equals(row[col2]));
                if (!resultAnd) {
                    break;
                }
            }
            resultOr = resultAnd;
            if (resultOr) {
                break;
            }
        }
        return resultOr;
    }

    private void executeCreate(List<String> tokens) {
        List<String> headers = new ArrayList<>();
        boolean isHeader = false;
        for (String t : tokens) {
            if (")".equals(t)) {
                isHeader = false;
            }
            if (isHeader) {
                headers.add(t);
            }
            if ("(".equals(t)) {
                isHeader = true;
            }
        }
        String tableName = tokens.get(2);
        Table t = new Table(tableName, headers);
        tables.put(tableName, t);
    }

    private void executeInsert(List<String> tokens) {
        List<String> newData = new ArrayList<>();
        boolean isData = false;
        for (String t : tokens) {
            if (")".equals(t)) {
                isData = false;
            }
            if (isData) {
                newData.add(t.substring(1, t.length() - 1));
            }
            if ("(".equals(t)) {
                isData = true;
            }
        }
        String tableName = tokens.get(2);
        String[] newDataRow = newData.toArray(new String[0]);
        tables.get(tableName).insert(newDataRow);
    }

    private Map<String, Table> tables = new HashMap<>();

    class Table {
        private String name;
        private List<String> headers;
        private List<String> qHeaders;
        private List<String[]> data;

        Table(String name, List<String> headers) {
            this.name = name;
            this.headers = headers;
            this.qHeaders = new ArrayList<>(headers.size());
            for (String header : headers) {
                qHeaders.add(String.format("%s.%s", name, header));
            }
            this.data = new ArrayList<>();
        }

        Table(String name, List<String> headers, List<String> qHeaders) {
            this.name = name;
            this.headers = headers;
            this.qHeaders = qHeaders;
            this.data = new ArrayList<>();
        }

        void insert(String[] newDataRow) {
            data.add(newDataRow);
        }

        String getName() {
            return name;
        }

        List<String[]> getData() {
            return data;
        }

        List<String> getHeaders() {
            return headers;
        }

        List<String> getQHeaders() {
            return qHeaders;
        }
    }

    private Table oneTableCartesian(Table table1) {
        List<String> headers = new ArrayList<>(table1.getHeaders());
        List<String> qHeaders = new ArrayList<>(table1.getQHeaders());
        Table cart = new Table(String.format("#%s", table1.getName()), headers, qHeaders);
        int rc1 = table1.getData().size();
        for (int i = 0; i < rc1; i++) {
            String[] nxt = concatOneArray(table1.getData().get(i));
            cart.insert(nxt);
        }
        return cart;
    }

    private Table twoTablesCartesian(Table table1, Table table2) {
        List<String> headers = new ArrayList<>();
        headers.addAll(table1.getHeaders());
        headers.addAll(table2.getHeaders());
        List<String> qHeaders = new ArrayList<>();
        qHeaders.addAll(table1.getQHeaders());
        qHeaders.addAll(table2.getQHeaders());
        Table cart = new Table(String.format("#%s#%s", table1.getName(), table2.getName()), headers, qHeaders);
        int rc1 = table1.getData().size();
        int rc2 = table2.getData().size();
        for (int i = 0; i < rc1; i++) {
            for (int j = 0; j < rc2; j++) {
                String[] nxt = concatTwoArrays(table1.getData().get(i), table2.getData().get(j));
                cart.insert(nxt);
            }
        }
        return cart;
    }

    private Table threeTablesCartesian(Table table1, Table table2, Table table3) {
        List<String> headers = new ArrayList<>();
        headers.addAll(table1.getHeaders());
        headers.addAll(table2.getHeaders());
        headers.addAll(table3.getHeaders());
        List<String> qHeaders = new ArrayList<>();
        qHeaders.addAll(table1.getQHeaders());
        qHeaders.addAll(table2.getQHeaders());
        qHeaders.addAll(table3.getQHeaders());
        Table cart = new Table(String.format("#%s#%s#%s", table1.getName(), table2.getName(), table3.getName()), headers, qHeaders);
        int rc1 = table1.getData().size();
        int rc2 = table2.getData().size();
        int rc3 = table3.getData().size();
        for (int i = 0; i < rc1; i++) {
            for (int j = 0; j < rc2; j++) {
                for (int k = 0; k < rc3; k++) {
                    String[] nxt = concatThreeArrays(table1.getData().get(i), table2.getData().get(j), table3.getData().get(k));
                    cart.insert(nxt);
                }

            }
        }
        return cart;
    }

    private String[] concatOneArray(String[] a) {
        int aLen = a.length;
        String[] b = (String[]) Array.newInstance(String.class, aLen);
        System.arraycopy(a, 0, b, 0, aLen);
        return b;
    }

    private String[] concatTwoArrays(String[] a, String[] b) {
        int aLen = a.length;
        int bLen = b.length;
        String[] c = (String[]) Array.newInstance(String.class, aLen + bLen);
        System.arraycopy(a, 0, c, 0, aLen);
        System.arraycopy(b, 0, c, aLen, bLen);
        return c;
    }

    private String[] concatThreeArrays(String[] a, String[] b, String[] c) {
        int aLen = a.length;
        int bLen = b.length;
        int cLen = c.length;
        String[] d = (String[]) Array.newInstance(String.class, aLen + bLen + cLen);
        System.arraycopy(a, 0, d, 0, aLen);
        System.arraycopy(b, 0, d, aLen, bLen);
        System.arraycopy(c, 0, d, aLen + bLen, cLen);
        return d;
    }
}