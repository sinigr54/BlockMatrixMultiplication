#include <fmt/printf.h>
#include "matrix/multiplier/algorithm/parallel_outer_algorithm.h"
#include <matrix/multiplier/algorithm/parallel_inner_algorithm.h>
#include <matrix/multiplier/algorithm/native_algorithm.h>
#include "matrix/multiplier/matrix_multiplier.h"

using std::vector;

using fmt::print;

int main() {
    int MATRIX_DIMENSION = 2880;

    vector<int> BLOCK_SIZES = {
            6, 10, 15, 20, 24, 30, 36, 40, 60,
            72, 80, 96, 120, 144, 160, 180, 240, 360, 480, 720
    };

    const int P = 4;
    omp_set_num_threads(P);

    matrix<int> m1(MATRIX_DIMENSION);
    matrix<int> m2(MATRIX_DIMENSION);

    m1.fill();
    m2.fill();

    matrix_multiplier<int, native_multiplier> multiplier1{};
    matrix_multiplier<int, parallel_inner_algorithm> multiplier2{};
    matrix_multiplier<int, parallel_outer_algorithm> multiplier3{};

    for (int i : BLOCK_SIZES) {
        print("Block size: {}\n", i);

        auto b_m1 = m1.to_block_matrix(80);
        auto b_m2 = m2.to_block_matrix(80);

        auto start_time = omp_get_wtime();
        multiplier1.multiply(b_m1, b_m2);
        auto end_time = omp_get_wtime() - start_time;

        print("{}\n", end_time);

        start_time = omp_get_wtime();
        multiplier2.multiply(b_m1, b_m2);
        end_time = omp_get_wtime() - start_time;

        print("Time inner: {}\n", end_time);

        start_time = omp_get_wtime();
        multiplier3.multiply(b_m1, b_m2);
        end_time = omp_get_wtime() - start_time;

        print("Time outer: {}\n", end_time);
    }

    return 0;
}