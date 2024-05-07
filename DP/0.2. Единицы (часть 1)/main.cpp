#include <iostream>

int main() {
    int mod = 1000000007;
    int N, K;
    std::cin >> N >> K;

    N++;
    long long arr[N];

    for (int i = 0; i < N; ++i) {
        arr[i] = 1;
    }

    for (int j = 0; j < K; ++j) {
        for (int i = 1; i < N - j; ++i) {
            arr[i] = (arr[i] + arr[i - 1]) % mod;
        }
    }

    std::cout << arr[N - K - 1] % mod;

    return 0;
}
