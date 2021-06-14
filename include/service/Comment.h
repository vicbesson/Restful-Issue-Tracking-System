/**
* @class Comment
* @brief
* This class is meant to act as a comment in an issue in
* our issue tracking system.
* @author $Author: Victor Besson $
*/

#ifndef COMMENT_H
#define COMMENT_H

#include "User.h"
#include <string>

class Comment {
 public:
  /**
  * Constructor.
  * @param i Unsigned int value of comment id.
  * @param is Unsigned int value of issue id comment is assigned to.
  * @param u User to set user.
  * @param v String to set comment value.
  */
  Comment(unsigned int i, unsigned int is, unsigned int u, std::string v)
  : id(i), issueID(is), userID(u), value(v) {}
  /**
  * Destructor.
  */
  virtual ~Comment() {}
  /**
  * Getter for id of the comment assigned to an issue.
  * @return The unsigned int value for the
  * id of the comment.
  */
  unsigned int getID() { return id; }
  /**
  * Getter for id of the issue the comment is assigned to.
  * @return The unsigned int value for the
  * id of the issue the comment is assigned to.
  */
  unsigned int getIssueID() { return issueID; }
  /**
  * Getter for userID of user assigned to issue.
  * @return The unsigned int value for the
  * userID of user assigned to issue.
  */
  unsigned int getUserID() { return userID; }
  /**
  * Getter for value of comment.
  * @return The string value of the comment.
  */
  std::string getValue() { return value; }

 private:
  /**
  * The id of the comment to be used for the filesystem.
  */
  unsigned int id;
  /**
  * The id of the issue the comment is assigned to.
  */
  unsigned int issueID;
  /**
  * User associated with comment
  */
  unsigned int userID;
  /**
  * The value of the comment as string.
  */
  std::string value;
};

#endif // COMMENT_H
