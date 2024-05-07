import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws IOException {

        FastScanner scanner = new FastScanner("in.txt");

        int pD = scanner.nextInt();
        int pI = scanner.nextInt();
        int pR = scanner.nextInt();

        String strA = scanner.nextLine();
        int lengthA = strA.length();
        char[] strAarr = strA.toCharArray();

        String strB = scanner.nextLine();
        int lengthB = strB.length();
        char[] strBarr = strB.toCharArray();

        int[][] F = new int[lengthA + 1][lengthB + 1];

        for (int i = 0; i <= lengthB; ++i) {
            F[0][i] = i * pI;
        }
        for (int i = 0; i <= lengthA; ++i) {
            F[i][0] = i * pD;
        }

        for (int i = 1; i <= lengthA; ++i) {
            for (int j = 1; j <= lengthB; ++j) {
                int r = (strAarr[i - 1] == strBarr[j - 1] ? 0 : 1);
                F[i][j] = Math.min(Math.min(F[i - 1][j] + pD, F[i][j - 1] + pI), F[i - 1][j - 1] + pR * r);
            }
        }

        PrintWriter writer = new PrintWriter("out.txt");
        writer.print(F[lengthA][lengthB]);
        writer.close();
    }
}

class FastScanner {
    BufferedReader reader;
    private StringTokenizer tokenizer;

    public FastScanner(String fileName) throws IOException {
        reader = new BufferedReader(new FileReader(fileName));
    }

    public String nextLine() throws IOException {
        return reader.readLine();
    }

    public String next() throws IOException {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            String line = reader.readLine();
            if (line == null) {
                return null;
            }
            tokenizer = new StringTokenizer(line);
        }
        return tokenizer.nextToken();
    }

    public int nextInt() throws IOException {
        return Integer.parseInt(next());
    }
}
