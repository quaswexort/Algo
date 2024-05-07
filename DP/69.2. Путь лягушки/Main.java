import java.util.Scanner;

public class Main {
    public static void main(String[] args) {

        Scanner in = new Scanner(System.in);

        int n = in.nextInt();

        int[] a = new int[n];
        int[] F = new int[n];
        int[] b = new int[n];

        int tmp;

        for (int i = 0; i < n; ++i) {
            a[i] = in.nextInt();
        }

        if (n == 1) {
            System.out.println(a[0]);
            System.out.print(1);
        } else if (n == 2) {
            System.out.print(-1);
        } else if (n == 3) {
            System.out.println(a[0] + a[2]);
            System.out.print(1 + " " + 3);
        } else if (n == 4) {
            System.out.println(a[0] + a[3]);
            System.out.print(1 + " " + 4);
        } else if (n == 5) {
            System.out.println(a[0] + a[2] + a[4]);
            System.out.print(1 + " " + 3 + " " + 5);
        } else if (n > 5) {
            F[0] = a[0];
            F[1] = -1;
            F[2] = a[0] + a[2];
            F[3] = a[0] + a[3];
            F[4] = a[0] + a[2] + a[4];

            b[0] = n;

            for (int i = 5; i < n; ++i) {
                tmp = Math.max(F[i - 2], F[i - 3]);
                F[i] = a[i] + tmp;
            }

            int j = 1;
            for (int i = n - 1; i > 3; j++) {
                if (F[i] - F[i - 2] == a[i]) {
                    b[j] = i - 1;
                    i = i - 2;
                } else {
                    b[j] = i - 2;
                    i = i - 3;
                }
            }

            b[j] = 1;

            System.out.println(F[n - 1]);

            for (int i = j; i >= 0; --i) {
                System.out.print(b[i] + " ");
            }
        }
    }
}
