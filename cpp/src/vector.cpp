#include "dcc_core/vector.h"

// Helper method to allocate and initialize array
int* Vector::GetInitializedArray(size_t capacity) {
  int* res = new int[capacity];
  for (size_t i = 0; i < capacity; ++i) {
    res[i] = 0;
  }
  return res;
}

// Default constructor
Vector::Vector() : Vector(0) {}

// Constructor with size
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

// Copy constructor
Vector::Vector(const Vector& other) : a_(nullptr), size_(0), capacity_(0) {
  size_ = other.size_;
  capacity_ = other.capacity_;
  a_ = GetInitializedArray(other.capacity_);
  for (size_t j = 0; j < size_; ++j) {
    a_[j] = other[j];
  }
}

// Move constructor
Vector::Vector(Vector&& other) : a_(other.a_), size_(other.size_), capacity_(other.capacity_) {
  other.a_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

// Destructor
Vector::~Vector() { delete[] a_; }

// Iterator constructor
Vector::iterator::iterator(int* ptr) noexcept : ptr_(ptr) {}

// Iterator dereference operator
int& Vector::iterator::operator*() const noexcept { return *ptr_; }

// Iterator arrow operator
int* Vector::iterator::operator->() const noexcept { return ptr_; }

// Iterator pre-increment
Vector::iterator& Vector::iterator::operator++() noexcept {
  ptr_++;
  return *this;
}

// Iterator post-increment
Vector::iterator Vector::iterator::operator++(int) noexcept {
  iterator tmp = *this;
  ptr_++;
  return tmp;
}

// Iterator equality
bool Vector::iterator::operator==(iterator other) const noexcept {
  return (ptr_ == other.GetPtr());
}

// Iterator inequality
bool Vector::iterator::operator!=(iterator other) const noexcept {
  return (ptr_ != other.GetPtr());
}

// Iterator GetPtr
int* Vector::iterator::GetPtr() const noexcept { return ptr_; }

// Iterator begin
Vector::iterator Vector::begin() const noexcept { return iterator(a_); }

// Iterator end
Vector::iterator Vector::end() const noexcept { return iterator(a_ + size_); }

// Print method
void Vector::Print() {
  for (size_t i = 0; i < size_; i++) {
    std::cout << a_[i] << ", ";
  }
  std::cout << std::endl;
}

// PushBack method
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

// Resize method
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

// Size method
size_t Vector::Size() const noexcept { return size_; }

// Copy assignment operator
Vector& Vector::operator=(const Vector& other) noexcept {
  if (this != &other) {
    delete[] a_;  // clean up existing data

    size_ = other.size_;  // copy the data
    capacity_ = other.capacity_;
    a_ = GetInitializedArray(capacity_);
    for (size_t i = 0; i < size_; ++i) {
      a_[i] = other[i];
    }
  }
  return *this;
}

// Move assignment operator
Vector& Vector::operator=(Vector&& other) noexcept {
  if (this != &other) {
    delete[] a_;  // clean up existing data

    size_ = other.size_;  // move the data
    capacity_ = other.capacity_;
    a_ = other.a_;

    other.a_ = nullptr;  // leave other in safe state
    other.size_ = 0;
    other.capacity_ = 0;
  }
  return *this;
}

// Subscript operator
int& Vector::operator[](size_t i) noexcept { return a_[i]; }

// Const subscript operator
const int& Vector::operator[](size_t i) const noexcept { return a_[i]; }
