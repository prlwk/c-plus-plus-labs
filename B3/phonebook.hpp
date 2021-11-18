#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <string>
#include <list>

class PhoneBook
{
public:
  struct Contact
  {
    std::string name;
    std::string number;
  };

  using iterator = std::list<Contact>::iterator;
  using const_iterator = std::list<Contact>::const_iterator;

  void insertBefore(iterator iterator, const std::string& name, const std::string& number);
  void insertAfter(iterator iterator, const std::string& name, const std::string& number);
  void pushBack(const std::string& name, const std::string& number);
  void changeRecording(iterator iterator, const std::string& name, const std::string& number);
  void remove(iterator iterator);
  void show(const iterator& iter, std::ostream &out) const;
  bool empty() const;

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

private:
  std::list<Contact> phoneBook_;
};

#endif
