#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    std::ifstream in("input.txt");

    int n = 0;
    int *matrix_sizes;

    if (in.is_open()) {
        std::string line;
        getline(in, line);

        n = stoi(line);

        matrix_sizes = new int[n + 1];

        std::string item;
        std::stringstream s;

        getline(in, line);
        s << line;
        s >> item;

        int ind = 0;

        matrix_sizes[ind++] = stoi(item);
        s >> item;
        matrix_sizes[ind++] = stoi(item);

        s.clear();

        while (getline(in, line)) {
            s << line;
            s >> item >> item;
            matrix_sizes[ind++] = stoi(item);
            s.clear();
        }
    }
    in.close();

    int table[n][n];

    for (int i = 0; i < n; ++i) {
        table[i][i] = 0;
    }

    for (int j = 1; j < n; ++j) {
        for (int i = j - 1; i >= 0; --i) {
            table[i][j] = INT_MAX;
            for (int k = i; k < j; ++k) {
                table[i][j] = std::min(table[i][j],
                                       table[i][k] + table[k + 1][j]
                                       + matrix_sizes[i] * matrix_sizes[k + 1] * matrix_sizes[j + 1]);
            }
        }
    }

    std::ofstream out;
    out.open("output.txt");
    if (out.is_open()) {
        out << table[0][n - 1];
    }

    return 0;
}
