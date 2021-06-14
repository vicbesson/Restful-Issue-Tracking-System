/**
* @class Issue
* @brief
* This class is meant to act as a issue in our issue tracking
* system.
* @author $Author: Victor Besson $
*/

#ifndef ISSUE_H
#define ISSUE_H

#include "Comment.h"
#include "User.h"
#include <string>
#include <vector>

class Issue {
 public:
  /**
  * Enum used for status of issue.
  */
  enum Status {New, Assigned, WontFix, SLast};
  /**
  * Enum used for priority of issue.
  */
  enum Priority {Low, Medium, High, Top, PLast};
  /**
  * Constructor.
  */
  Issue() {}
  /**
  * Constructor.
  * @param i Unsigned int to set id.
  * @param t String to set title.
  * @param d String to set description.
  * @param u Unsigned int to set user.
  * @param s Unsigned int to set status.
  * @param p Unsigned int to set priority.
  * @param o String to set os.
  */
  Issue(unsigned int i, std::string t, std::string d, unsigned int u, Status s,
  Priority p, std::string o) :
  id(i), title(t), description(d), userID(u), status(s), priority(p), os(o) {}
  /**
  * Constructor.
  * @param i Unsigned int to set id.
  * @param t String to set title.
  * @param d String to set description.
  * @param s Unsigned int to set status.
  * @param p Unsigned int to set priority.
  */
  Issue(unsigned int i, std::string t, std::string d, Status s,
  Priority p) :
  id(i), title(t), description(d), status(s), priority(p), os("No OS") {}
  /**
  * Destructor.
  */
  virtual ~Issue();
  /**
  * Setter for title
  * @param t String to set title of issue.
  */
  void updateTitle(std::string t) { title = t; }
  /**
  * Setter for description
  * @param d String to set description of issue.
  */
  void updateDescription(std::string d) { description = d; }
  /**
  * Setter for status
  * @param s Status to set status of issue.
  */
  void updateStatus(Status s) { status = s; }
  /**
  * Setter for priority
  * @param p Priority to set priority of issue.
  */
  void updatePriority(Priority p) { priority = p; }
  /**
  * Setter for os
  * @param o String to set os of issue.
  */
  void updateOS(std::string o) { os = o; }
  /**
  * Getter for id
  * @return The unsigned int value of the id of the issue.
  */
  unsigned int getID() { return id; }
  /**
  * Getter for title
  * @return The string value of the title of the issue.
  */
  std::string getTitle() { return title; }
  /**
  * Getter for description
  * @return The string value of the description of the issue.
  */
  std::string getDescription() { return description; }
  /**
  * Getter for userID of user assigned to issue.
  * @return The unsigned int value of the
  * userID of user assigned to issue.
  */
  unsigned int getUserID() { return userID; }
  /**
  * Getter for status
  * @return The string value for the status of issue.
  */
  std::string getStatus();
  /**
   * Getter for status as enum
   * @return The enum value for the status of the issue.
   */
  Status getStatusEnum() { return status; }
  /**
  * Getter for priority
  * @return The string value for the priority of issue.
  */
  std::string getPriority();
  /**
   * Getter for priority as enum
   * @return The enum value for the priority of the issue.
   */
  Priority getPriorityEnum() { return priority; }
  /**
  * Getter for os.
  * @return The os associated with issue.
  */
  std::string getOS() { return os; }
  /**
  * Add comment to issue
  * @param c Comment to add to issue.
  */
  void addComment(Comment* c);
  /**
  * Delete comment from issue
  * @param index Index of comment to delete.
  */
  void deleteComment(unsigned int index);
  /**
  * Delete comment from issue
  * @return vector of Comment that are the comments in the issue.
  */
  std::vector<Comment*> getComments();
  /**
  * Returns the comment at index
  * @param index Index of comment to get.
  * @return Comment at index.
  */
  Comment* getComment(unsigned index);

 private:
  /**
  * ID of issue.
  */
  unsigned int id;
  /**
  * Title of issue.
  */
  std::string title;
  /**
  * Description of issue.
  */
  std::string description;
  /**
  * id of user assigned with issue.
  */
  unsigned int userID;
  /**
  * Comments associated with issue.
  */
  std::vector<Comment*> comments;
  /**
  * Status of issue.
  */
  Status status;
  /**
  * Priority of issue.
  */
  Priority priority;
  /**
  * Operating system the issue is occuring on.
  */
  std::string os;
};

#endif // ISSUE_H
