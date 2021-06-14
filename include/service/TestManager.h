/**
* @class TestManager
* @brief
* This class is meant for real time testing
* will primarily be used by me.
* @author $Author: Victor Besson $
*/

#ifndef TESTMANAGER_H
#define TESTMANAGER_H

#include "Issue.h"
#include "User.h"
#include "Comment.h"
#include "KnickKnacker.h"
#include "KnickKnackerIO.h"
#include <string>
#include <vector>
class TestManager {
 public:
  /**
  * Constructor.
  */
  TestManager() {}
  /**
  * Destructor.
  */
  virtual ~TestManager() {}
  /**
  * Start the testManager loop.
  */
  void startTestManager();
  /**
  * Formats commands into integers.
  * @return Vector of int to be for commands in testManager.
  * @param command String to format into command.
  */
  std::vector<int> formatCommand(std::string command);
  /**
  * Add single user to users.csv
  */
  void addUserToFile();
  /**
  * Add single isse to issues.csv
  */
  void addIssueToFile();
  /**
  * Add single comment to comments.csv
  */
  void addCommentToFile();
  /**
  * Add 10 users to users.csv
  */
  void addUsersToFile();
  /**
  * Add 10 issues to issues.csv
  */
  void addIssuesToFile();
  /**
  * Add 10 comments to comments.csv
  */
  void addCommentsToFile();
  /**
  * reads issues.csv and outputs to console
  */
  void readAllIssues();
  /**
  * reads users.csv and outputs to console
  */
  void readAllUsers();
  /**
  * reads comments.csv and outputs to console
  */
  void readAllComments();
};

#endif // TESTMANAGER_H
