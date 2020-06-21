#include "./test_common.hpp"

// alone because it is quite long to run ... (exception ....)

TEST(Array, BoundCheck) { //NOLINT

  nda::array<long, 2> A(2, 3);

  EXPECT_THROW(A(0, 3), std::runtime_error); //NOLINT

  // FIXME : SHOULD WE REALLY THROW ?
  //EXPECT_THROW(A(nda::range(0, 4), 2), std::runtime_error);
  //EXPECT_THROW(A(nda::range(10, 14), 2), std::runtime_error);

  EXPECT_THROW(A(nda::range(), 5), std::runtime_error); //NOLINT
  EXPECT_THROW(A(0, 3), std::runtime_error);            //NOLINT
}