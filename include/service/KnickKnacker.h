/**
* @class KnickKnacker
* @brief
* This class is meant to act as the main service of our issue
* tracking system.
* @author $Author: Victor Besson $
*/

#ifndef KNICKNACKER_H
#define KNICKNACKER_H

#include "KnickKnackerIO.h"
#include "Issue.h"
#include "User.h"
#include <vector>
#include <string>

class KnickKnacker {
 public:
  /**
  * Constructor.
  */
  KnickKnacker() : broker(new KnickKnackerIO()) {}
  /**
  * Constructor for testing.
  * @param b KnickKnackerIO used as the broker for the service.
  */
  KnickKnacker(KnickKnackerIO* b) : broker(b) {}
  /**
  * Destructor.
  */
  virtual ~KnickKnacker();
  /**
  * Creates and persists a new issue
  * @param title The title of the issue
  * @param desc A description of the issue
  * @param status The status of the issue
  * @param priority The priority of the issue
  * @return The unique identifier value of the created issue
  */
  unsigned int createIssue(std::string title, std::string desc,
    Issue::Status status, Issue::Priority priority);
  /**
  * Gets the issue specified by issue ID
  * @param id The unique identifier value of the issue
  * @return The issue matching the ID, nullptr if no match found
  */
  Issue getIssueByID(unsigned int id);
  /**
  * Updates the attributes in an issue matching the ID to the
  * values specified
  * @param id The ID of the issue to update
  * @param title The new title of the issue, empty string if unchanged
  * @param desc The new description of the issue, empty string if unchanged
  * @param status The new status of the issue
  * @param priority The new priority of the issue
  * @return The updated issue object, nullptr if the ID does not match
  *   any records
  */
  bool updateIssue(unsigned int id, std::string title,
    std::string desc, Issue::Status status, Issue::Priority priority);
  /**
  * Deletes an issue matching the ID
  * @param id The unique identifier of the issue to delete
  * @return true if the issue was successfully deleted
  */
  bool deleteIssueByID(unsigned int id);
  /**
  * Returns all the issues in a list
  * @return a list of all the issues
  */
  std::vector<Issue> getAllIssues();

 private:
  /**
  * broker to be used for IO
  */
  KnickKnackerIO* broker;
};

#endif // KNICKNACKER_H
