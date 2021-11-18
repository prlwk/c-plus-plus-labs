#include <stdexcept>
#include <sstream>
#include <boost/test/unit_test.hpp>
#include "phonebook.hpp"

BOOST_AUTO_TEST_SUITE(testPhoneBook)

const std::string name1 = "Anastasia";
const std::string number1 = "111111111";
const std::string name2 = "Alex";
const std::string number2 = "222222222";
const std::string name3 = "Ann";
const std::string number3 = "333";
const std::string emptyName;
const std::string emptyNumber;

struct Fixture
{
  Fixture()
  {
    phoneBook.pushBack(name1, number1);
    phoneBook.pushBack(name2, number2);
  }
  PhoneBook phoneBook;
};

BOOST_FIXTURE_TEST_CASE(testBeginAndEnd, Fixture)
{
  BOOST_CHECK(phoneBook.begin()->name == name1);
  BOOST_CHECK(phoneBook.begin()->number == number1);
  BOOST_CHECK(std::prev(phoneBook.end())->name == name2);
  BOOST_CHECK(std::prev(phoneBook.end())->number == number2);
}

BOOST_FIXTURE_TEST_CASE(testRemoveMethod, Fixture)
{
  auto iterator = phoneBook.begin();
  phoneBook.remove(iterator);
  BOOST_CHECK(phoneBook.begin()->name == name2);
  BOOST_CHECK(phoneBook.begin()->number == number2);
}

BOOST_FIXTURE_TEST_CASE(testInsertBeforeMethod, Fixture)
{
  auto iterator = phoneBook.begin();
  phoneBook.insertBefore(iterator, name3, number3);
  BOOST_CHECK(phoneBook.begin()->name == name3);
  BOOST_CHECK(phoneBook.begin()->number == number3);
  BOOST_CHECK_THROW(phoneBook.insertBefore(iterator, emptyName, number1), std::invalid_argument);
  BOOST_CHECK_THROW(phoneBook.insertBefore(iterator, name1, emptyNumber), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(testInsertAfterMethod, Fixture)
{
  auto iterator = phoneBook.begin();
  phoneBook.insertAfter(iterator, name3, number3);
  BOOST_CHECK(std::next(iterator)->name == name3);
  BOOST_CHECK(std::next(iterator)->number == number3);
  BOOST_CHECK_THROW(phoneBook.insertAfter(iterator, emptyName, number1), std::invalid_argument);
  BOOST_CHECK_THROW(phoneBook.insertAfter(iterator, name1, emptyNumber), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(testPushBack, Fixture)
{
  phoneBook.pushBack(name3, number3);
  BOOST_CHECK(std::prev(phoneBook.end())->name == name3);
  BOOST_CHECK(std::prev(phoneBook.end())->number == number3);
  BOOST_CHECK_THROW(phoneBook.pushBack(emptyName, number1), std::invalid_argument);
  BOOST_CHECK_THROW(phoneBook.pushBack(name1, emptyNumber), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(testChangeRecording, Fixture)
{
  auto iterator = phoneBook.begin();
  phoneBook.changeRecording(iterator, name3, number3);
  BOOST_CHECK(phoneBook.begin()->name == name3);
  BOOST_CHECK(phoneBook.begin()->number == number3);
  BOOST_CHECK_THROW(phoneBook.changeRecording(iterator, emptyName, number1), std::invalid_argument);
  BOOST_CHECK_THROW(phoneBook.changeRecording(iterator, name1, emptyNumber), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testEmpty)
{
  PhoneBook book;
  BOOST_CHECK(book.empty() == 1);
  book.pushBack(name3, number3);
  BOOST_CHECK(book.empty() == 0);
}

BOOST_FIXTURE_TEST_CASE(testPrint, Fixture)
{
  auto iter = phoneBook.begin();
  std::ostringstream outputStream;
  phoneBook.show(iter, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), number1 + " " + name1 + "\n");
}

BOOST_AUTO_TEST_SUITE_END()
