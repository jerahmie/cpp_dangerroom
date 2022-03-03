#define BOOST_TEST_MODULE My Test
#include <boost/test/included/unit_test.hpp>
#include <complex>
#include "twice.h"

BOOST_AUTO_TEST_CASE(simple_test)
{
  const int i = 1;
  BOOST_TEST(i);
  BOOST_TEST(twice(i) == 2);
  BOOST_TEST(twice(4.4) == 8.8);
  const std::complex<double> b = 1.+2.j;
  const std::complex<double> c = 2.+4.j;
  BOOST_TEST(twice(b) == c);
}
