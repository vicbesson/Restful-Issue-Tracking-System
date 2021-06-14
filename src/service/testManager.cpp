#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "TestManager.h"

bool is_number(const std::string& s);

void TestManager::startTestManager() {
  bool play = true;
  // User input converted into integers
  // input[0] command to switch on in the main loop
  std::vector<int> input;
  std::string command;
  while (play) {
    command.clear();
    std::cout << ">>> ";
    while (command[0] == '\n' || command.empty())
        getline(std::cin, command);
    input = formatCommand(command);
    switch (input[0]) {
      // write to file
      case 10:
        addIssueToFile();
        break;
      case 11:
        addUserToFile();
        break;
      case 12:
        addCommentToFile();
        break;
      case 20:
        addIssuesToFile();
        break;
      case 21:
        addUsersToFile();
        break;
      case 22:
        addCommentsToFile();
        break;
      case 30:
        readAllIssues();
        break;
      case 31:
        readAllUsers();
        break;
      case 32:
        readAllComments();
        break;
      case 0:
        std::cout << "bye" << std::endl;
        play = false;
        break;
      default:
        std::cout << "invalid command" << std::endl;
        break;
    }
  }
}

std::vector<int> TestManager::formatCommand(std::string command) {
  std::vector<int> temp;
  std::vector<std::string> tempCommand;
  std::string parsed;
  std::stringstream parser(command);

  while (getline(parser, parsed, ' ')) {
      tempCommand.push_back(parsed);
  }
  for (unsigned int i = 0; i < tempCommand.size(); i++) {
    for (unsigned int c = 0; c < tempCommand[i].size(); c++) {
      tempCommand[i][c] = tolower(tempCommand[i][c]);
    }
  }

  if (tempCommand[0] == "aifile" || tempCommand[0] == "aif") {
      temp.push_back(10);
  } else if (tempCommand[0] == "aufile" || tempCommand[0] == "auf") {
      temp.push_back(11);
  } else if (tempCommand[0] == "acfile" || tempCommand[0] == "acf") {
      temp.push_back(12);
  } else if (tempCommand[0] == "mifile" || tempCommand[0] == "mif") {
      temp.push_back(20);
  } else if (tempCommand[0] == "mufile" || tempCommand[0] == "muf") {
      temp.push_back(21);
  } else if (tempCommand[0] == "mcfile" || tempCommand[0] == "mcf") {
      temp.push_back(22);
  } else if (tempCommand[0] == "rifile" || tempCommand[0] == "rif") {
      temp.push_back(30);
  } else if (tempCommand[0] == "rufile" || tempCommand[0] == "ruf") {
      temp.push_back(31);
  } else if (tempCommand[0] == "rcfile" || tempCommand[0] == "rcf") {
      temp.push_back(32);
  } else if (tempCommand[0] == "exit" || tempCommand[0] == "quit"
  || tempCommand[0] == "e") {
      temp.push_back(0);
  } else {
      temp.push_back(-1);
      return temp;
  }
  // Remove the command  string
  tempCommand.erase(tempCommand.begin());
  // Pushback all the numbers remaining in the command
  if (!tempCommand.empty()) {
      for (auto i : tempCommand) {
          if (is_number(i)) {
              temp.push_back(std::stoi(i));
          }
      }
  }

  if (temp.empty())
    temp.push_back(-1);

  temp.shrink_to_fit();

  return temp;
}

void TestManager::addUserToFile() {
  KnickKnackerIO io;
  User* user = new User(1, "john", "doe", "testname");
  io.appendUser(user);
  delete user;
}

void TestManager::addIssueToFile() {
  KnickKnackerIO io;
  Issue* issue = new Issue(1, "test title", "random description",
  1, Issue::New, Issue::Low, "Windows 10");
  io.appendIssue(issue);
  delete issue;
}

void TestManager::addCommentToFile() {
  KnickKnackerIO io;
  Comment* comment = new Comment(1, 1, 1, "test comment");
  io.appendComment(comment);
  delete comment;
}

void TestManager::addUsersToFile() {
  KnickKnackerIO io;
  std::vector<User*> users;
  User* user = new User(1, "john", "doe", "testname");
  for (unsigned int i = 0; i < 10; i++) {
    users.push_back(user);
  }
  io.overwriteUsers(users);
  delete user;
  users.clear();
}

void TestManager::addIssuesToFile() {
  KnickKnackerIO io;
  std::vector<Issue*> issues;
  Issue* issue = new Issue(1, "test title", "random description",
  1, Issue::New, Issue::Low, "Windows 10");
  for (unsigned int i = 0; i < 10; i++) {
    issues.push_back(issue);
  }
  io.overwriteIssues(issues);
  delete issue;
  issues.clear();
}

void TestManager::addCommentsToFile() {
  KnickKnackerIO io;
  std::vector<Comment*> comments;
  Comment* comment = new Comment(1, 1, 1, "test comment");
  for (unsigned int i = 0; i < 10; i++) {
    comments.push_back(comment);
  }
  io.overwriteComments(comments);
  delete comment;
  comments.clear();
}

void TestManager::readAllIssues() {
  KnickKnackerIO io;
  std::string delimiter = ",";
  std::vector<Issue*> issues = io.readAllIssues();
  for (Issue* i : issues) {
    std::cout
    << i->getID() << delimiter
    << i->getTitle() << delimiter
    << i->getDescription() << delimiter
    << i->getUserID() << delimiter
    << i->getStatus() << delimiter
    << i->getPriority() << delimiter
    << i->getOS()
    << std::endl;
    delete i;
  }
  issues.clear();
}

void TestManager::readAllComments() {
  KnickKnackerIO io;
  std::string delimiter = ",";
  std::vector<Comment*> comments = io.readAllComments();
  for (Comment* c : comments) {
    std::cout
    << c->getID() << delimiter
    << c->getIssueID() << delimiter
    << c->getUserID() << delimiter
    << c->getValue()
    << std::endl;
    delete c;
  }
  comments.clear();
}

void TestManager::readAllUsers() {
  KnickKnackerIO io;
  std::string delimiter = ",";
  std::vector<User*> users = io.readAllUsers();
  for (User* u : users) {
    std::cout
    << u->getID() << delimiter
    << u->getFirstName() << delimiter
    << u->getLastName() << delimiter
    << u->getUsername()
    << std::endl;
    delete u;
  }
  users.clear();
}

bool is_number(const std::string& s) {
  return !s.empty() && std::find_if(s.begin(),
  s.end(), [](unsigned char c) {
    return !std::isdigit(c);
  }) == s.end();
}
