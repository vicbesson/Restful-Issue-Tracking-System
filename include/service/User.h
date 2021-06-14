/**
* @class User
* @brief
* This class is meant to act as a user in our issue tracking
* system.
* @author $Author: Victor Besson $
*/

#ifndef USER_H
#define USER_H

#include <string>

class User {
 public:
  /**
  * Constructor.
  * @param i Unsigned int to set id.
  * @param f String to set firstName.
  * @param l String to set lastName.
  * @param u String to set username.
  */
  User(unsigned int i, std::string f, std::string l, std::string u)
  : id(i), firstName(f), lastName(l), username(u) {}
  /**
  * Destructor.
  */
  virtual ~User() {}
  /**
  * Setter for firstName
  * @param f String to set firstName of user.
  */
  void updateFirstName(std::string f) { firstName = f; }
  /**
  * Setter for lastName
  * @param l String to set lastName of user.
  */
  void updateLastName(std::string l) { lastName = l; }
  /**
  * Setter for username
  * @param u String to set username of user.
  */
  void updateUsername(std::string u) { username = u; }
  /**
  * Getter for id.
  * @return Unsigned int value of id.
  */
  unsigned int getID() { return id; }
  /**
  * Getter for full name of user.
  * @return The string value of the users full name.
  */
  std::string getFullName() { return (firstName + " " + lastName); }
  /**
  * Getter for first name of user.
  * @return The string value of the users first name.
  */
  std::string getFirstName() { return firstName; }
  /**
  * Getter for last name of user.
  * @return The string value of the users last name.
  */
  std::string getLastName() { return lastName; }
  /**
  * Getter for username.
  * @return The string value of the username of user.
  */
  std::string getUsername() { return username; }

 private:
  /**
  * ID of user.
  */
  unsigned int id;
  /**
  * First name of user.
  */
  std::string firstName;
  /**
  * Last name of user.
  */
  std::string lastName;
  /**
  * Username of user.
  */
  std::string username;
};

#endif // USER_H
