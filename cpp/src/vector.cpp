#include "dcc_core/vector.h"
#include <stdexcept>
#include <iostream>

int* Vector::GetInitializedArray(size_t capacity) {
  int* res = new int[capacity];
  for (size_t i = 0; i < capacity; ++i) {
    res[i] = 0;
  }
  return res;
}

Vector::Vector() : Vector(0) {}

Vector::Vector(int size) : a_(nullptr), size_(0), capacity_(10) {
  if (size < 0) {
    throw std::invalid_argument("Size cannot be negative");
  }
  size_ = static_cast<size_t>(size);
  while (capacity_ < size_) {
    capacity_ *= 2;
  }
  a_ = GetInitializedArray(capacity_);
}

Vector::Vector(const Vector& other) : a_(nullptr), size_(0), capacity_(0) {
  size_ = other.size_;
  capacity_ = other.capacity_;
  a_ = GetInitializedArray(other.capacity_);
  for (size_t j = 0; j < size_; ++j) {
    a_[j] = other[j];
  }
}

Vector::Vector(Vector&& other) : a_(other.a_), size_(other.size_), capacity_(other.capacity_) {
  other.a_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

Vector::~Vector() { delete[] a_; }

Vector::Iterator::Iterator(int* ptr) noexcept : ptr_(ptr) {}

int& Vector::Iterator::operator*() const noexcept { return *ptr_; }

int* Vector::Iterator::operator->() const noexcept { return ptr_; }

Vector::Iterator& Vector::Iterator::operator++() noexcept {
  ptr_++;
  return *this;
}

Vector::Iterator Vector::Iterator::operator++(int) noexcept {
  Iterator tmp = *this;
  ptr_++;
  return tmp;
}

bool Vector::Iterator::operator==(Iterator other) const noexcept {
  return (ptr_ == other.ptr_);
}

bool Vector::Iterator::operator!=(Iterator other) const noexcept {
  return (ptr_ != other.ptr_);
}

Vector::Iterator Vector::begin() const noexcept {
  return Iterator(a_); 
}

Vector::Iterator Vector::end() const noexcept { 
  return Iterator(a_ + size_); 
}

void Vector::Print() {
  for (size_t i = 0; i < size_; i++) {
    std::cout << a_[i] << ", ";
  }
  std::cout << std::endl;
}

void Vector::PushBack(const int& val) {
  if (size_ == capacity_) {
    capacity_ *= 2;
    int* tmp = GetInitializedArray(capacity_);
    for (size_t i = 0; i < size_; i++) {
      tmp[i] = a_[i];
    }
    delete[] a_;
    a_ = tmp;
  }
  a_[size_] = val;
  ++size_;
}

void Vector::Resize(const size_t& size) {
  if (size < capacity_) {
    size_ = size;
  } else {
    do {
      capacity_ *= 2;
    } while (capacity_ < size);

    int* tmp = GetInitializedArray(capacity_);

    for (size_t i = 0; i < size_; ++i) {
      tmp[i] = a_[i];
    }
    delete[] a_;
    a_ = tmp;
    size_ = size;
  }
}

size_t Vector::Size() const noexcept { return size_; }

Vector& Vector::operator=(const Vector& other) noexcept {
  if (this != &other) {
    delete[] a_;

    size_ = other.size_;
    capacity_ = other.capacity_;
    a_ = GetInitializedArray(capacity_);
    for (size_t i = 0; i < size_; ++i) {
      a_[i] = other[i];
    }
  }
  return *this;
}

Vector& Vector::operator=(Vector&& other) noexcept {
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

int& Vector::operator[](size_t i) noexcept { return a_[i]; }

const int& Vector::operator[](size_t i) const noexcept { return a_[i]; }
