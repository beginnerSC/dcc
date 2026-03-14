#ifndef DCC_CORE_VECTOR_H
#define DCC_CORE_VECTOR_H

class Vector {
  int* a_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 10;
  int* GetInitializedArray(size_t capacity) const;
public:
  Vector() : Vector(0) {}
  Vector(size_t size);
  Vector(const Vector& other);
  Vector(Vector&& other);
  ~Vector();

  class Iterator {
    int* ptr_ = nullptr;
  public:
    explicit Iterator(int* ptr) : ptr_(ptr) {}
    int& operator*() const;
    int* operator->() const;  
    Iterator& operator++();
    Iterator operator++(int);
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;
  };

  Iterator begin() const;
  Iterator end() const;
  void Print() const;
  void PushBack(int elem);
  void Resize(size_t size);
  size_t Size() const;
  Vector& operator=(const Vector& other);
  Vector& operator=(Vector&& other);
  int& operator[](size_t i);                // called when the Vector object is not const
  const int& operator[](size_t i) const;    // called when the Vector object is const
};

#endif 
