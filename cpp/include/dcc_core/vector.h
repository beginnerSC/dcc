#ifndef DCC_CORE_VECTOR_H
#define DCC_CORE_VECTOR_H

class Vector {
  int* a_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 10;
  
  int* GetInitializedArray(const size_t capacity);

public:
  Vector() : Vector(0) {}
  Vector(size_t size);
  Vector(const Vector& other);
  Vector(Vector&& other);
  ~Vector();

  class Iterator {
    int* ptr_ = nullptr;

  public:
    Iterator(int* ptr) : ptr_(ptr) {}
    int operator*() const;
    int* operator->() const;  
    Iterator& operator++();
    Iterator operator++(int);
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;
  };

  Iterator begin() const;
  Iterator end() const;
  void Print() const;
  void PushBack(int);
  void Resize(size_t size);
  size_t Size() const;
  Vector& operator=(const Vector& other);
  Vector& operator=(Vector&& other);
  int& operator[](size_t idx) const;
};

#endif 
