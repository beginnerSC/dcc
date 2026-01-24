#include <gtest/gtest.h>
#include "dcc_core/collections.h"

TEST(CollectionsTest, Counter) {
    std::unordered_map<char, int> res = {{'a', 3}, {'g', 1}, {'m', 1}, {'n', 1}, {'r', 1}};
    EXPECT_EQ(Counter("anagram"), res);
}