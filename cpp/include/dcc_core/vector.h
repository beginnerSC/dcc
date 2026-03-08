#ifndef DCC_CORE_VECTOR_H
#define DCC_CORE_VECTOR_H

class Vector {
private:
  int* a_;
  size_t size_;
  size_t capacity_;

  int* GetInitializedArray(size_t capacity);

public:
  Vector();
  explicit Vector(int size);
  Vector(const Vector& other);
  Vector(Vector&& other);
  ~Vector();

  class Iterator {
    int* ptr_;

  public:
    explicit Iterator(int* ptr) noexcept;
    int& operator*() const noexcept;
    int* operator->() const noexcept;
    Iterator& operator++() noexcept;
    Iterator operator++(int) noexcept;
    bool operator==(Iterator other) const noexcept;
    bool operator!=(Iterator other) const noexcept;
  };

  Iterator begin() const noexcept;
  Iterator end() const noexcept;
  void Print();
  void PushBack(const int& val);
  void Resize(const size_t& size);
  size_t Size() const noexcept;
  Vector& operator=(const Vector& other) noexcept;
  Vector& operator=(Vector&& other) noexcept;
  int& operator[](size_t i) noexcept;
  const int& operator[](size_t i) const noexcept;
};

#endif