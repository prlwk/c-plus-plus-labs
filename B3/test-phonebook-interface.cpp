#include <iostream>
#include <sstream>
#include <boost/test/unit_test.hpp>

#include "phonebook-interface.hpp"

BOOST_AUTO_TEST_SUITE(testUserInterface)

const std::string name1 = "Anastasia";
const std::string number1 = "111111111";
const std::string name2 = "Alex";
const std::string number2 = "222222222";
const std::string name3 = "Ann";
const std::string number3 = "333";
const std::string currentMark = "current";
const std::string mark1 = "important";
const std::string mark2 = "work";
const std::string invalidBookmark = "<INVALID BOOKMARK>\n";
const std::string empty = "<EMPTY>\n";

struct Fixture
{
  Fixture()
  {
    userInterface.add(name1, number1);
    userInterface.add(name2, number2);
    userInterface.add(name3, number3);
    userInterface.add(name1, number2);
    userInterface.add(name2, number1);
  }
  PhoneBookInterface userInterface;
};

BOOST_FIXTURE_TEST_CASE(testShow, Fixture)
{
  const std::string out = "111111111 Anastasia\n";
  std::ostringstream outputStream;
  userInterface.show(currentMark, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), out);
  std::ostringstream outputStream2;
  userInterface.show(mark1, outputStream2);
  BOOST_CHECK_EQUAL(outputStream2.str(), invalidBookmark);
  std::ostringstream outputStream3;
  PhoneBookInterface userInterface1;
  userInterface1.show(currentMark, outputStream3);
  BOOST_CHECK_EQUAL(outputStream3.str(), empty);
}

BOOST_FIXTURE_TEST_CASE(testMoveToPosition, Fixture)
{
  const std::string out1 = "111111111 Anastasia\n";
  std::ostringstream outputStream;
  userInterface.moveToPosition(currentMark, PhoneBookInterface::FIRST, outputStream);
  userInterface.show(currentMark, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), out1);

  const std::string out2 = "111111111 Alex\n";
  std::ostringstream outputStream1;
  userInterface.moveToPosition(currentMark, PhoneBookInterface::LAST, outputStream1);
  userInterface.show(currentMark, outputStream1);
  BOOST_CHECK_EQUAL(outputStream1.str(), out2);

  std::ostringstream outputStream2;
  userInterface.moveToPosition(mark1, PhoneBookInterface::FIRST, outputStream2);
  BOOST_CHECK_EQUAL(outputStream2.str(), invalidBookmark);

  std::ostringstream outputStream3;
  PhoneBookInterface userInterface1;
  userInterface1.moveToPosition(currentMark, PhoneBookInterface::FIRST, outputStream3);
  BOOST_CHECK_EQUAL(outputStream3.str(), empty);
}

BOOST_FIXTURE_TEST_CASE(testInsertAfterMethod, Fixture)
{
  const std::string out = "111111111 Ann\n";
  std::ostringstream outputStream;
  userInterface.moveToPosition(currentMark, PhoneBookInterface::LAST, outputStream);
  userInterface.insertAfter(currentMark, name3, number1, outputStream);
  userInterface.moveToPosition(currentMark, PhoneBookInterface::LAST, outputStream);
  userInterface.show(currentMark, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), out);
  std::ostringstream outputStream2;
  userInterface.insertAfter(mark1, name3, number1, outputStream2);
  BOOST_CHECK_EQUAL(outputStream2.str(), invalidBookmark);
}

BOOST_FIXTURE_TEST_CASE(testInsertBeforeMethod, Fixture)
{
  const std::string out = "111111111 Ann\n";
  std::ostringstream outputStream;
  userInterface.insertBefore(currentMark, name3, number1, outputStream);
  userInterface.moveToPosition(currentMark, PhoneBookInterface::FIRST, outputStream);
  userInterface.show(currentMark, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), out);
  std::ostringstream outputStream2;
  userInterface.insertBefore(mark1, name3, number1, outputStream2);
  BOOST_CHECK_EQUAL(outputStream2.str(), invalidBookmark);
}

BOOST_FIXTURE_TEST_CASE(testStoreMethod, Fixture)
{
  const std::string out = "111111111 Anastasia\n";
  std::ostringstream outputStream;
  userInterface.store(mark1, mark2, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), invalidBookmark);
  std::ostringstream outputStream2;
  userInterface.store(currentMark, mark1, outputStream2);
  userInterface.show(mark1, outputStream2);
  BOOST_CHECK_EQUAL(outputStream2.str(), out);
}

BOOST_FIXTURE_TEST_CASE(testRemoveMethod, Fixture)
{
  const std::string out = "222222222 Anastasia\n";
  std::ostringstream outputStream;
  userInterface.moveToPosition(currentMark, PhoneBookInterface::LAST, outputStream);
  userInterface.remove(currentMark, outputStream);
  userInterface.moveToPosition(currentMark, PhoneBookInterface::LAST, outputStream);
  userInterface.show(currentMark, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), out);

  std::ostringstream outputStream2;
  userInterface.remove(mark1, outputStream2);
  BOOST_CHECK_EQUAL(outputStream2.str(), invalidBookmark);

  std::ostringstream outputStream3;
  PhoneBookInterface userInterface1;
  userInterface1.remove(currentMark, outputStream3);
  BOOST_CHECK_EQUAL(outputStream3.str(), empty);
}

BOOST_FIXTURE_TEST_CASE(testMoveMethod, Fixture)
{
  const std::string out = "333 Ann\n";
  std::ostringstream outputStream;
  userInterface.move(currentMark, 2, outputStream);
  userInterface.show(currentMark, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), out);

  const std::string out1 = "111111111 Anastasia\n";
  std::ostringstream outputStream1;
  userInterface.moveToPosition(currentMark, PhoneBookInterface::LAST, outputStream1);
  userInterface.move(currentMark, -5, outputStream1);
  userInterface.show(currentMark, outputStream1);
  BOOST_CHECK_EQUAL(outputStream1.str(), out1);

  std::ostringstream outputStream2;
  userInterface.move(mark1, 5, outputStream2);
  BOOST_CHECK_EQUAL(outputStream2.str(), invalidBookmark);

  std::ostringstream outputStream3;
  PhoneBookInterface userInterface1;
  userInterface1.move(currentMark, 5,outputStream3);
  BOOST_CHECK_EQUAL(outputStream3.str(), empty);

  const std::string out2 = "111111111 Anastasia\n";
  std::ostringstream outputStream4;
  userInterface.moveToPosition(currentMark, PhoneBookInterface::LAST, outputStream4);
  userInterface.move(currentMark, -50, outputStream4);
  userInterface.show(currentMark, outputStream4);
  BOOST_CHECK_EQUAL(outputStream4.str(), out2);
}

BOOST_AUTO_TEST_SUITE_END()
