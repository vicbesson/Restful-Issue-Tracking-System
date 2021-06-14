#include <string>
#include "Issue.h"

Issue::~Issue() {
  for (Comment* c : comments) {
    delete c;
  }
  comments.clear();
}

void Issue::addComment(Comment* c) {
  if (c != nullptr)
    comments.push_back(c);
}

void Issue::deleteComment(unsigned int index) {
  if (index < comments.size()) {
    delete comments[index];
    comments.erase(comments.begin() + index);
  }
}

std::string Issue::getStatus() {
  switch (status) {
    case New:
      return "New";
    case Assigned:
      return "Assigned";
    case WontFix:
      return "WontFix";
  }
  return "?";
}

std::string Issue::getPriority() {
  switch (priority) {
    case Low:
      return "Low";
    case Medium:
      return "Medium";
    case High:
      return "High";
    case Top:
      return "Top";
  }
  return "?";
}
