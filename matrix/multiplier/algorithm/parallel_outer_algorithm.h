//
// Created by sinigr on 2/3/18.
//

#ifndef MATRIXMUL_PARALLEL_OUTER_ALGORITHM_H
#define MATRIXMUL_PARALLEL_OUTER_ALGORITHM_H

#include <matrix/matrix.h>
#include <matrix/block_matrix.h>

template <class T>
class parallel_outer_algorithm {
    void block_multiply(const block_matrix<T> &m1,
                        const block_matrix<T> &m2,
                        matrix<T> &result_matrix,
                        int i,
                        int j,
                        int block_index,
                        int block_size);

public:
    matrix<T> execute(const block_matrix<T> &m1, const block_matrix<T> &m2);
};

template<class T>
matrix<T> parallel_outer_algorithm<T>::execute(const block_matrix<T> &m1, const block_matrix<T> &m2) {
    matrix<T> result_matrix(m1.get_dimension());

    int blocks_count = m1.get_number_block_rows();
    int block_size = m1.get_block_size();

    for (int i = 0; i < blocks_count; ++i) {
        for (int j = 0; j < blocks_count; ++j) {

            #pragma omp parallel for
            for (int s = 0; s < blocks_count; ++s) {
                block_multiply(m1, m2, result_matrix, i, j, s, block_size);
            }

        }
    }

    return result_matrix;
}

template<class T>
void parallel_outer_algorithm<T>::block_multiply(const block_matrix<T> &m1,
                                                 const block_matrix<T> &m2,
                                                 matrix<T> &result_matrix,
                                                 int i,
                                                 int j,
                                                 int block_index,
                                                 int block_size) {

    int index_m1 = m1.get_index(i, block_index);
    int index_m2 = m2.get_index(block_index, j);

    for (int k = 0; k < block_size; ++k) {
        for (int l = 0; l < block_size; ++l) {
            T sum = 0;
            for (int r = 0; r < block_size; ++r) {
                sum += m1[index_m1 + r + k * block_size] * m2[index_m2 + l + r * block_size];
            }

            #pragma omp atomic
            result_matrix(i * block_size + k, j * block_size + l) += sum;
        }
    }
}

#endif //MATRIXMUL_PARALLEL_OUTER_ALGORITHM_H
