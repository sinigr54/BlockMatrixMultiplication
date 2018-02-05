//
// Created by sinigr on 1/28/18.
//

#ifndef MATRIXMUL_BLOCKMATRIX_H
#define MATRIXMUL_BLOCKMATRIX_H

#include <vector>
#include <fmt/printf.h>
#include <matrix/matrix.h>
#include <omp.h>

using std::vector;
using fmt::print;

template<typename T>
class matrix;

template<typename T>
class block_matrix {
    int number_elements{};
    int block_size{};
    int dimension{};
    int number_block_rows{};
    int number_block_columns{};
    int blocks_count{};
    T *data_;

    void initialize_data(const matrix<T> &m);

public:
    block_matrix() = delete;

    block_matrix(const matrix<T> &m, int block_size);

    ~block_matrix();

    inline int get_dimension() const;

    inline int get_block_size() const;

    int get_blocks_count() const;

    int get_index(int i, int j) const;

    inline int get_number_block_rows() const;

    inline int get_number_block_columns() const;

    inline T operator()(int i, int j) const;

    inline T operator[](int i) const;

    template<typename U>
    friend std::ostream &operator<<(std::ostream &os, const block_matrix<U> &m);
};

template<typename T>
block_matrix<T>::block_matrix(const matrix<T> &m, int block_size):
        block_size(block_size),
        dimension(m.rows_count()),
        number_elements(m.size()),
        number_block_rows(m.rows_count() / block_size),
        number_block_columns(m.columns_count() / block_size),
        blocks_count(number_block_rows * number_block_columns) {

    initialize_data(m);
}

template<typename T>
void block_matrix<T>::initialize_data(const matrix<T> &m) {
    data_ = new T[number_elements];

    int block_row_size = m.rows_count() / number_block_rows;
    int block_column_size = m.columns_count() / number_block_columns;

    int index = 0;

    for (int s = 0; s < number_block_rows; ++s) {
        for (int q = 0; q < number_block_columns; ++q) {
            for (int row = 0; row < block_row_size; ++row) {
                int i = s * block_row_size + row;
                for (int column = 0; column < block_column_size; ++column) {
                    int j = q * block_column_size + column;
                    data_[index++] = m(i, j);
                }
            }
        }
    }
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const block_matrix<T> &m) {
    for (int i = 0; i < m.number_elements; ++i) {
        os << m.data_[i] << " ";
    }

    return os;
}

template<typename T>
block_matrix<T>::~block_matrix() {
    delete[] data_;
}

template<typename T>
int block_matrix<T>::get_number_block_rows() const {
    return number_block_rows;
}

template<typename T>
int block_matrix<T>::get_number_block_columns() const {
    return number_block_columns;
}

template<typename T>
int block_matrix<T>::get_block_size() const {
    return block_size;
}

template<typename T>
int block_matrix<T>::get_dimension() const {
    return dimension;
}

template<typename T>
T block_matrix<T>::operator()(int i, int j) const {
    return data_[get_index(i, j)];
}

template<typename T>
int block_matrix<T>::get_blocks_count() const {
    return blocks_count;
}

template<typename T>
T block_matrix<T>::operator[](int i) const {
    return data_[i];
}

template<typename T>
int block_matrix<T>::get_index(int i, int j) const {
    int block_items_count = block_size * block_size;

    int index_i = i % number_block_rows;
    int index_j = j % number_block_columns;

    int index = index_i * block_items_count * number_block_rows + index_j * block_items_count;

    return index;
}

#endif //MATRIXMUL_BLOCKMATRIX_H
