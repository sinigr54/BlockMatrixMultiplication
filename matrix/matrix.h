//
// Created by sinigr on 1/28/18.
//

#ifndef MATRIXMUL_MATRIX_H
#define MATRIXMUL_MATRIX_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <fmt/printf.h>
#include <random>
#include "block_matrix.h"

using std::vector;

template<typename T>
class block_matrix;

template<typename T>
class matrix {
    T **data_;
    int rows;
    int columns;

public:
    matrix() = delete;

    matrix(int n);

    matrix(int m, int n);

    matrix(const matrix &another);

    ~matrix();

    block_matrix<T> to_block_matrix(int block_size);

    void fill();

    void fill(const vector<vector<T>> &items);

    inline int size() const;

    inline int rows_count() const;

    inline int columns_count() const;

    inline T operator()(int row, int column) const;

    inline T &operator()(int row, int column);

    template<typename U>
    friend std::ostream &operator<<(std::ostream &os, const matrix<U> &m);
};

template<typename T>
matrix<T>::matrix(int n): matrix(n, n) {

}


template<typename T>
matrix<T>::matrix(int m, int n): rows(m), columns(n) {
    data_ = new T *[rows];
    for (int i = 0; i < rows; ++i) {
        data_[i] = new T[columns];
    }
}

template<typename T>
matrix<T>::matrix(const matrix &another): data_(new T *[another.rows_count()]),
                                          rows(another.rows),
                                          columns(another.columns) {

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            data_[i][j] = another(i, j);
        }
    }
}

template<typename T>
int matrix<T>::rows_count() const {
    return rows;
}

template<typename T>
int matrix<T>::columns_count() const {
    return columns;
}

template<typename T>
T matrix<T>::operator()(int row, int column) const {
    return data_[row][column];
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const matrix<T> &m) {
    for (int i = 0; i < m.rows_count(); ++i) {
        for (int j = 0; j < m.columns_count(); ++j) {
            os << m(i, j) << " ";
        }

        os << "\n";
    }

    return os;
}

template<typename T>
matrix<T>::~matrix() {
    for (int i = 0; i < rows; ++i) {
        delete[] data_[i];
    }

    delete[] data_;
}

template<typename T>
void matrix<T>::fill() {
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(1, 100);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            data_[i][j] = distribution(generator);
        }
    }
}

template<typename T>
void matrix<T>::fill(const vector<vector<T>> &items) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            data_[i][j] = items[i][j];
        }
    }
}

template<typename T>
block_matrix<T> matrix<T>::to_block_matrix(int block_size) {
    return block_matrix<T>(*this, block_size);
}

template<typename T>
int matrix<T>::size() const {
    return rows * columns;
}

template<typename T>
T &matrix<T>::operator()(int row, int col) {
    return data_[row][col];
}

#endif //MATRIXMUL_MATRIX_H
