#include <stdexcept>
#include <sstream>
#include <boost/test/unit_test.hpp>

#include "phonebook-interface.hpp"
#include "parcer.hpp"

BOOST_AUTO_TEST_SUITE(testParcer)

const std::string invalidCommand = "<INVALID COMMAND>\n";
const std::string invalidStep = "<INVALID STEP>\n";
const std::string invalidCommand1 = "go";

const std::string invalidStrForAdd1 = "add 8980345a67 Nastia";
const std::string invalidStrForAdd2 = "add 8980345867";
const std::string invalidStrForAdd3 = "add 8980345867 Nastia";
const std::string invalidStrForAdd4 = "add 8980345867 \"Nastia";
const std::string rightStrForAdd = "add 8980345867 \"Nastia\"";
const std::string rightStrForAdd2 = "add 8980345867 \"Nastia \"Molchanova\"\"";

const std::string invalidStrForStore = "store current info%";
const std::string invalidStrForStore2 = "store info% current";
const std::string rightStrForStore = "store current work";

const std::string invalidStrForInsert = "insert otherplace current 88888 \"Nastia\"";
const std::string invalidStrForInsert2 = "insert before cur%rent 88888 \"Nastia\"";
const std::string invalidStrForInsert3 = "insert before current 88f888 \"Nastia\"";
const std::string invalidStrForInsert4 = "insert before current 88888 \"Nastia";
const std::string rightStrForInsert = "insert before current 88888 \"Nastia\"";

const std::string invalidStrForDelete = "delete current@";
const std::string rightStrForDelete = "delete current";

const std::string invalidStrForShow = "show current@";
const std::string rightStrForShow = "show current";

const std::string invalidStrForMove = "move current@ first";
const std::string invalidStrForMove1 = "move current second";
const std::string invalidStrForMove2 = "move current 5.8";
const std::string rightStrForMove = "move current last";

const std::string name1 = "Anastasia";
const std::string number1 = "111111111";
const std::string name2 = "Alex";
const std::string number2 = "222222222";

struct Fixture
{
  Fixture()
  {
    userInterface.add(name1, number1);
    userInterface.add(name2, number2);
    userInterface.add(name1, number2);
  }
  PhoneBookInterface userInterface;
};

BOOST_FIXTURE_TEST_CASE(testInvalidNameCommand, Fixture)
{
  std::istringstream stream;
  std::ostringstream outputStream;
  stream.str(invalidCommand1);
  CommandType command;
  stream >> command;
  command(userInterface, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), invalidCommand);
}

BOOST_FIXTURE_TEST_CASE(testParseAdd, Fixture)
{
  std::istringstream stream;
  std::ostringstream outputStream;
  stream.str(invalidStrForAdd1);
  CommandType command;
  stream >> command;
  command(userInterface, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), invalidCommand);

  std::istringstream stream2;
  std::ostringstream outputStream2;
  stream2.str(invalidStrForAdd2);
  CommandType command2;
  stream2 >> command2;
  command2(userInterface, outputStream2);
  BOOST_CHECK_EQUAL(outputStream2.str(), invalidCommand);

  std::istringstream stream4;
  std::ostringstream outputStream4;
  stream4.str(invalidStrForAdd3);
  CommandType command4;
  stream4 >> command4;
  command4(userInterface, outputStream4);
  BOOST_CHECK_EQUAL(outputStream4.str(), invalidCommand);

  std::istringstream stream5;
  std::ostringstream outputStream5;
  stream5.str(invalidStrForAdd4);
  CommandType command5;
  stream5 >> command5;
  command5(userInterface, outputStream5);
  BOOST_CHECK_EQUAL(outputStream5.str(), invalidCommand);

  std::istringstream stream6;
  std::ostringstream outputStream6;
  stream6.str(rightStrForAdd);
  CommandType command6;
  stream6 >> command6;
  BOOST_CHECK_NO_THROW(command6(userInterface, outputStream6));

  std::istringstream stream7;
  std::ostringstream outputStream7;
  stream7.str(rightStrForAdd2);
  CommandType command7;
  stream7 >> command7;
  BOOST_CHECK_NO_THROW(command7(userInterface, outputStream7));
}

BOOST_FIXTURE_TEST_CASE(testParseStore, Fixture)
{
  std::istringstream stream;
  std::ostringstream outputStream;
  stream.str(invalidStrForStore);
  CommandType command;
  stream >> command;
  command(userInterface, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), invalidCommand);

  std::istringstream stream2;
  std::ostringstream outputStream2;
  stream2.str(invalidStrForStore2);
  CommandType command2;
  stream2 >> command2;
  command2(userInterface, outputStream2);
  BOOST_CHECK_EQUAL(outputStream2.str(), invalidCommand);

  std::istringstream stream4;
  std::ostringstream outputStream4;
  stream4.str(rightStrForStore);
  CommandType command4;
  stream4 >> command4;
  BOOST_CHECK_NO_THROW(command4(userInterface, outputStream4));
}

BOOST_FIXTURE_TEST_CASE(testParseInsert, Fixture)
{
  std::istringstream stream;
  std::ostringstream outputStream;
  stream.str(invalidStrForInsert);
  CommandType command;
  stream >> command;
  command(userInterface, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), invalidCommand);

  std::istringstream stream2;
  std::ostringstream outputStream2;
  stream2.str(invalidStrForInsert2);
  CommandType command2;
  stream2 >> command2;
  command2(userInterface, outputStream2);
  BOOST_CHECK_EQUAL(outputStream2.str(), invalidCommand);

  std::istringstream stream3;
  std::ostringstream outputStream3;
  stream3.str(invalidStrForInsert3);
  CommandType command3;
  stream3 >> command3;
  command3(userInterface, outputStream3);
  BOOST_CHECK_EQUAL(outputStream3.str(), invalidCommand);

  std::istringstream stream4;
  std::ostringstream outputStream4;
  stream4.str(invalidStrForInsert4);
  CommandType command4;
  stream4 >> command4;
  command4(userInterface, outputStream4);
  BOOST_CHECK_EQUAL(outputStream4.str(), invalidCommand);

  std::istringstream stream5;
  std::ostringstream outputStream5;
  stream5.str(rightStrForInsert);
  CommandType command5;
  stream5 >> command5;
  BOOST_CHECK_NO_THROW(command5(userInterface, outputStream5));
}

BOOST_FIXTURE_TEST_CASE(testParseDelete, Fixture)
{
  std::istringstream stream;
  std::ostringstream outputStream;
  stream.str(invalidStrForDelete);
  CommandType command;
  stream >> command;
  command(userInterface, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), invalidCommand);

  std::istringstream stream2;
  std::ostringstream outputStream2;
  stream2.str(rightStrForDelete);
  CommandType command2;
  stream2 >> command2;
  BOOST_CHECK_NO_THROW(command2(userInterface, outputStream2));
}

BOOST_FIXTURE_TEST_CASE(testParseShow, Fixture)
{
  std::istringstream stream;
  std::ostringstream outputStream;
  stream.str(invalidStrForShow);
  CommandType command;
  stream >> command;
  command(userInterface, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), invalidCommand);

  std::istringstream stream2;
  std::ostringstream outputStream2;
  stream2.str(rightStrForShow);
  CommandType command2;
  stream2 >> command2;
  BOOST_CHECK_NO_THROW(command2(userInterface, outputStream2));
}

BOOST_FIXTURE_TEST_CASE(testParseMove, Fixture)
{
  std::istringstream stream;
  std::ostringstream outputStream;
  stream.str(invalidStrForMove);
  CommandType command;
  stream >> command;
  command(userInterface, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), invalidCommand);

  std::istringstream stream2;
  std::ostringstream outputStream2;
  stream2.str(invalidStrForMove1);
  CommandType command2;
  stream2 >> command2;
  command2(userInterface, outputStream2);
  BOOST_CHECK_EQUAL(outputStream2.str(), invalidStep);

  std::istringstream stream3;
  std::ostringstream outputStream3;
  stream3.str(invalidStrForMove2);
  CommandType command3;
  stream3 >> command3;
  command3(userInterface, outputStream3);
  BOOST_CHECK_EQUAL(outputStream3.str(), invalidStep);

  std::istringstream stream4;
  std::ostringstream outputStream4;
  stream4.str(rightStrForMove);
  CommandType command4;
  stream4 >> command4;
  BOOST_CHECK_NO_THROW(command4(userInterface, outputStream4));
}

BOOST_AUTO_TEST_CASE(testIsNumberValid)
{
  std::string number = "12345678";
  std::string number1 = "1234f456";
  std::string number2 = "1234456%";

  BOOST_CHECK(detail::isNumberValid(number));
  BOOST_CHECK(!(detail::isNumberValid(number1)));
  BOOST_CHECK(!(detail::isNumberValid(number2)));
}

BOOST_AUTO_TEST_CASE(testIsMarkNameValid)
{
  std::string markName = "current";
  std::string markName1 = "current-important";
  std::string markName2 = "current-important45";
  std::string markName3 = "current-important45%";

  BOOST_CHECK(detail::isMarkNameValid(markName));
  BOOST_CHECK(detail::isMarkNameValid(markName1));
  BOOST_CHECK(detail::isMarkNameValid(markName2));
  BOOST_CHECK(!(detail::isMarkNameValid(markName3)));
}

BOOST_FIXTURE_TEST_CASE(testPrintCommands, Fixture)
{
  std::ostringstream outputStream;
  printInvalidCommand(userInterface, outputStream);
  BOOST_CHECK_EQUAL(outputStream.str(), invalidCommand);

  std::ostringstream outputStream2;
  printInvalidStep(userInterface, outputStream2);
  BOOST_CHECK_EQUAL(outputStream2.str(), invalidStep);
}

BOOST_AUTO_TEST_SUITE_END()
