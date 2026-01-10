#include <iostream>
// #include <pybind11/pybind11.h>
// #include <pybind11/stl.h>
#include <vector>
#include <utility>
#include <ranges>
#include <cmath>
#include <stdexcept>
#include <string>
#include <sstream>
#include <unordered_map>
#include <deque>
#include <algorithm>
#include <concepts>
#include <type_traits>
#include <print>
#include <functional>

// std::string hello_from_bin() { return "Hello from dcc!"; }

// namespace py = pybind11;

// class Point{
//   double x_, y_;
//   double step_size_ = 0.01;
//   Point* target_;
//   std::vector<double> pursuit_curve_x_ = {}, 
//                       pursuit_curve_y_ = {}; 

//   const double Distance(const Point* p) const {
//     auto [px, py] = p->GetCoordinates(); 
//     return std::hypot(px-x_, py-y_);   // also from cmath, claimed to be more numerically stable than std::sqrt(x*x + y*y)
//   }
// public:
//   Point(const double& x, const double& y): x_(x), y_(y) {}
//   void Step(){
//     auto [tx, ty] = target_->GetCoordinates();
//     const double scale = step_size_/Distance(target_);
//     x_ += scale*(tx-x_);
//     y_ += scale*(ty-y_);

//     pursuit_curve_x_.push_back(x_);
//     pursuit_curve_y_.push_back(y_);
//   }
//   std::pair<const std::vector<double>&, const std::vector<double>&> GetPursuitCurve() const noexcept {
//     return {pursuit_curve_x_, pursuit_curve_y_};
//   }
//   const std::pair<double, double> GetCoordinates() const {
//     return {x_, y_};
//   }
//   void SetStepSize(const double& step_size) {
//     step_size_ = step_size;
//   }
//   void SetTarget(Point* target){
//     target_ = target; 
//   }
// };

// PYBIND11_MODULE(_core, m) {
//   // m.doc() = "pybind11 hello module";

//   // m.def("hello_from_bin", &hello_from_bin, R"pbdoc(
//   //     A function that returns a Hello string.
//   // )pbdoc");

//   py::class_<Point>(m, "Point")
//     .def(py::init<const double&, const double&>())
//     .def("Step",            &Point::Step)
//     .def("GetCoordinates",  &Point::GetCoordinates)
//     .def("GetPursuitCurve", &Point::GetPursuitCurve)
//     .def("SetTarget",       &Point::SetTarget)
//     .def("SetStepSize",     &Point::SetStepSize);
// }

void RangesExample(){
  std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto processed_numbers = numbers 
                          | std::views::filter([](int n){ return n % 2 == 0; }) 
                          | std::views::transform([](int n){ return n * 2; });
  // processed_numbers now represents a view of {4, 8, 12, 16, 20}

  for (const int& n : processed_numbers) {
    std::cout << n << ", ";
  }
  std::cout << std::endl << std::endl;
}


bool IsEmpty(int a){
  return (a==-1);
}

bool IsEmpty(const std::string& a){
  return a.empty();
}

std::string FormatValue(int a){
  std::stringstream ss;
  ss << "I[" << std::to_string(a) << "]";
  return ss.str(); 
}

std::string FormatValue(const std::string& a){
  std::stringstream ss;
  ss << "S[" << a << "]";
  return ss.str();
}

template <typename MapType>
std::string renderContainer(const MapType& map)
{
  std::stringstream ss;

  for (const auto& [key, value] : map)
  {
    ss << (IsEmpty(key) ? "UNKNOWN" : FormatValue(key)) 
      << "=" 
      << (IsEmpty(value) ? "UNSPECIFIED" : FormatValue(value))
      << "\\n";
  }
  return ss.str();
}

template <typename C>
concept NumericContainer = requires(C c, std::size_t index) {
    // 1. Type Requirement: Must have a nested value_type
    typename C::value_type;  // ????

    // 2. Nested Requirement: value_type must be a floating point
    requires std::floating_point<typename C::value_type>;

    // 3. Compound Requirement: .size() must return exactly std::size_t
    { c.size() } -> std::same_as<std::size_t>;

    // 4. Compound Requirement: index access must return a reference to value_type
    { c[index] } -> std::same_as<typename C::value_type&>;

    // 5. Compound Requirement: .clear() must exist and be noexcept
    { c.clear() } noexcept;
};

// Usage: A function that only accepts types matching the NumericContainer concept
void process_data(NumericContainer auto& container) {
    if (container.size() > 0) {
        container[0] *= 2.0;
    }
}


int main() {
  std::unordered_map<std::string, int> dd = {{"AAA", 1}, {"BBB", 2}};
  std::println("{}", dd);

  std::unordered_map<std::string, int> map = {{"Tim", 11}, {"", 9}};

  std::cout << renderContainer(map) << std::endl;

  return 0;
}

// int main0() {
//   Point A(0, 0), B(0, 1), C(1, 1), D(1, 0);

//   A.SetTarget(&B);
//   B.SetTarget(&C);
//   C.SetTarget(&D);
//   D.SetTarget(&A);

//   for (size_t i=0 ; i<1000 ; ++i) {
//     A.Step();
//     B.Step();
//     C.Step();
//     D.Step();
//   }
//   auto [ax, ay] = A.GetPursuitCurve();

//   for (const double& x : ax){
//     std::cout << x << ", ";
//   }
//   std::cout << std::endl;
  
//   for (const double& y : ay){
//     std::cout << y << ", ";
//   }

//   return 0;  
// }
