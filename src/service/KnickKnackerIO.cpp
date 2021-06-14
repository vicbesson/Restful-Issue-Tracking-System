#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>
#include <sys/types.h>//NOLINT
#ifdef _WIN32
  #include <direct.h>//NOLINT
#endif
  #include <sys/stat.h>//NOLINT
#include "KnickKnackerIO.h"

std::vector<Issue*> KnickKnackerIO::readAllIssues() {
  dirExists();
  std::vector<Issue*> issues;
  std::fstream file(DIR_ISSUES, std::ios::in);
  if (file.is_open()) {
    std::vector<std::string> row;
    std::string line, word;
    while (std::getline(file, line)) {
      row.clear();
      std::stringstream s(line);
      while (getline(s, word, ',')) {
        row.push_back(word);
      }
      Issue* issue = new Issue(
        (unsigned int)std::stoi(row[0]),
        row[1],
        row[2],
        (unsigned int)std::stoi(row[3]),
        convertToStatus(row[4]),
        convertToPriority(row[5]),
        row[6]);
      issues.push_back(issue);
    }
    file.close();
  }
  return issues;
}

Issue* KnickKnackerIO::getIssueByID(unsigned int id) {
  dirExists();
  Issue* issue = nullptr;
  std::fstream file(DIR_ISSUES, std::ios::in);
  if (file.is_open()) {
    std::vector<std::string> row;
    std::string line, word;
    while (std::getline(file, line)) {
      row.clear();
      std::stringstream s(line);
      while (getline(s, word, ',')) {
        row.push_back(word);
      }
      if (std::stoi(row[0]) == id) {
        issue = new Issue(
          (unsigned int)std::stoi(row[0]),
          row[1],
          row[2],
          (unsigned int)std::stoi(row[3]),
          convertToStatus(row[4]),
          convertToPriority(row[5]),
          row[6]);
        break;
      }
    }
    file.close();
  }
  return issue;
}

std::vector<Comment*> KnickKnackerIO::readAllComments() {
  dirExists();
  std::vector<Comment*> comments;
  std::fstream file(DIR_COMMENTS, std::ios::in);
  if (file.is_open()) {
    std::vector<std::string> row;
    std::string line, word;
    while (std::getline(file, line)) {
      row.clear();
      std::stringstream s(line);
      while (getline(s, word, ',')) {
        row.push_back(word);
      }
      Comment* comment = new Comment(
        (unsigned int)std::stoi(row[0]),
        (unsigned int)std::stoi(row[1]),
        (unsigned int)std::stoi(row[2]),
        row[3]);
      comments.push_back(comment);
    }
    file.close();
  }
  return comments;
}

std::vector<User*> KnickKnackerIO::readAllUsers() {
  dirExists();
  std::vector<User*> users;
  std::fstream file(DIR_USERS, std::ios::in);
  if (file.is_open()) {
    std::vector<std::string> row;
    std::string line, word;
    while (std::getline(file, line)) {
      row.clear();
      std::stringstream s(line);
      while (getline(s, word, ',')) {
        row.push_back(word);
      }
      User* user = new User(
        (unsigned int)std::stoi(row[0]),
        row[1],
        row[2],
        row[3]);
      users.push_back(user);
    }
    file.close();
  }
  return users;
}

void KnickKnackerIO::overwriteIssues(std::vector<Issue*> issues) {
  dirExists();
  std::fstream file(DIR_ISSUES, std::ios::out);
  std::string delimiter = ",";
  if (file.is_open()) {
    for (Issue* i : issues) {
      file << i->getID() << delimiter
      << i->getTitle() << delimiter
      << i->getDescription() << delimiter
      << i->getUserID() <<delimiter
      << i->getStatus() <<delimiter
      << i->getPriority() <<delimiter
      << i->getOS()
      << "\n";
    }
    file.close();
  }
}

void KnickKnackerIO::overwriteComments(std::vector<Comment*> comments) {
  dirExists();
  std::fstream file(DIR_COMMENTS, std::ios::out);
  std::string delimiter = ",";
  if (file.is_open()) {
    for (Comment* c : comments) {
      file << c->getID() << delimiter
      << c->getIssueID() << delimiter
      << c->getUserID() << delimiter
      << c->getValue()
      << "\n";
    }
    file.close();
  }
}

void KnickKnackerIO::overwriteUsers(std::vector<User*> users) {
  dirExists();
  std::fstream file(DIR_USERS, std::ios::out);
  std::string delimiter = ",";
  if (file.is_open()) {
    for (User* u : users) {
      file << u->getID() << delimiter
      << u->getFirstName() << delimiter
      << u->getLastName() << delimiter
      << u->getUsername()
      << "\n";
    }
    file.close();
  }
}

void KnickKnackerIO::appendIssue(Issue* issue) {
  dirExists();
  std::fstream file(DIR_ISSUES, std::ios::out | std::ios::app);
  std::string delimiter = ",";
  if (file.is_open()) {
    file << issue->getID() << delimiter
    << issue->getTitle() << delimiter
    << issue->getDescription() << delimiter
    << issue->getUserID() <<delimiter
    << issue->getStatus() <<delimiter
    << issue->getPriority() <<delimiter
    << issue->getOS()
    << "\n";
    file.close();
  }
}

void KnickKnackerIO::appendComment(Comment* comment) {
  dirExists();
  std::fstream file(DIR_COMMENTS, std::ios::out | std::ios::app);
  std::string delimiter = ",";
  if (file.is_open()) {
    file << comment->getID() << delimiter
    << comment->getIssueID() << delimiter
    << comment->getUserID() << delimiter
    << comment->getValue()
    << "\n";
    file.close();
  }
}

void KnickKnackerIO::appendUser(User* user) {
  dirExists();
  std::fstream file(DIR_USERS, std::ios::out | std::ios::app);
  std::string delimiter = ",";
  if (file.is_open()) {
    file << user->getID() << delimiter
    << user->getFirstName() << delimiter
    << user->getLastName() << delimiter
    << user->getUsername()
    << "\n";
    file.close();
  }
}

Issue::Priority KnickKnackerIO::convertToPriority(const std::string& s) {
  if (toLower(s) == "low") {
    return Issue::Low;
  } else if (toLower(s) == "medium") {
    return Issue::Medium;
  } else if (toLower(s) == "high") {
    return Issue::High;
  } else if (toLower(s) == "top") {
    return Issue::Top;
  }
  return Issue::Low;
}

Issue::Status KnickKnackerIO::convertToStatus(const std::string& s) {
  if (toLower(s) == "new") {
    return Issue::New;
  } else if (toLower(s) == "assigned") {
    return Issue::Assigned;
  } else if (toLower(s) == "wontfix") {
    return Issue::WontFix;
  }
  return Issue::New;
}

void KnickKnackerIO::dirExists() {
  struct stat info;
  int nError = 0;//NOLINT
  int nMode = 0733;//NOLINT
  std::string sPath = DAT_DIR;
  if (stat(sPath.c_str(), &info) != 0) {
    #if defined(_WIN32)
      nError = _mkdir(sPath.c_str());//NOLINT
    #else
      nError = mkdir(sPath.c_str(), nMode);//NOLINT
    #endif
  } else if (info.st_mode & S_IFDIR) {
    return;
  } else {
      #if defined(_WIN32)
        nError = _mkdir(sPath.c_str());//NOLINT
      #else
        nError = mkdir(sPath.c_str(), nMode);//NOLINT
      #endif
  }
}

std::string KnickKnackerIO::toLower(std::string input) {
  // convert string to lower case
  std::for_each(input.begin(), input.end(), [](char & c) {
    c = ::tolower(c);
  });
  return input;
}

bool KnickKnackerIO::is_number(const std::string& s) {
  return !s.empty() && std::find_if(s.begin(),
  s.end(), [](unsigned char c) {
    return !std::isdigit(c);
  }) == s.end();
}
