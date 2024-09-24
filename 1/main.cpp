#include <array>
#include <iostream>

template <int N>
constexpr int Det(const std::array<std::array<int, N>, N>& matrix, int colMask, int size) {
    if (size == 1) {
        int col = 0;
        while (!(colMask & (1 << col))) {
            ++col;
        }
        return matrix[N - size][col];
    }

    int determinant = 0;
    int row = N - size;
    int good_col = 0;
    for (int col = 0; col < N; ++col) {
        if (good_col == size) break;
        if (colMask & (1 << col)) { 
            good_col++;
            int sign = (good_col % 2 == 0) ? 1 : -1;
            determinant += sign * matrix[row][col] * Det<N>(matrix, colMask ^ (1 << col), size - 1);
        }

    }

    return determinant;
}

template <int N>
constexpr int Det(const std::array<std::array<int, N>, N>& matrix) {
    int fullMask = (1 << N) - 1;
    return Det<N>(matrix, fullMask, N);
}


int main() {
    constexpr std::array<std::array<int, 3>, 3> matrix = {{
        {0, 1, 2},
        {1, 2, 3},
        {2, 3, 7}
    }};

    constexpr int result = Det<3>(matrix);
    std::cout << result << std::endl;

    return 0;
}

