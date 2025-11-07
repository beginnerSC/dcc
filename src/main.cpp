#include <iostream>
#include <pybind11/pybind11.h>

// std::string hello_from_bin() { return "Hello from dcc!"; }

// namespace py = pybind11;

// PYBIND11_MODULE(_core, m) {
//   m.doc() = "pybind11 hello module";

//   m.def("hello_from_bin", &hello_from_bin, R"pbdoc(
//       A function that returns a Hello string.
//   )pbdoc");
// }

class vector{
  int *a = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 10;
public: 
  vector() {}
  vector(size_t size) : size_(size) {
    a = get_initialized_array(capacity_);
  }
  ~vector() { delete [] a; }

  int* get_initialized_array(size_t capacity){
    int *res = new int[capacity];
    for (size_t i=0 ; i<capacity ; ++i)
    {
      res[i] = 0;
    }
    return res;
  }
  void print() {
    for (size_t i=0 ; i<size_ ; i++)
    {
      std::cout << a[i] << ", ";
    }
    std::cout << std::endl;
  }
  void push_back(const int& val)
  {
    if (size_ == capacity_)
    {
      capacity_ *= 2;
      int *tmp = get_initialized_array(capacity_);
      for (size_t i=0 ; i<size_ ; i++)
      {
        tmp[i] = a[i];
      }
      delete [] a;
      a = tmp;
    }
    a[size_] = val;
    ++size_;
  }

  const int& get_capacity() const
  {
    return capacity_;
  }
  const int& size() const 
  {
    return size_;
  }
  vector& operator=(const vector& other)
  {
    if (this != &other){
      delete [] a;
      size_ = other.size();
      capacity_ = other.get_capacity();
      a = get_initialized_array(capacity_);
      for (size_t i=0 ; i<size_ ; ++i)
      {
        a[i] = other[i];
      }
    }
    return *this;
  }

  int& operator[](size_t i)
  {
    return a[i]; 
  }

  const int& operator[](size_t i) const
  {
    return a[i]; 
  }
};

int main() {
  size_t size = 3;
  vector v(size);

  v.print();

  for (int i=0 ; i<2*size ; ++i)
  {
    v.push_back(i);
  }

  v.print();

  std::cout << v[1] << ", " << v[7] << ", " << std::endl;

  v[3] = 10;
  v.print();

  vector u;
  
  u = v;
  u[3] = 20;
  u.print();

  return 0;
}