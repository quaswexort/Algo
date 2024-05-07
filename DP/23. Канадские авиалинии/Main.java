import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws IOException {

        FastScanner scanner = new FastScanner("in.txt");

        int n = scanner.nextInt();
        int m = scanner.nextInt();

        Map<String, Integer> cities = new HashMap<>(n);

        for (int i = 0; i < n; ++i) {
            cities.put(scanner.next(), n - 1 - i);
        }

        ArrayList<ArrayList<Integer>> airlines = new ArrayList<>(n);
        for(int i = 0; i < n; ++i) {
            airlines.add(new ArrayList<>(n - 1));
        }

        String firstCity;
        String secondCity;
        for (int i = 0; i < m; ++i) {
            firstCity = scanner.next();
            secondCity = scanner.next();
            airlines.get(cities.get(firstCity)).add(cities.get(secondCity));
            airlines.get(cities.get(secondCity)).add(cities.get(firstCity));
        }

        int[][] d = new int[n][n];

        d[0][0] = 1;

        for(int i = 1; i < n; ++i) {
            for(int j = 0; j < i; ++j) {
                for(int k : airlines.get(i)) {
                    if(k < i && (k != j || j == 0)) {
                        d[i][j] = Math.max(d[i][j], d[k][j]);
                    }
                }
                if(d[i][j] != 0) {
                    d[i][j] += 1;
                    d[j][i] = d[i][j];
                }
            }
            for(int k : airlines.get(i)) {
                if(k < i) {
                    d[i][i] = Math.max(d[i][i], d[k][i]);
                }
            }
        }

        PrintWriter writer = new PrintWriter("out.txt");
        writer.println(d[n-1][n-1] < 2 && n != 1 ? "No solution" : d[n-1][n-1]);
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
}
