#ifndef ETRC22_TEST_RUNNER_H_
#define ETRC22_TEST_RUNNER_H_

#include "driving.h"

class TestRunner {
 public:
  TestRunner(DrivingManager* driving_manager);
  void Update();
  bool is_completed = false;
 private:
  void SetTestRunParam();
  DrivingManager* driving_manager_;
  DrivingParam testRunParams[100] = {};
  int8_t currParamIndex = 0;
  int8_t paramNum = 0;
};

#endif  // ETRC22_TEST_RUNNER_H_