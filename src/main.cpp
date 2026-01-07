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

class Vector{
  int *a_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 10;

  int* GetInitializedArray(size_t capacity){
    int *res = new int[capacity];
    for (size_t i=0 ; i<capacity ; ++i){
      res[i] = 0;
    }
    return res;
  }

public: 
  Vector() : Vector(0) {}  // without Vector(0) I get UB in end() when computing (a_ + size_) with a_ nullptr
  Vector(int size) {   // with Vector(size_t size) and no casting below, Vector(-5) will break the code
    if (size < 0) {
      throw std::invalid_argument("Size cannot be negative");
    }
    size_ = static_cast<size_t>(size);
    while (capacity_ < size_) {
      capacity_ *= 2;
    }
    a_ = GetInitializedArray(capacity_);
  }
  Vector(const Vector& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    a_ = GetInitializedArray(other.capacity_);
    for (size_t j=0 ; j<size_ ; ++j) {
      a_[j] = other[j];
    }
  }
  Vector(Vector&& other) {
    a_ = other.a_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    other.a_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }
  ~Vector() { delete [] a_; }

  class iterator{
    int *ptr_ = nullptr;
  public: 
    iterator(int* ptr) noexcept : ptr_(ptr) {}
    int& operator*() const noexcept {
      return *ptr_;
    }
    int* operator->() const noexcept {  // useless as int has no members, only for the sake of completeness; will be useful later on if I template the Vector class
      return ptr_;
    }
    iterator& operator++() noexcept {
      ptr_++;
      return *this;
    }
    iterator operator++(int _) noexcept {
      iterator tmp = *this;
      ptr_++;
      return tmp;
    }
    bool operator==(iterator other) const noexcept {
      return (ptr_ == other.GetPtr());
    }
    bool operator!=(iterator other) const noexcept {
      return (ptr_ != other.GetPtr());
    }
    int* GetPtr() const noexcept {
      return ptr_;
    }
// Dereferencing (* operator): Return the value at the current position
// Arrow operator (-> operator): For accessing members (less relevant for int, but good practice)
// Pre-increment (++it): Move to the next element and return the iterator
// Post-increment (it++): Move to the next element but return the old position
// Equality comparison (==): Check if two iterators point to the same position
// Inequality comparison (!=): Check if two iterators point to different positions
  };

  iterator begin() const noexcept {
    return iterator(a_);
  }
  iterator end() const noexcept {
    return iterator(a_ + size_);
  }

  void Print() {
    for (size_t i=0 ; i<size_ ; i++){
      std::cout << a_[i] << ", ";
    }
    std::cout << std::endl;
  }
  void PushBack(const int& val){
    if (size_ == capacity_){
      capacity_ *= 2;
      int *tmp = GetInitializedArray(capacity_);
      for (size_t i=0 ; i<size_ ; i++){
        tmp[i] = a_[i];
      }
      delete [] a_;
      a_ = tmp;
    }
    a_[size_] = val;
    ++size_;
  }

  void Resize(const size_t& size){
    if (size < capacity_) {
      size_ = size;
    } else {
      do {
        capacity_ *= 2; 
      } while (capacity_ < size);

      int* tmp = GetInitializedArray(capacity_);

      for (size_t i=0 ; i<size_ ; ++i) {
        tmp[i] = a_[i];
      }
      delete [] a_;
      a_ = tmp;
      size_ = size;
    }
  }
  size_t Size() const noexcept {
    return size_;
  }
  Vector& operator=(const Vector& other) noexcept {
    if (this != &other){
      delete [] a_;                   // clean up existing data  

      size_ = other.size_;            // copy the data
      capacity_ = other.capacity_;
      a_ = GetInitializedArray(capacity_);
      for (size_t i=0 ; i<size_ ; ++i) {
        a_[i] = other[i];
      }
    }
    return *this;
  }
  Vector& operator=(Vector&& other) noexcept {
    if (this != &other){
      delete [] a_;                   // clean up existing data

      size_ = other.size_;            // move the data
      capacity_ = other.capacity_;
      a_ = other.a_;

      other.a_ = nullptr;             // leave other in safe state
      other.size_ = 0;
      other.capacity_ = 0;
    }
    return *this;
  }
  int& operator[](size_t i) noexcept {
    return a_[i]; 
  }
  const int& operator[](size_t i) const noexcept {
    return a_[i]; 
  }
};

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


struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

std::vector<std::vector<int>> levelOrder(TreeNode* root) {

  if (root==nullptr) return {};

  std::vector<std::vector<int>> res;
  std::deque<TreeNode*> q{root};

  while (!q.empty()){
    std::vector<int> level = {};
    size_t n = q.size();
    for (size_t i=0 ; i<n ; i++) {
      TreeNode* node = q.front(); 
      level.push_back(node->val);
      if (node->left) q.push_back(node->left);
      if (node->right) q.push_back(node->right);
      q.pop_front();
    }
    res.push_back(level);
  }
  return res;
}

int climbStairs(int n) {   // https://leetcode.com/problems/climbing-stairs/
  if (n < 3){
    return n;
  } else {
    int pre = 1;
    int cur = 2;
    for (int j=3 ; j<n+1 ; ++j) {
      int tmp = cur;
      cur += pre;
      pre = tmp;
    }
    return cur;
  }
}

int rob(std::vector<int>& nums) { // https://leetcode.com/problems/house-robber/
  int pre = 0;
  int cur = nums.front();
  for (size_t j=1 ; j<nums.size() ; ++j) {
    int tmp = cur;
    cur = std::max(nums[j] + pre, cur);
    pre = tmp;
  }
  return cur;
}

int coinChange(std::vector<int>& coins, int amount) {   // https://leetcode.com/problems/coin-change/
  static std::unordered_map<int, int> cache;
  if (amount < 0) {
    return -1;
  } else if (amount == 0) {   // trace the code without this branch
    return 0;
  } else if (cache.contains(amount)) {
    return cache[amount];
  } else {
    std::vector<int> num_coins;
    int min = std::numeric_limits<int>::max();
    for (int coin : coins){
      int sub = coinChange(coins, amount - coin);
      if (sub != -1) {
        num_coins.push_back(sub + 1);
      }
    }
    cache[amount] = std::ranges::min(num_coins);
    return cache[amount];
  }
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

  std::vector<int> coins = {1, 2, 5};
  int amount = 11;
  std::cout << coinChange(coins, amount) << std::endl;

  // will break coinChange
  // std::vector<int> coins = {2}; 
  // int amount = 3;

// Input: root = [3,9,20,null,null,15,7]
// Output: [[3],[9,20],[15,7]]

  // TreeNode root(3, &TreeNode(9), &TreeNode(20, &TreeNode(15), &TreeNode(7))); // doesn't compile: '&' requires l-value
  // TreeNode n15(15), n7(7), n9(9), n20(20, &n15, &n7), root(3, &n9, &n20);
  TreeNode* root = new TreeNode(3, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7)));
  // TreeNode* root = new TreeNode();

  std::vector<std::vector<int>> res = levelOrder(root);
  for (const auto& level : res){
    std::cout << "[";

    for (size_t i=0 ; i<level.size() ; ++i){
      std::cout << level[i];
      if (i != level.size()-1) {
        std::cout << ", ";
      }
    }
    std::cout << "], "; 
  }


  std::unordered_map<std::string, int> map = {{"Tim", 11}, {"", 9}};

  std::cout << renderContainer(map) << std::endl;


  size_t size = 3;
  Vector v(size);

  for (Vector::iterator it=v.begin() ; it!=v.end() ; it++) {
    std::cout << *it << ", ";
  }
  std::cout << std::endl;

  for (const int& val : v) {
    std::cout << val << ", ";
  }
  std::cout << std::endl;

  for (int i=0 ; i<2*size ; ++i){
    v.PushBack(i);
  }

  v.Print();

  std::cout << v[1] << ", " << v[7] << ", " << std::endl;

  v[3] = 10;
  v.Print();

  std::cout << "copy assignment: " << std::endl;
  Vector u;
  
  u = v;
  u[3] = 20; 
  u.Print();

  std::cout << "copy ctor: " << std::endl;
  Vector x = v;
  x.Print();

  std::cout << "Resize: " << std::endl;
  v.Resize(20);
  v.Print();

  v.Resize(5);
  v.Print();

  v.Resize(40);
  v.Print();

  v.Resize(5);
  v.Print();

  std::cout << "move assignment: " << std::endl;
  v = std::move(x);
  v.Print();

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
