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
  int *a;
  size_t size = 0;
  size_t capacity = 10;
public: 
  vector(size_t size) : size(size) {
    a = new int[size];
    for (size_t i=0 ; i<size ; ++i)
    {
      a[i] = 0;
    }
  }
  ~vector() { delete [] a; }
  void print() {
    for (size_t i=0 ; i<size ; i++)
    {
      std::cout << a[i] << ", ";
    }
    std::cout << std::endl;
  }
  void push_back(const int& val)
  {
    if (size == capacity)
    {
      capacity *= 2;
    }
    a[size] = val;
    ++size;
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

  return 0;
}