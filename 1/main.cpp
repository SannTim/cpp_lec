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
    if (N % 2 == 0)
        return -Det<N>(matrix, fullMask, N);
    else 
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
    constexpr std::array<std::array<int, 4>, 4> matrix4 = { {
        {0, 1, 2, 4},
        {1, 2, 3, 7},
        {2, 3, 7, 1},
        {1, 3, 0, -5}
    }};
    constexpr int resultik = Det<4>(matrix4);
    std::cout << resultik << std::endl;
    constexpr std::array<std::array<int, 5>, 5> matrix5 = { {
        {1, 2, 3, 4, 5},
        {-1, 0, 2, 5, 3},
        {1, 2, 2, 4, 6},
        {-3, 1, -2, 4, 3},
        {1, 2, 6, 7, -8}
    }};
    constexpr int resultik5 = Det<5>(matrix5);
    std::cout << resultik5 << std::endl;
    constexpr std::array<std::array<int, 6>, 6> matrix6 = { {
        {1, 2, 3, 4, 5, 1},
        {-1, 0, 2, 5, 3, 2},
        {1, 2, 2, 4, 6, 3},
        {-3, 1, -2, 4, 3, 4},
        {1, 2, 6, 7, -8, 5},
        {1, 2, 2, 4, 6, 6}
    }};
    constexpr int resultik6 = Det<6>(matrix6);
    std::cout << resultik6 << std::endl;
    return 0;
}

