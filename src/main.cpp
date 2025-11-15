#include <iostream>
#include <pybind11/pybind11.h>
#include <vector>
#include <utility>
#include <ranges>
#include <cmath>

// std::string hello_from_bin() { return "Hello from dcc!"; }

// namespace py = pybind11;

// PYBIND11_MODULE(_core, m) {
//   m.doc() = "pybind11 hello module";

//   m.def("hello_from_bin", &hello_from_bin, R"pbdoc(
//       A function that returns a Hello string.
//   )pbdoc");
// }

class vector{
  int *a_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 10;

  int* get_initialized_array(size_t capacity){
    int *res = new int[capacity];
    for (size_t i=0 ; i<capacity ; ++i)
    {
      res[i] = 0;
    }
    return res;
  }

public: 
  vector() {}
  vector(size_t size) : size_(size) {
    a_ = get_initialized_array(capacity_);
  }
  ~vector() { delete [] a_; }

  void print() {
    for (size_t i=0 ; i<size_ ; i++)
    {
      std::cout << a_[i] << ", ";
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
        tmp[i] = a_[i];
      }
      delete [] a_;
      a_ = tmp;
    }
    a_[size_] = val;
    ++size_;
  }

  void resize(const size_t& size)
  {
    if (size < capacity_) {
      size_ = size;
    } else {
      do {
        capacity_ *= 2; 
      } while (capacity_ < size);
      int* tmp = get_initialized_array(capacity_);
      for (size_t i=0 ; i<size_ ; ++i){
        tmp[i] = a_[i];
      }
      delete [] a_;
      a_ = tmp;
      size_ = size;
    }
  }
  const int& capacity() const
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
      delete [] a_;
      size_ = other.size();
      capacity_ = other.capacity();
      a_ = get_initialized_array(capacity_);
      for (size_t i=0 ; i<size_ ; ++i)
      {
        a_[i] = other[i];
      }
    }
    return *this;
  }

  int& operator[](size_t i)
  {
    return a_[i]; 
  }

  const int& operator[](size_t i) const
  {
    return a_[i]; 
  }
};

void RangesExample(){

  std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto processed_numbers = numbers 
                          | std::views::filter([](int n){ return n % 2 == 0; }) 
                          | std::views::transform([](int n){ return n * 2; });
  // processed_numbers now represents a view of {4, 8, 12, 16, 20}

  for (const int& n : processed_numbers)
    std::cout << n << ", ";

  std::cout << std::endl << std::endl;
}

int main0() {
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

  std::cout << "copy ctor: " << std::endl;
  vector u;
  
  u = v;
  u[3] = 20; 
  u.print();

  std::cout << "resize: " << std::endl;
  v.resize(20);
  v.print();

  v.resize(5);
  v.print();

  v.resize(40);
  v.print();

  return 0;
}

class Point{
  double x_, y_;
  double step_size_ = 0.01;
  Point* target_;
  std::vector<double> pursuit_curve_x_ = {}, 
                      pursuit_curve_y_ = {}; 
public:
  Point(const double& x, const double& y): x_(x), y_(y) {}
  void Step(){
    auto [tx, ty] = target_->GetCoordinates();
    const double scale = step_size_/Distance(target_);
    x_ += scale*(tx-x_);
    y_ += scale*(ty-y_);

    pursuit_curve_x_.push_back(x_);
    pursuit_curve_y_.push_back(y_);
  }
  const double Distance(const Point* p) const {
    auto [px, py] = p->GetCoordinates(); 
    return std::hypot(px-x_, py-y_);   // also from cmath, claimed to be more numerically stable than std::sqrt(x*x + y*y)
  }
  std::pair<const std::vector<double>&, const std::vector<double>&> GetPursuitCurve() const noexcept {
    return {pursuit_curve_x_, pursuit_curve_y_};
  }
  const std::pair<double, double> GetCoordinates() const {
    return {x_, y_};
  }
  void SetStepSize(const double& step_size) {
    step_size_ = step_size;
  }
  void SetTarget(Point* target){
    target_ = target; 
  }
};

int main() {
  Point A(0, 0), B(0, 1), C(1, 1), D(1, 0);

  A.SetTarget(&B);
  B.SetTarget(&C);
  C.SetTarget(&D);
  D.SetTarget(&A);

  for (size_t i=0 ; i<1000 ; ++i) {
    A.Step();
    B.Step();
    C.Step();
    D.Step();
  }
  auto [ax, ay] = A.GetPursuitCurve();

  for (const double& x : ax){
    std::cout << x << ", ";
  }
  std::cout << std::endl;
  
  for (const double& y : ay){
    std::cout << y << ", ";
  }

  return 0;  
}