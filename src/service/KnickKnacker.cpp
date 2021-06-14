#include <string>
#include <vector>
#include "KnickKnacker.h"

KnickKnacker::~KnickKnacker() {
  delete broker;
}

unsigned int KnickKnacker::createIssue(std::string title, std::string desc,
   Issue::Status status, Issue::Priority priority) {
  std::vector<Issue*> issues = broker->readAllIssues();
  unsigned int id;
  if (!issues.empty()) {
    id = issues.back()->getID() + 1;
  } else {
    id = 1;
  }
  for (Issue* i : issues) {
    delete i;
  }
  issues.clear();
  Issue* issue = new Issue(id, title, desc, status, priority);
  broker->appendIssue(issue);
  delete issue;
  return id;
}

Issue KnickKnacker::getIssueByID(unsigned int id) {
  Issue* pIssue = broker->getIssueByID(id);
  Issue issue = *pIssue;
  delete pIssue;
  return issue;
}

bool KnickKnacker::updateIssue(unsigned int id, std::string title,
   std::string desc, Issue::Status status, Issue::Priority priority) {
  std::vector<Issue*> issues = broker->readAllIssues();
  bool updated = false;
  for (Issue* i : issues) {
    if (i->getID() == id) {
      if (!title.empty()) {
        i->updateTitle(title);
      }
      if (!desc.empty()) {
        i->updateDescription(desc);
      }
      i->updateStatus(status);
      i->updatePriority(priority);
      updated = true;
      break;
    }
  }
  broker->overwriteIssues(issues);
  for (Issue* i : issues) {
    delete i;
  }
  issues.clear();
  return updated;
}

bool KnickKnacker::deleteIssueByID(unsigned int id) {
  std::vector<Issue*> issues = broker->readAllIssues();
  bool found = false;
  for (std::vector<Issue*>::iterator it = issues.begin();
    it != issues.end(); ++it) {
    if ((*it)->getID() == id) {
      it = issues.erase(it);
      found = true;
      break;
    }
  }
  broker->overwriteIssues(issues);
  for (Issue* i : issues) {
    delete i;
  }
  issues.clear();
  return found;
}

std::vector<Issue> KnickKnacker::getAllIssues() {
  std::vector<Issue> issues;
  std::vector<Issue*> pIssues = broker->readAllIssues();
  for (Issue* i : pIssues) {
    issues.push_back(*i);
    delete i;
  }
  pIssues.clear();
  return issues;
}
