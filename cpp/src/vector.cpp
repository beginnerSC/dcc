#include "dcc_core/vector.h"
#include <iostream>

int* Vector::GetInitializedArray(size_t capacity) const {
  int* res = new int[capacity];
  for (size_t i=0 ; i<capacity ; ++i) {
    res[i] = 0;
  }
  return res;
}

Vector::Vector(size_t size) : size_(size) {
  while (size_ > capacity_) {
    capacity_ *= 2;
  }
  data_ = GetInitializedArray(capacity_);
}

Vector::Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_) {
  data_ = GetInitializedArray(capacity_);
  for (size_t i=0 ; i<size_ ; ++i) {
    data_[i] = other[i];
  }
}

Vector::Vector(Vector&& other) : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
  other.data_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

Vector::~Vector() {
  delete[] data_;
}

int& Vector::Iterator::operator*() const {
  return *ptr_;
}

int* Vector::Iterator::operator->() const {
  return ptr_;
}

Vector::Iterator& Vector::Iterator::operator++() {
  ++ptr_;
  return *this;
}

Vector::Iterator Vector::Iterator::operator++(int) {
  Iterator tmp = *this;
  ++(*this);
  return tmp;
}

bool Vector::Iterator::operator==(const Iterator& other) const {
  return (ptr_ == other.ptr_);
}

bool Vector::Iterator::operator!=(const Iterator& other) const {
  return (ptr_ != other.ptr_);
}

Vector::Iterator Vector::begin() const {
  return Iterator(data_);
}

Vector::Iterator Vector::end() const {
  return Iterator(data_ + size_);
}

void Vector::Print() const {
  for (size_t i=0 ; i<size_ ; ++i) {
    std::cout << data_[i] << ", ";
  }
  std::cout << std::endl;
}

void Vector::PushBack(int elem) {
  if (size_ == capacity_) {
    capacity_ *= 2;
    int* tmp = GetInitializedArray(capacity_);
    for (size_t i=0 ; i<size_ ; ++i) {
      tmp[i] = data_[i];
    }
    delete[] data_;
    data_ = tmp;
  }
  data_[size_++] = elem;
}

void Vector::Resize(size_t size) {
  if (size > capacity_) {
    while (size > capacity_) {
      capacity_ *= 2;
    }
    int* tmp = GetInitializedArray(capacity_);
    for (size_t i=0 ; i<size_ ; ++i) {
      tmp[i] = data_[i];
    }
    delete[] data_;
    data_ = tmp;
  }
  size_ = size;
}

size_t Vector::Size() const {
  return size_;
}

Vector& Vector::operator=(const Vector& other) {
  if (this != &other) {
    size_ = other.size_;
    capacity_ = other.capacity_;

    delete[] data_;
    data_ = GetInitializedArray(capacity_);
    for (size_t i=0 ; i<size_ ; ++i) {
      data_[i] = other[i];
    }
  }
  return *this;
}

Vector& Vector::operator=(Vector&& other) {
  if (this != &other) {
    delete[] data_;
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }
  return *this;
}

int& Vector::operator[](size_t i) {
  return data_[i];
}

const int& Vector::operator[](size_t i) const {
  return data_[i];
}