#include <gtest/gtest.h>
#include <stdexcept>
#include "dcc_core/vector.h"

class VectorTest : public ::testing::Test {
 protected:
  Vector v;
};

// Constructor tests
TEST(VectorConstructorTest, DefaultConstructor) {
  Vector v;
  EXPECT_EQ(v.Size(), 0);
}

TEST(VectorConstructorTest, SizedConstructor) {
  Vector v(5);
  EXPECT_EQ(v.Size(), 5);
  for (size_t i = 0; i < v.Size(); ++i) {
    EXPECT_EQ(v[i], 0);
  }
}

TEST(VectorConstructorTest, SizedConstructorWithLargeSize) {
  Vector v(100);
  EXPECT_EQ(v.Size(), 100);
}

TEST(VectorConstructorTest, SizedConstructorThrowsOnNegativeSize) {
  EXPECT_THROW(Vector(-5), std::invalid_argument);
}

TEST(VectorConstructorTest, CopyConstructor) {
  Vector v1(3);
  v1[0] = 10;
  v1[1] = 20;
  v1[2] = 30;

  Vector v2(v1);
  EXPECT_EQ(v2.Size(), 3);
  EXPECT_EQ(v2[0], 10);
  EXPECT_EQ(v2[1], 20);
  EXPECT_EQ(v2[2], 30);

  // Modify copy and verify original is unchanged
  v2[0] = 100;
  EXPECT_EQ(v1[0], 10);
  EXPECT_EQ(v2[0], 100);
}

TEST(VectorConstructorTest, MoveConstructor) {
  Vector v1(3);
  v1[0] = 10;
  v1[1] = 20;
  v1[2] = 30;

  Vector v2(std::move(v1));
  EXPECT_EQ(v2.Size(), 3);
  EXPECT_EQ(v2[0], 10);
  EXPECT_EQ(v2[1], 20);
  EXPECT_EQ(v2[2], 30);

  // Original should be in safe state
  EXPECT_EQ(v1.Size(), 0);
}

// PushBack tests
TEST(VectorTest, PushBackSingleElement) {
  Vector v;
  v.PushBack(5);
  EXPECT_EQ(v.Size(), 1);
  EXPECT_EQ(v[0], 5);
}

TEST(VectorTest, PushBackMultipleElements) {
  Vector v;
  for (int i = 0; i < 10; ++i) {
    v.PushBack(i);
  }
  EXPECT_EQ(v.Size(), 10);
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(v[i], i);
  }
}

TEST(VectorTest, PushBackCausesCapacityGrowth) {
  Vector v;
  for (int i = 0; i < 20; ++i) {
    v.PushBack(i);
  }
  EXPECT_EQ(v.Size(), 20);
}

// Resize tests
TEST(VectorTest, ResizeToSmaller) {
  Vector v(10);
  for (int i = 0; i < 10; ++i) {
    v[i] = i;
  }
  v.Resize(5);
  EXPECT_EQ(v.Size(), 5);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(v[i], i);
  }
}

TEST(VectorTest, ResizeToLarger) {
  Vector v(3);
  v[0] = 10;
  v[1] = 20;
  v[2] = 30;

  v.Resize(10);
  EXPECT_EQ(v.Size(), 10);
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v[1], 20);
  EXPECT_EQ(v[2], 30);
  // New elements should be initialized to 0
  for (int i = 3; i < 10; ++i) {
    EXPECT_EQ(v[i], 0);
  }
}

TEST(VectorTest, ResizeMultipleTimes) {
  Vector v(5);
  for (int i = 0; i < 5; ++i) {
    v[i] = i;
  }

  v.Resize(20);
  EXPECT_EQ(v.Size(), 20);

  v.Resize(5);
  EXPECT_EQ(v.Size(), 5);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(v[i], i);
  }

  v.Resize(40);
  EXPECT_EQ(v.Size(), 40);
}

// Assignment operators
TEST(VectorTest, CopyAssignment) {
  Vector v1(3);
  v1[0] = 10;
  v1[1] = 20;
  v1[2] = 30;

  Vector v2;
  v2 = v1;
  EXPECT_EQ(v2.Size(), 3);
  EXPECT_EQ(v2[0], 10);
  EXPECT_EQ(v2[1], 20);
  EXPECT_EQ(v2[2], 30);

  // Modify copy and verify original is unchanged
  v2[0] = 100;
  EXPECT_EQ(v1[0], 10);
  EXPECT_EQ(v2[0], 100);
}

TEST(VectorTest, CopyAssignmentSelfAssignment) {
  Vector v(3);
  v[0] = 10;
  v[1] = 20;
  v[2] = 30;

  v = v;
  EXPECT_EQ(v.Size(), 3);
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v[1], 20);
  EXPECT_EQ(v[2], 30);
}

TEST(VectorTest, MoveAssignment) {
  Vector v1(3);
  v1[0] = 10;
  v1[1] = 20;
  v1[2] = 30;

  Vector v2;
  v2 = std::move(v1);
  EXPECT_EQ(v2.Size(), 3);
  EXPECT_EQ(v2[0], 10);
  EXPECT_EQ(v2[1], 20);
  EXPECT_EQ(v2[2], 30);

  // Original should be in safe state
  EXPECT_EQ(v1.Size(), 0);
}

TEST(VectorTest, MoveAssignmentSelfAssignment) {
  Vector v(3);
  v[0] = 10;
  v[1] = 20;
  v[2] = 30;

  v = std::move(v);
  EXPECT_EQ(v.Size(), 3);
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v[1], 20);
  EXPECT_EQ(v[2], 30);
}

// Subscript operator tests
TEST(VectorTest, SubscriptOperatorRead) {
  Vector v(5);
  v[0] = 10;
  v[2] = 30;
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v[1], 0);
  EXPECT_EQ(v[2], 30);
}

TEST(VectorTest, SubscriptOperatorWrite) {
  Vector v(3);
  v[0] = 100;
  v[1] = 200;
  v[2] = 300;
  EXPECT_EQ(v[0], 100);
  EXPECT_EQ(v[1], 200);
  EXPECT_EQ(v[2], 300);
}

TEST(VectorTest, ConstSubscriptOperator) {
  Vector v(3);
  v[0] = 10;
  v[1] = 20;
  v[2] = 30;

  const Vector& cv = v;
  EXPECT_EQ(cv[0], 10);
  EXPECT_EQ(cv[1], 20);
  EXPECT_EQ(cv[2], 30);
}

// Iterator tests
TEST(VectorTest, BeginAndEnd) {
  Vector v(3);
  v[0] = 10;
  v[1] = 20;
  v[2] = 30;

  Vector::iterator it = v.begin();
  EXPECT_EQ(*it, 10);

  ++it;
  EXPECT_EQ(*it, 20);

  ++it;
  EXPECT_EQ(*it, 30);

  ++it;
  EXPECT_EQ(it, v.end());
}

TEST(VectorTest, IteratorPreIncrement) {
  Vector v(3);
  v[0] = 10;
  v[1] = 20;
  v[2] = 30;

  Vector::iterator it = v.begin();
  Vector::iterator it2 = ++it;
  EXPECT_EQ(*it, 20);
  EXPECT_EQ(*it2, 20);
  EXPECT_EQ(it, it2);
}

TEST(VectorTest, IteratorPostIncrement) {
  Vector v(3);
  v[0] = 10;
  v[1] = 20;
  v[2] = 30;

  Vector::iterator it = v.begin();
  Vector::iterator it2 = it++;
  EXPECT_EQ(*it, 20);
  EXPECT_EQ(*it2, 10);
  EXPECT_NE(it, it2);
}

TEST(VectorTest, IteratorEquality) {
  Vector v(3);
  Vector::iterator it1 = v.begin();
  Vector::iterator it2 = v.begin();
  EXPECT_EQ(it1, it2);

  ++it1;
  EXPECT_NE(it1, it2);
}

TEST(VectorTest, IteratorLoop) {
  Vector v(5);
  for (int i = 0; i < 5; ++i) {
    v[i] = i * 10;
  }

  int index = 0;
  for (Vector::iterator it = v.begin(); it != v.end(); ++it) {
    EXPECT_EQ(*it, index * 10);
    ++index;
  }
  EXPECT_EQ(index, 5);
}

TEST(VectorTest, ConstIteratorLoop) {
  Vector v(5);
  for (int i = 0; i < 5; ++i) {
    v[i] = i * 10;
  }

  const Vector& cv = v;
  int index = 0;
  for (Vector::iterator it = cv.begin(); it != cv.end(); ++it) {
    EXPECT_EQ(*it, index * 10);
    ++index;
  }
  EXPECT_EQ(index, 5);
}

// Size test
TEST(VectorTest, Size) {
  Vector v;
  EXPECT_EQ(v.Size(), 0);

  v.PushBack(1);
  EXPECT_EQ(v.Size(), 1);

  v.PushBack(2);
  EXPECT_EQ(v.Size(), 2);

  v.Resize(10);
  EXPECT_EQ(v.Size(), 10);
}

// Integration test with the original main() code
TEST(VectorIntegrationTest, OriginalMainBehavior) {
  size_t size = 3;
  Vector v(size);

  // Check initial state
  EXPECT_EQ(v.Size(), size);
  for (size_t i = 0; i < size; ++i) {
    EXPECT_EQ(v[i], 0);
  }

  // Add elements
  for (int i = 0; i < 2 * static_cast<int>(size); ++i) {
    v.PushBack(i);
  }
  EXPECT_EQ(v.Size(), 3 + 6);

  // Check specific elements
  EXPECT_EQ(v[1], 0);
  EXPECT_EQ(v[7], 4);

  // Modify element
  v[3] = 10;
  EXPECT_EQ(v[3], 10);

  // Copy assignment
  Vector u;
  u = v;
  EXPECT_EQ(u.Size(), v.Size());
  u[3] = 20;
  EXPECT_EQ(v[3], 10);  // Original unchanged
  EXPECT_EQ(u[3], 20);

  // Copy constructor
  Vector x = v;
  EXPECT_EQ(x.Size(), v.Size());
  for (size_t i = 0; i < v.Size(); ++i) {
    EXPECT_EQ(x[i], v[i]);
  }

  // Resize operations
  v.Resize(20);
  EXPECT_EQ(v.Size(), 20);

  v.Resize(5);
  EXPECT_EQ(v.Size(), 5);

  v.Resize(40);
  EXPECT_EQ(v.Size(), 40);

  v.Resize(5);
  EXPECT_EQ(v.Size(), 5);

  // Move assignment
  v = std::move(x);
  EXPECT_EQ(v.Size(), 9);  // x had size 9 before move
  EXPECT_EQ(x.Size(), 0);  // x should be empty after move
}
