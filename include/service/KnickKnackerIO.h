/**
* @class KnickKnackerIO
* @brief
* This class is meant to act as a broker for reading and writing
* for our issue tracking system.
* @author $Author: Victor Besson $
*/

#ifndef KNICKNACKERIO_H
#define KNICKNACKERIO_H

#define DIR_ISSUES "dat/issues.csv"
#define DIR_USERS "dat/users.csv"
#define DIR_COMMENTS "dat/comments.csv"
#define DAT_DIR "dat";

#include <fstream>
#include <vector>
#include <string>
#include "Issue.h"
#include "Comment.h"
#include "User.h"

class KnickKnackerIO {
 public:
  /**
  * Constructor.
  */
  KnickKnackerIO() {}
  /**
  * Destructor.
  */
  virtual ~KnickKnackerIO() {}
  /**
  * Reads issues.csv and loads all issues into issue vector
  * @return Vector of Issue.
  */
  virtual std::vector<Issue*> readAllIssues();
  /**
  * Reads issues.csv and returns issue with given id.
  * @param id Unsigned int value of id for issue.
  * @return Issue with given id.
  */
  virtual Issue* getIssueByID(unsigned int id);
  /**
  * Reads comments.csv and loads all comments into into comment vector
  * @return Vector of Comment.
  */
  virtual std::vector<Comment*> readAllComments();
  /**
  * Reads users.csv and loads all users into into user vector
  * @return Vector of User.
  */
  virtual std::vector<User*> readAllUsers();
  /**
  * Writes vector of Issue to issues.csv.
  * @param issues The vector of Issue to add to file.
  */
  virtual void overwriteIssues(std::vector<Issue*> issues);
  /**
  * Writes vector of Comment to comments.csv
  * @param comments The vector of Comment to add to file.
  */
  virtual void overwriteComments(std::vector<Comment*> comments);
  /**
  * Writes issue to users.csv.
  * @param users The vector of User to add to file.
  */
  virtual void overwriteUsers(std::vector<User*> users);
  /**
  * Writes issue to issues.csv.
  * @param issue The Issue to add to file.
  */
  virtual void appendIssue(Issue* issue);
  /**
  * Write comment to comments.csv.
  * @param comment The Comment to add to file.
  */
  virtual void appendComment(Comment* comment);
  /**
  * Write user to users.csv.
  * @param user The User to add to file.
  */
  virtual void appendUser(User* user);

 private:
  /**
  * Converts String to Issue::Priority value;
  * @return Issue::Priority value of string.
  * @param s The String to convert to Issue::Priority.
  */
  Issue::Priority convertToPriority(const std::string& s);
  /**
  * Converts String to Issue::Status value;
  * @return Issue::Status value of string.
  * @param s The String to convert to Issue::Status.
  */
  Issue::Status convertToStatus(const std::string& s);
  /**
  * Checks if DAT_DIR exists and if it doesn't creates it.
  * https://stackoverflow.com/questions/18100097/portable-way-to-check-if-directory-exists-windows-linux-c
  * https://stackoverflow.com/questions/20358455/cross-platform-way-to-make-a-directory
  */
  void dirExists();
  /**
  * Converts string to lowercase.
  * @return The string coverted to lowercase.
  * @param input String to convert to lowercase.
  */
  std::string toLower(std::string input);
  /**
  * Checks if string is unsigned integer.
  * @return The boolean value of the comparison.
  * @param s String to check if it is unsigned integer.
  */
  bool is_number(const std::string& s);
};

#endif // KNICKNACKERIO_H
