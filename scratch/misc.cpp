#include <vector>
#include <utility>
#include <iostream>

class Matrix {
    std::vector<std::vector<double>> data_;
    std::size_t cols_ = 0;
    std::size_t rows_ = 0;
public:
    Matrix(std::size_t rows, std::size_t cols) : cols_(cols), rows_(rows) {
        data_ = std::vector<std::vector<double>>(rows_, std::vector<double>(cols_, 0));
    }
    Matrix(const Matrix& other) : data_(other.data_), cols_(other.cols_), rows_(other.rows_) {}
    Matrix(Matrix&& other) : data_(std::move(other.data_)), cols_(other.cols_), rows_(other.rows_) {}
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            data_ = other.data_;
            cols_ = other.cols_;
            rows_ = other.rows_;
        }
        return *this;
    }
    Matrix& operator=(Matrix&& other) {
        if (this != &other) {
            data_ = std::move(other.data_);
            cols_ = other.cols_;
            rows_ = other.rows_; 

            other.cols_ = 0;
            other.rows_ = 0;
        }
        return *this;
    }
    double& operator()(std::size_t i, std::size_t j) {
        return data_[i][j];
    }
    const double& operator()(std::size_t i, std::size_t j) const {
        return data_[i][j];
    }
    std::size_t rows() const noexcept { 
        return rows_;
    }
    std::size_t cols() const noexcept {
        return cols_;
    }
};

int main() {
    std::cout << "Hey aaa!" << std::endl;
}