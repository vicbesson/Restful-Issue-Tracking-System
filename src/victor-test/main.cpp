#include "TestManager.h"

int main() {
  TestManager* test = new TestManager();
  test->startTestManager();
  delete test;
  return 0;
}
