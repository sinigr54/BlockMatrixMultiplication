//
// Created by sinigr on 1/31/18.
//

#ifndef MATRIXMUL_MATRIX_MULTIPLIER_H
#define MATRIXMUL_MATRIX_MULTIPLIER_H

#include "matrix/matrix.h"
#include "matrix/block_matrix.h"

template<class T,
        template <typename> typename Algorithm>
class matrix_multiplier {
    Algorithm<T> multiplication_algorithm;
public:
    matrix<T> multiply(const block_matrix<T> &m1, const block_matrix<T> &m2);
};

template<class T, template<typename> typename Algorithm>
matrix<T> matrix_multiplier<T, Algorithm>::multiply(const block_matrix<T> &m1, const block_matrix<T> &m2) {
    return multiplication_algorithm.execute(m1, m2);
}


#endif //MATRIXMUL_MATRIX_MULTIPLIER_H
