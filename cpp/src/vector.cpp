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
  a_ = GetInitializedArray(capacity_);
}

Vector::Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_) {
  a_ = GetInitializedArray(capacity_);
  for (size_t i=0 ; i<size_ ; ++i) {
    a_[i] = other[i];
  }
}

Vector::Vector(Vector&& other) : a_(other.a_), size_(other.size_), capacity_(other.capacity_) {
  other.a_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

Vector::~Vector() {
  delete[] a_;
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
  return Iterator(a_);
}

Vector::Iterator Vector::end() const {
  return Iterator(a_ + size_);
}

void Vector::Print() const {
  for (size_t i=0 ; i<size_ ; ++i) {
    std::cout << a_[i] << ", ";
  }
  std::cout << std::endl;
}

void Vector::PushBack(int elem) {
  if (size_ == capacity_) {
    capacity_ *= 2;
    int* tmp = GetInitializedArray(capacity_);
    for (size_t i=0 ; i<size_ ; ++i) {
      tmp[i] = a_[i];
    }
    delete[] a_;
    a_ = tmp;
  }
  a_[size_++] = elem;
}

void Vector::Resize(size_t size) {
  if (size > capacity_) {
    while (size > capacity_) {
      capacity_ *= 2;
    }
    int* tmp = GetInitializedArray(capacity_);
    for (size_t i=0 ; i<size_ ; ++i) {
      tmp[i] = a_[i];
    }
    delete[] a_;
    a_ = tmp;
  }
  size_ = size;
}

size_t Vector::Size() const {
  return size_;
}

Vector& Vector::operator=(const Vector& other) {
  if (this != &other) {
    delete[] a_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    a_ = GetInitializedArray(capacity_);
    for (size_t i=0 ; i<size_ ; ++i) {
      a_[i] = other[i];
    }
  }
  return *this;
}

Vector& Vector::operator=(Vector&& other) {
  if (this != &other) {
    delete[] a_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    a_ = other.a_;

    other.a_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }
  return *this;
}

int& Vector::operator[](size_t i) {
  return a_[i];
}

const int& Vector::operator[](size_t i) const {
  return a_[i];
}