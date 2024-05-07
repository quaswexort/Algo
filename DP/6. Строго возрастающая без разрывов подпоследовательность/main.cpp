import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws IOException {

        FastScanner scanner = new FastScanner("input.txt");
        int n = scanner.nextInt();

        long[] initArr = new long[n];

        long[] subsequences = new long[n];

        for (int i = 0; i < n; ++i) {
            initArr[i] = scanner.nextLong();
            subsequences[i] = Long.MAX_VALUE;
        }

        subsequences[0] = initArr[0];

        int upperBound = 0;

        int j;
        for (int i = 1; i < n; ++i) {
            j = Arrays.binarySearch(subsequences, initArr[i]);
            if(j < 0) {
                j = -(j + 1);
            }
            subsequences[j] = initArr[i];
            if(j > upperBound) ++upperBound;
        }

        PrintWriter writer = new PrintWriter("output.txt");
        writer.print(upperBound + 1);
        writer.close();
    }
}

class FastScanner {
    BufferedReader reader;
    StringTokenizer tokenizer;

    public FastScanner(String fileName) throws IOException {
        reader = new BufferedReader(new FileReader(fileName));
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

    public long nextLong() throws IOException {
        return Long.parseLong(next());
    }
}
