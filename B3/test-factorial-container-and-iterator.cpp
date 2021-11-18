#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "factorial-container.hpp"

BOOST_AUTO_TEST_SUITE(testFactorialContainer)

FactorialContainer cont(10);

BOOST_AUTO_TEST_CASE(testDereferenceOperator)
{
  BOOST_CHECK_EQUAL(*cont.begin(), 1);
}

BOOST_AUTO_TEST_CASE(testBeginAndEnd)
{
  auto iter = cont.begin();
  BOOST_CHECK_EQUAL(*iter, 1);
  auto iter2 = --cont.end();
  BOOST_CHECK_EQUAL(*iter2, 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10);
}

BOOST_AUTO_TEST_CASE(testRbeginAndRend)
{
  BOOST_CHECK_EQUAL(*(--cont.rend()), 1);
  BOOST_CHECK_EQUAL(*cont.rbegin(), 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10);
}

BOOST_AUTO_TEST_CASE(testIncrementAndDecrement)
{
  auto iter = cont.begin();
  iter++;
  BOOST_CHECK_EQUAL(*iter, 2);
  auto iter2 = cont.end();
  iter2--;
  BOOST_CHECK_EQUAL(*iter2, 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10);
  BOOST_CHECK_EQUAL(*(++cont.begin()), 2);
  BOOST_CHECK_EQUAL(*(--cont.end()), 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10);
  BOOST_CHECK_THROW(++cont.end(), std::out_of_range);
  BOOST_CHECK_THROW(--cont.begin(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(testComparisonOperators)
{
  auto iter1 = cont.begin();
  auto iter2 = cont.end();
  BOOST_CHECK(iter1 != iter2);
  auto iter3 = cont.end();
  BOOST_CHECK(iter3 == iter2);
}

BOOST_AUTO_TEST_CASE(testBigNumberInContainer)
{
  BOOST_CHECK_THROW(FactorialContainer container(188888), std::overflow_error);
}

BOOST_AUTO_TEST_CASE(testSizeMethod)
{
  FactorialContainer cont(9);
  FactorialContainer cont2(4);
  FactorialContainer cont3;
  BOOST_CHECK_EQUAL(cont.size(), 9);
  BOOST_CHECK_EQUAL(cont2.size(), 4);
  BOOST_CHECK_EQUAL(cont3.size(), 0);
}

BOOST_AUTO_TEST_CASE(testComputeFactorial)
{
  BOOST_CHECK_EQUAL(computeFactorial(5), 1 * 2 * 3 * 4 * 5);
  BOOST_CHECK_EQUAL(computeFactorial(10), 1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10);
  BOOST_CHECK_EQUAL(computeFactorial(0), 0);
}

BOOST_AUTO_TEST_SUITE_END()
