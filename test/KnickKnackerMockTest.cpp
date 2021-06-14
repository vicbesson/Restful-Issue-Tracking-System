#include "KnickKnacker.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <vector>

using namespace ::testing;

class MockKnickKnackerIO : public KnickKnackerIO {
 public:
   explicit MockKnickKnackerIO() {}
   virtual ~MockKnickKnackerIO() {}

   MOCK_METHOD0(readAllIssues, std::vector<Issue*>());
   MOCK_METHOD1(getIssueByID, Issue*(unsigned int id));
   MOCK_METHOD0(readAllComments, std::vector<Comment*>());
   MOCK_METHOD0(readAllUsers, std::vector<User*>());
   MOCK_METHOD1(overwriteIssues, void(std::vector<Issue*> issues));
   MOCK_METHOD1(overwriteComments, void(std::vector<Comment*> comments));
   MOCK_METHOD1(overwriteUsers, void(std::vector<User*> users));
   MOCK_METHOD1(appendIssue, void(Issue* issue));
   MOCK_METHOD1(appendComment, void(Comment* comment));
   MOCK_METHOD1(appendUser, void(User* user));
};

TEST(KnickKnackerMockTest, createIssueTest) {
  std::vector<Issue*>  iss;
  Issue* issue = new Issue(1, "title", "test", 0, Issue::New, Issue::Low, "os");
  iss.push_back(issue);
  MockKnickKnackerIO* mockIO = new MockKnickKnackerIO();
  Expectation read =
  EXPECT_CALL(*mockIO, readAllIssues())
  .Times(1)
  .WillOnce(Return(iss));
  EXPECT_CALL(*mockIO, appendIssue(_))
  .Times(1)
  .After(read)
  .WillOnce(Return());
  KnickKnacker* k = new KnickKnacker(mockIO);
  unsigned int i = k->createIssue("title", "test", Issue::New, Issue::Low);
  EXPECT_EQ(i, 2);
  delete k;
}

TEST(KnickKnackerMockTest, getIssueByIDTest) {
  std::vector<Issue*> iss;
  Issue* issueT = new Issue(2, "title", "test", Issue::New, Issue::Low);
  Issue issueC(2, "title", "test", Issue::New, Issue::Low);
  MockKnickKnackerIO* mockIO = new MockKnickKnackerIO();

  EXPECT_CALL(*mockIO, getIssueByID(_))
  .Times(1)
  .WillOnce(Return(issueT));

  KnickKnacker* k = new KnickKnacker(mockIO);
  Issue issueR = k->getIssueByID(2);
  EXPECT_EQ(2, issueR.getID());
  EXPECT_EQ("title", issueR.getTitle());
  EXPECT_EQ("test", issueR.getDescription());
  EXPECT_EQ("New", issueR.getStatus());
  EXPECT_EQ("Low", issueR.getPriority());
  EXPECT_EQ("No OS", issueR.getOS());
  delete k;
}

TEST(KnickKnackerMockTest, updateIssueTest) {
  std::vector<Issue*> iss;
  Issue* issue = new Issue(2, "title", "test", Issue::New, Issue::Low);
  iss.push_back(issue);
  MockKnickKnackerIO* mockIO = new MockKnickKnackerIO();

  Expectation read =
  EXPECT_CALL(*mockIO, readAllIssues())
  .Times(1)
  .WillOnce(Return(iss));
  EXPECT_CALL(*mockIO, overwriteIssues(_))
  .Times(1)
  .After(read)
  .WillOnce(Return());

  KnickKnacker* k = new KnickKnacker(mockIO);
  bool updateC = k->updateIssue(2, "new title", "new test", Issue::Assigned,
  Issue::Top);
  EXPECT_EQ(true, updateC);
  delete k;
}

TEST(KnickKnackerMockTest, deleteIssueByIDTest) {
  std::vector<Issue*> iss;
  Issue* issue = new Issue(2, "title", "test", Issue::New, Issue::Low);
  iss.push_back(issue);
  MockKnickKnackerIO* mockIO = new MockKnickKnackerIO();

  Expectation read =
  EXPECT_CALL(*mockIO, readAllIssues())
  .Times(1)
  .WillOnce(Return(iss));
  EXPECT_CALL(*mockIO, overwriteIssues(_))
  .Times(1)
  .After(read)
  .WillOnce(Return());

  KnickKnacker* k = new KnickKnacker(mockIO);
  bool updateC = k->deleteIssueByID(2);
  EXPECT_EQ(true, updateC);
  delete k;
}

TEST(KnickKnackerMockTest, getAllIssuesTest) {
  std::vector<Issue*> iss;
  Issue* issue = new Issue(2, "title", "test", Issue::New, Issue::Low);
  Issue* issue2 = new Issue(3, "title2", "test2", Issue::Assigned, Issue::High);
  iss.push_back(issue);
  iss.push_back(issue2);
  MockKnickKnackerIO* mockIO = new MockKnickKnackerIO();

  EXPECT_CALL(*mockIO, readAllIssues())
  .Times(1)
  .WillOnce(Return(iss));

  KnickKnacker* k = new KnickKnacker(mockIO);
  std::vector<Issue> all = k->getAllIssues();
  EXPECT_EQ(2, all.size());
  EXPECT_EQ(2, all[0].getID());
  EXPECT_EQ(3, all[1].getID());
  EXPECT_EQ("title", all[0].getTitle());
  EXPECT_EQ("title2", all[1].getTitle());
  EXPECT_EQ("test", all[0].getDescription());
  EXPECT_EQ("test2", all[1].getDescription());
  EXPECT_EQ("New", all[0].getStatus());
  EXPECT_EQ("Assigned", all[1].getStatus());
  EXPECT_EQ("Low", all[0].getPriority());
  EXPECT_EQ("High", all[1].getPriority());
  EXPECT_TRUE(all[0].getOS() == all[1].getOS());
  delete k;
}
