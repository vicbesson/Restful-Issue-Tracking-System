#include "Issue.h"
#include "gtest/gtest.h"

TEST(TestIssue, defaultConstructorTest) {
}

TEST(TestIssue, constructor1Test) {
  Issue iss(50, "test title", "test description", 13407, Issue::New,
  Issue::Low, "test OS");

  EXPECT_EQ(50, iss.getID());
  EXPECT_EQ("test title", iss.getTitle());
  EXPECT_EQ("test description", iss.getDescription());
  EXPECT_EQ(13407, iss.getUserID());
  EXPECT_EQ("New", iss.getStatus());
  EXPECT_EQ("Low", iss.getPriority());
  EXPECT_EQ("test OS", iss.getOS());
}

TEST(TestIssue, constructor2Test) {
  Issue iss(50, "test title", "test description", Issue::New, Issue::Low);

  EXPECT_EQ(50, iss.getID());
  EXPECT_EQ("test title", iss.getTitle());
  EXPECT_EQ("test description", iss.getDescription());
  EXPECT_EQ("New", iss.getStatus());
  EXPECT_EQ("Low", iss.getPriority());
  EXPECT_EQ("No OS", iss.getOS());
}

TEST(TestIssue, destructorTest) {
  //nothing to test yet without implmentation of Comment class
}

TEST(TestIssue, updateTitleTest) {
  Issue iss(50, "test title", "test description", 13407, Issue::New,
  Issue::Low, "test OS");

  EXPECT_EQ("test title", iss.getTitle());
  iss.updateTitle("updated title");
  EXPECT_EQ("updated title", iss.getTitle());
  iss.updateTitle("updated again");
  EXPECT_EQ("updated again", iss.getTitle());
}

TEST(TestIssue, updateDescriptionTest) {
  Issue iss(50, "test title", "test description", 13407, Issue::New,
  Issue::Low, "test OS");

  EXPECT_EQ("test description", iss.getDescription());
  iss.updateDescription("updated description");
  EXPECT_EQ("updated description", iss.getDescription());
  iss.updateDescription("updated again");
  EXPECT_EQ("updated again", iss.getDescription());
}

TEST(TestIssue, updateStatusTest) {
  Issue iss(50, "test title", "test description", 13407, Issue::New,
  Issue::Low, "test OS");

  EXPECT_EQ("New", iss.getStatus());
  iss.updateStatus(Issue::Assigned);
  EXPECT_EQ("Assigned", iss.getStatus());
  iss.updateStatus(Issue::WontFix);
  EXPECT_EQ("WontFix", iss.getStatus());
  iss.updateStatus(Issue::SLast);
  EXPECT_EQ("?", iss.getStatus());
}

TEST(TestIssue, updatePriorityTest) {
  Issue iss(50, "test title", "test description", 13407, Issue::New,
  Issue::Low, "test OS");

  EXPECT_EQ("Low", iss.getPriority());
  iss.updatePriority(Issue::Medium);
  EXPECT_EQ("Medium", iss.getPriority());
  iss.updatePriority(Issue::High);
  EXPECT_EQ("High", iss.getPriority());
  iss.updatePriority(Issue::PLast);
  EXPECT_EQ("?", iss.getPriority());
}

TEST(TestIssue, updateOSTest) {
  Issue iss(50, "test title", "test description", 13407, Issue::New,
  Issue::Low, "test OS");

  EXPECT_EQ("test OS", iss.getOS());
  iss.updateOS("updated OS");
  EXPECT_EQ("updated OS", iss.getOS());
  iss.updateOS("updated again");
  EXPECT_EQ("updated again", iss.getOS());
}

TEST(TestIssue, getIDTest) {
  Issue iss(50, "test title", "test description", 13407, Issue::New,
  Issue::Low, "test OS");
  Issue iss2(1450, "test title", "test description", 13407, Issue::New,
  Issue::Low, "test OS");

  EXPECT_EQ(50, iss.getID());
  EXPECT_EQ(1450, iss2.getID());
}

TEST(TestIssue, getTitleTest) {
  Issue iss(50, "test title", "test description", 13407, Issue::New,
  Issue::Low, "test OS");
  Issue iss2(50, "different title", "test description", 13407, Issue::New,
  Issue::Low, "test OS");

  EXPECT_EQ("test title", iss.getTitle());
  EXPECT_EQ("different title", iss2.getTitle());
}

TEST(TestIssue, getDescriptionTest) {
  Issue iss(50, "test title", "test description", 13407, Issue::New,
  Issue::Low, "test OS");
  Issue iss2(50, "test title", "different description", 13407, Issue::New,
  Issue::Low, "test OS");

  EXPECT_EQ("test description", iss.getDescription());
  EXPECT_EQ("different description", iss2.getDescription());
}

TEST(TestIssue, getUserIDTest) {
  Issue iss(50, "test title", "test description", 13407, Issue::New,
  Issue::Low, "test OS");
  Issue iss2(50, "test title", "test description", 1245, Issue::New,
  Issue::Low, "test OS");

  EXPECT_EQ(13407, iss.getUserID());
  EXPECT_EQ(1245, iss2.getUserID());
}

TEST(TestIssue, getStatusTest) {
  Issue iss(50, "test title", "test description", 13407, Issue::New,
  Issue::Low, "test OS");
  Issue iss2(50, "test title", "test description", 13407, Issue::WontFix,
  Issue::Low, "test OS");
  Issue iss3(50, "test title", "test description", 13407, Issue::SLast,
  Issue::Low, "test OS");

  EXPECT_EQ("New", iss.getStatus());
  EXPECT_EQ("WontFix", iss2.getStatus());
  EXPECT_EQ("?", iss3.getStatus());
}

TEST(TestIssue, getStatusEnumTest) {
  Issue iss(50, "test title", "test description", 13407, Issue::New,
  Issue::Low, "test OS");
  Issue iss2(50, "test title", "test description", 13407, Issue::WontFix,
  Issue::Low, "test OS");
  Issue iss3(50, "test title", "test description", 13407, Issue::SLast,
  Issue::Low, "test OS");

  EXPECT_EQ(Issue::New, iss.getStatusEnum());
  EXPECT_EQ(Issue::WontFix, iss2.getStatusEnum());
  EXPECT_EQ(Issue::SLast, iss3.getStatusEnum());
}

TEST(TestIssue, getPriorityTest) {
  Issue iss(50, "test title", "test description", 13407, Issue::New,
  Issue::Low, "test OS");
  Issue iss2(50, "test title", "test description", 13407, Issue::New,
  Issue::Top, "test OS");
  Issue iss3(50, "test title", "test description", 13407, Issue::New,
  Issue::PLast, "test OS");

  EXPECT_EQ("Low", iss.getPriority());
  EXPECT_EQ("Top", iss2.getPriority());
  EXPECT_EQ("?", iss3.getPriority());
}

TEST(TestIssue, getPriorityEnumTest) {
  Issue iss(50, "test title", "test description", 13407, Issue::New,
  Issue::Low, "test OS");
  Issue iss2(50, "test title", "test description", 13407, Issue::New,
  Issue::Top, "test OS");
  Issue iss3(50, "test title", "test description", 13407, Issue::New,
  Issue::PLast, "test OS");

  EXPECT_EQ(Issue::Low, iss.getPriorityEnum());
  EXPECT_EQ(Issue::Top, iss2.getPriorityEnum());
  EXPECT_EQ(Issue::PLast, iss3.getPriorityEnum());
}

TEST(TestIssue, getOSTest) {
  Issue iss(50, "test title", "test description", 13407, Issue::New,
  Issue::Low, "test OS");
  Issue iss2(50, "test title", "test description", 13407, Issue::New,
  Issue::Low, "different OS");

  EXPECT_EQ("test OS", iss.getOS());
  EXPECT_EQ("different OS", iss2.getOS());
}

TEST(TestIssue, addCommentTest) {
  //nothing to test yet without implmentation of Comment class
}

TEST(TestIssue, deleteCommentTest) {
  //nothing to test yet without implementation of Comment class
}

TEST(TestIssue, getCommentsTest) {
  //nothing to test yet without implementation of Comment class
}

TEST(TestIssue, getCommentTest) {
  //nothing to test yet without implementation of Comment class
}
