import java.io.*;
import java.util.*;

public class Solution {
    private static final String EOF = "^Z";
    private static final String NEW_LINE = "\n";
    private static final String BACK = "..";
    private static final String SEP = "\\";

    public static void main(String[] args) throws Exception {
        new Solution().process();
    }

    class File {
        private ArrayDeque<String> path;
        private String fullPath;
        private List<String> data;
        private List<Boolean> isIncludeLine;
        private boolean opened = false;

        File(String[] path) {
            this.path = new ArrayDeque<>();
            this.data = new ArrayList<>();
            this.isIncludeLine = new ArrayList<>();
            for (String p : path) {
                if (BACK.equals(p)) {
                    this.path.pollLast();
                } else {
                    this.path.addLast(p.toLowerCase());
                }
            }
            this.fullPath = String.join(SEP, this.path);
        }

        File(ArrayDeque<String> outerPath, String[] innerPath) {
            if (isAbsolutePath(innerPath)) {
                this.path = new ArrayDeque<>();
            } else {
                this.path = new ArrayDeque<>(outerPath);
                this.path.pollLast();
            }
            for (String p : innerPath) {
                if (BACK.equals(p)) {
                    this.path.pollLast();
                } else {
                    this.path.addLast(p.toLowerCase());
                }
            }
            this.fullPath = String.join(SEP, this.path);
        }

        void addLine(String line) {
            isIncludeLine.add(false);
            data.add(line);
        }

        void addIncludeLine(String line) {
            isIncludeLine.add(true);
            data.add(line);
        }
    }

    private ArrayDeque<File> fileDeque = new ArrayDeque<>();
    private Map<String, File> fileMap = new HashMap<>();
    private List<String> result = new ArrayList<>();
    private BufferedWriter out;

    private boolean isEOF(String line) {
        return EOF.equals(line);
    }

    private boolean isAbsolutePath(String[] path) {
        return path.length >= 2 && path[0].endsWith(":");
    }

    private String[] handleInclude(String line) {
        String leftTrim = line.replaceAll("^\\s+", "");
        if (leftTrim.startsWith("#")) {
            String leftLeftTrim = leftTrim.substring(1).replaceAll("^\\s+", "");
            if (leftLeftTrim.startsWith("include")) {
                String leftLeftLeftTrim = leftLeftTrim.substring(7).replaceAll("^\\s+", "").trim();
                if (leftLeftLeftTrim.startsWith("<") && leftLeftLeftTrim.endsWith(">")) {
                    return leftLeftLeftTrim.substring(1, leftLeftLeftTrim.length() - 1).trim().split("\\\\");
                }
            }
        }
        return null;
    }

    private void rec(String currentFileName) {
        File currentFile = fileMap.get(currentFileName);
        if (currentFile == null) {
            return;
        }
        if (currentFile.opened) {
            try {
                out.write("Too long file");
                out.close();
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
            System.exit(0);
        }
        currentFile.opened = true;
        for (int i = 0; i < currentFile.data.size(); i++) {
            if (Boolean.TRUE.equals(currentFile.isIncludeLine.get(i))) {
                rec(currentFile.data.get(i));
            } else {
                result.add(currentFile.data.get(i));
            }
        }
        currentFile.opened = false;
    }

    private void process() throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
        boolean insideFile = false;
        String line;
        String[] include;
        while ((line = in.readLine()) != null) {
            if (!insideFile) {
                String[] tryPath = line.trim().split("\\\\");
                if (isAbsolutePath(tryPath)) {
                    fileDeque.addLast(new File(tryPath));
                    insideFile = true;
                }
            } else {
                if (isEOF(line)) {
                    insideFile = false;
                } else {
                    if ((include = handleInclude(line)) != null && include.length >= 1 && !"".equals(include[0])) {
                        fileDeque.getLast().addIncludeLine(new File(fileDeque.getLast().path, include).fullPath);
                    } else {
                        fileDeque.getLast().addLine(line);
                    }
                }
            }
        }
        in.close();
        out = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("output.txt")));
        if (!fileDeque.isEmpty()) {
            String firstFileName = fileDeque.peekFirst().fullPath;
            while (!fileDeque.isEmpty()) {
                File f = fileDeque.pollFirst();
                if (f != null) {
                    fileMap.put(f.fullPath, f);
                }
            }
            rec(firstFileName);
            int all = result.size();
            for (int i = 0; i <= all - 1; i++) {
                out.write(result.get(i));
                if (i != all - 1) {
                    out.write(NEW_LINE);
                }
            }
        }
        out.close();
    }
}