#ifndef DCC_CORE_DENSE_MATRIX_H
#define DCC_CORE_DENSE_MATRIX_H

#include <vector>

class DenseMatrix {
    std::vector<std::vector<double>> data_;
    size_t col_ = 0;
    size_t row_ = 0;
public:
    DenseMatrix(size_t col, size_t row): col_(col), row_(row) {
        data_ = std::vector<std::vector<double>>(col_, std::vector<double>(row_, 0));
    } 
    DenseMatrix(const DenseMatrix& other) : data_(other.data_), col_(other.col_), row_(other.row_) {}
    DenseMatrix(DenseMatrix&& other) : data_(std::move(ther.data_)), col_(other.col_), row_(other.row_) {}
};

#endif