import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
    public static void findLIS(int[] initArr,
                               int[] previousElements,
                               int[] seqLength) {
        int n = initArr.length;

        int[] subsequences = new int[n];  // subsequences[i] - элемент, на который заканчивается последовательность длины i+1
        int[] lastSubseqIndexes = new int[n];  /* lastSubseqIndexes[i] - индекс элемента,
                                                     на который заканчивается последовательность длины i+1 */

        for (int i = 0; i < n; ++i) {
            subsequences[i] = Integer.MAX_VALUE;
        }

        subsequences[0] = initArr[0];
        lastSubseqIndexes[0] = 0;
        previousElements[0] = -1;
        seqLength[0] = 1;

        int upperBound = 0;

        int j;
        for (int i = 0; i < n; ++i) {
            j = Arrays.binarySearch(subsequences, initArr[i]);
            if (j < 0) {
                j = -(j + 1);
            }
            subsequences[j] = initArr[i];
            lastSubseqIndexes[j] = i;
            seqLength[i] = j + 1;
            if (j != 0)
                previousElements[i] = lastSubseqIndexes[j - 1];
            if (j > upperBound) ++upperBound;
        }
    }

    public static int[] reverse(int[] arr) {
        int n = arr.length;
        int[] res = new int[n];
        for (int i = 0; i < n; ++i) {
            res[n - i - 1] = arr[i];
        }
        return res;
    }

    public static void main(String[] args) throws IOException {

        FastScanner scanner = new FastScanner("report.in");
        int n = scanner.nextInt();

        int[] initArr = new int[n];

        for (int i = 0; i < n; ++i) {
            initArr[i] = scanner.nextInt();
        }

        int[] reversedArr = reverse(initArr);

        int[] previousElements = new int[n];  /* previousElements[i] - индекс элемента, который предшествует
                                                   в искомой подпоследовательности элементу initArr[i] */
        int[] previousElementsReversed = new int[n];

        int[] seqLength = new int[n];  // seqLength[i] - длина последовательности, которая оканчивается на элемент initArr[i]
        int[] seqLengthReversed = new int[n];

        findLIS(initArr, previousElements, seqLength);
        findLIS(reversedArr, previousElementsReversed, seqLengthReversed);

        int finalInd = 0;
        int k = 0;
        int k1, k2;

        int[] result = new int[n];

        for (int i = 0; i < n; ++i) {
            k1 = seqLength[i];
            k2 = seqLengthReversed[n - i - 1];

            int minK = Math.min(k1, k2);
            if (minK > k) {
                k = minK;
                finalInd = i;
            }
        }

        int nextElemInd = finalInd;

        for (int j = 0; j < k; ++j) {
            result[k - 1 - j] = nextElemInd + 1;
            nextElemInd = previousElements[nextElemInd];
        }

        int nextElemIndRev = previousElementsReversed[n - finalInd - 1];

        for (int j = k; j < 2 * k; ++j) {
            if (nextElemIndRev != -1) {
                result[j] = n - nextElemIndRev;
                nextElemIndRev = previousElementsReversed[nextElemIndRev];
            }
        }

        PrintWriter writer = new PrintWriter("report.out");
        writer.println(k - 1);
        k = 2 * (k - 1) + 1;
        for (int i = 0; i < k; ++i) {
            writer.print(result[i] + " ");
        }
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
