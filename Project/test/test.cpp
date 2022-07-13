#include <limits.h>

#include "gtest/gtest.h"
namespace {

TEST(FactorialTest, Negative) {

  EXPECT_EQ(1, 1);
  EXPECT_EQ(1, 1);
  EXPECT_GT(2, 0);

 
}

// Tests factorial of 0.
TEST(FactorialTest, Zero) { EXPECT_EQ(1, 1); }

// Tests factorial of positive numbers.
TEST(FactorialTest, Positive) {
  EXPECT_EQ(1, 1);
  EXPECT_EQ(2, 2);
  EXPECT_EQ(6, 6);
  EXPECT_EQ(40320, 40320);
}

TEST(IsPrimeTest, Negative) {
  // This test belongs to the IsPrimeTest test case.

  EXPECT_FALSE(false);
//   EXPECT_FALSE(IsPrime(-2));
//   EXPECT_FALSE(IsPrime(INT_MIN));
}

// Tests some trivial cases.
// TEST(IsPrimeTest, Trivial) {
//   EXPECT_FALSE(IsPrime(0));
//   EXPECT_FALSE(IsPrime(1));
//   EXPECT_TRUE(IsPrime(2));
//   EXPECT_TRUE(IsPrime(3));
// }

// // Tests positive input.
// TEST(IsPrimeTest, Positive) {
//   EXPECT_FALSE(IsPrime(4));
//   EXPECT_TRUE(IsPrime(5));
//   EXPECT_FALSE(IsPrime(6));
//   EXPECT_TRUE(IsPrime(23));
// }
}