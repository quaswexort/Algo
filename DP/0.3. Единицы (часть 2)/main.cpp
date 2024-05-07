import java.util.Scanner;

public class Main {

    private final static int MOD = 1000000007;

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);
        long n = scanner.nextLong();
        long k = scanner.nextLong();

        // C(n)(k) = n! / (k! * (n - k)!)
        long num = factorial(n - k + 1, n);
        long denom = factorial(1, k);

        long res = (num * binPow(denom, MOD - 2, MOD)) % MOD;

        System.out.println(res);
    }

    private static long factorial(long from, long to) {
        long res = 1;
        for (long i = from; i <= to; ++i) {
            res = (res * i) % MOD;
        }
        return res;
    }

    private static long binPow(long x, long n, long mod) {
        if (n == 0) return 1;
        if (n % 2 == 0) {
            long res = binPow(x, n / 2, mod);
            return (res * res) % mod;
        } else return (binPow(x, n - 1, mod) * x) % mod;
    }
}
