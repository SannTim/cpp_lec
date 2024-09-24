#include <array>
#include <iostream>

template <int N>
constexpr int Det(const std::array<std::array<int, N>, N>& matrix) {
    // Базовый случай для матрицы 1x1
    if constexpr (N == 1) {
        return matrix[0][0];
    } else {
        int determinant = 0;
        for (int col = 0; col < N; ++col) {
            std::array<std::array<int, N - 1>, N - 1> submatrix = {};
            
            for (int i = 1; i < N; ++i) {
                int sub_col = 0;
                for (int j = 0; j < N; ++j) {
                    if (j == col) continue;
                    submatrix[i - 1][sub_col] = matrix[i][j];
                    ++sub_col;
                }
            }
            int sign = (col % 2 == 0) ? 1 : -1;
            determinant += sign * matrix[0][col] * Det<N - 1>(submatrix);
        }

        return determinant;
    }
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

