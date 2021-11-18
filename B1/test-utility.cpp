#include <stdexcept>
#include <vector>
#include <forward_list>
#include <algorithm>
#include <boost/test/unit_test.hpp>
#include <boost/test/tools/output_test_stream.hpp>

#include "utility.hpp"
#include "policy.hpp"
#include "structures-for-test.hpp"

BOOST_AUTO_TEST_SUITE(testUtility)

const double SIZE = 5;

struct SortFixture
{
  SortFixture() :
  vector({-10, 98, 97, 0, 1, -1}),
  list({26, 83, 99, 55, 88, 99, 0, -99}),
  sortedAscendingVector(vector),
  sortedAscendingList(list)
  {
    std::sort(sortedAscendingVector.begin(), sortedAscendingVector.end());
    sortedDescendingVector = sortedAscendingVector;
    std::reverse(sortedDescendingVector.begin(), sortedDescendingVector.end());
    sortedAscendingList.sort();
    sortedDescendingList = sortedAscendingList;
    sortedDescendingList.reverse();
  }

  std::vector <int> vector;
  std::forward_list <int> list;
  std::vector <int> sortedAscendingVector;
  std::forward_list <int> sortedAscendingList;
  std::vector <int> sortedDescendingVector;
  std::forward_list <int> sortedDescendingList;
};

BOOST_AUTO_TEST_CASE(testGetSorType)
{
  BOOST_CHECK_EQUAL(details::SortType::ASCENDING, getSortType("ascending"));
  BOOST_CHECK_EQUAL(details::SortType::DESCENDING, getSortType("descending"));
  BOOST_CHECK_THROW(getSortType(""), std::invalid_argument);
  BOOST_CHECK_THROW(getSortType("otherSortType"), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(testBubbleSortWithBracketsPolicy, SortFixture)
{
  details::bubbleSort <BracketsPolicy>(vector, details::SortType::ASCENDING);
  BOOST_CHECK(vector == sortedAscendingVector);
  details::bubbleSort <BracketsPolicy>(vector, details::SortType::DESCENDING);
  BOOST_CHECK(vector == sortedDescendingVector);
}

BOOST_FIXTURE_TEST_CASE(testBubbleSortWithAtPolicy, SortFixture)
{
  details::bubbleSort <AtPolicy>(vector, details::SortType::ASCENDING);
  BOOST_CHECK(vector == sortedAscendingVector);
  details::bubbleSort <AtPolicy>(vector, details::SortType::DESCENDING);
  BOOST_CHECK(vector == sortedDescendingVector);
}

BOOST_FIXTURE_TEST_CASE(testBubbleSortWithItPolicy, SortFixture)
{
  details::bubbleSort <ItPolicy>(list, details::SortType::ASCENDING);
  BOOST_CHECK(list == sortedAscendingList);
  details::bubbleSort <ItPolicy>(list, details::SortType::DESCENDING);
  BOOST_CHECK(list == sortedDescendingList);
}

BOOST_AUTO_TEST_CASE(testFillRandom)
{
  double * array = nullptr;
  BOOST_CHECK_THROW(details::fillRandom(array, SIZE), std::invalid_argument);
  std::vector<double> vector(SIZE);
}

BOOST_FIXTURE_TEST_CASE(testPrint, Redirecting)
{
  std::vector<int> emptyVector;
  BOOST_CHECK_NO_THROW(print(emptyVector, std::cout));
  std::list<int> emptyList;
  BOOST_CHECK_NO_THROW(print(emptyList, std::cout));
  std::vector<int> vector = {1, 4, 8, 9, 10, -8, 445};
  print(vector, std::cout);
  restore();
  BOOST_CHECK(outputStream.str() == "1 4 8 9 10 -8 445 ");
  std::forward_list<int> list = {1, 4, 8, 9, 10, -8, 445};
  print(list, std::cout);
  restore();
  BOOST_CHECK(outputStream.str() == "1 4 8 9 10 -8 445 ");
}

BOOST_AUTO_TEST_SUITE_END()
