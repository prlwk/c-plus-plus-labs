#include <vector>
#include <forward_list>
#include <stdexcept>
#include <boost/test/unit_test.hpp>

#include "utility.hpp"
#include "policy.hpp"

BOOST_AUTO_TEST_SUITE(testPolicy)

const size_t INDEX = 3;
const size_t INVALID_INDEX = 10;
const int ITEM_BY_INDEX = -1;
const int ITEM_BY_ITER = 83;

struct Fixture
{
  Fixture() :
  vector({-10, 98, 97, -1, 1, -12}),
  list({26, 83, 99, -1, 88, 99, 0, -99})
  {}

  std::vector <int> vector;
  std::forward_list <int> list;
};

BOOST_FIXTURE_TEST_CASE(testFunctionalBracketsPolicy, Fixture)
{
  BOOST_CHECK_EQUAL(0, BracketsPolicy<std::vector<int>>::begin(vector));
  BOOST_CHECK_EQUAL(vector.size(), BracketsPolicy<std::vector<int>>::end(vector));
  BOOST_CHECK_EQUAL(ITEM_BY_INDEX, BracketsPolicy<std::vector<int>>::get(vector, INDEX));
  BOOST_CHECK_THROW(BracketsPolicy<std::vector<int>>::get(vector, INVALID_INDEX), std::out_of_range);
}

BOOST_FIXTURE_TEST_CASE(testFunctionalAtPolicy, Fixture)
{
  BOOST_CHECK_EQUAL(0, AtPolicy<std::vector<int>>::begin(vector));
  BOOST_CHECK_EQUAL(vector.size(), AtPolicy<std::vector<int>>::end(vector));
  BOOST_CHECK_EQUAL(ITEM_BY_INDEX, AtPolicy<std::vector<int>>::get(vector, INDEX));
  BOOST_CHECK_THROW(AtPolicy<std::vector<int>>::get(vector, INVALID_INDEX), std::out_of_range);
}

BOOST_FIXTURE_TEST_CASE(testFunctionalItPolicy, Fixture)
{
  BOOST_CHECK(list.begin() == ItPolicy<std::forward_list<int>>::begin(list));
  BOOST_CHECK(list.end() == ItPolicy<std::forward_list<int>>::end(list));
  std::forward_list<int>::iterator it = list.begin();
  it++;
  BOOST_CHECK(*it == ItPolicy<std::forward_list<int>>::get(list, it));
}

BOOST_AUTO_TEST_SUITE_END()
