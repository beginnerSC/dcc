#include <iostream>
#include <pybind11/pybind11.h>

std::string hello_from_bin() { return "Hello from dcc!"; }

namespace py = pybind11;

PYBIND11_MODULE(_core, m) {
  m.doc() = "pybind11 hello module";

  m.def("hello_from_bin", &hello_from_bin, R"pbdoc(
      A function that returns a Hello string.
  )pbdoc");
}

class vector{
  int *a;
  size_t size;
public: 
  vector(size_t size) : size(size) {
    a = new int[size];
  }
  ~vector() { delete [] a; }
  void print() {
    for (size_t i=0 ; i<size ; i++)
    {
      std::cout << a[i] << ", ";
    }
  }
};

int main() {
  vector v(5);

  v.print();

  return 0;
}