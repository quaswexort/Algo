import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;

public class Main {
    public static void main(String[] args) throws IOException {

        FastScanner scanner = new FastScanner("input.txt");
        String str = scanner.nextLine();

        int n = str.length();

        String[] strArr = str.split("");

        int[][] table = new int[n][n];

        for (int i = 0; i < n; ++i) {
            table[i][i] = 1;
        }

        for (int k = 1; k < n; ++k) {
            for (int i = 0; i < n - k; ++i) {
                int j = i + k;
                if (strArr[i].equals(strArr[j])) {
                    table[i][j] = table[i + 1][j - 1] + 2;
                } else {
                    table[i][j] = Math.max(table[i + 1][j], table[i][j - 1]);
                }
            }
        }

        StringBuilder sb = new StringBuilder();

        int i = 0;
        int j = n - 1;

        int length = table[i][j];

        boolean isEven = true;

        int tmp = length / 2;
        if (length % 2 == 1) {
            tmp++;
            isEven = false;
        }

        while (sb.length() != tmp) {
            if (strArr[i].equals(strArr[j])) {
                sb.append(strArr[i]);
                i++;
                j--;
            } else {
                if (table[i + 1][j] == table[i][j]) {
                    i++;
                } else {
                    j--;
                }
            }
        }

        String res = sb.toString();
        String secondPart = sb.reverse().toString();

        if (!isEven) {
            secondPart = secondPart.substring(1);
        }
        res = res + secondPart;

        PrintWriter writer = new PrintWriter("output.txt");
        writer.println(length);
        writer.print(res);
        writer.close();
    }
}

class FastScanner {
    BufferedReader reader;

    public FastScanner(String fileName) throws IOException {
        reader = new BufferedReader(new FileReader(fileName));
    }

    public String nextLine() throws IOException {
        return reader.readLine();
    }
}
