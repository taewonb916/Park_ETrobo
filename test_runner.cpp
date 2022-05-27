#include "test_runner.h"

const int kTtestRunParamsNum = 2;
const DrivingParam kTestRunParams[kTtestRunParamsNum] = {
  { kTraceRightEdge, 50, { 0.5, 0, 0 }, kDistanceEnd, kInvalidColor, 1000, false},
  { kStopWheels, 0, { 0, 0, 0 }, kInvalidEnd, kInvalidColor, 0, false},
};


TestRunner::TestRunner(DrivingManager* driving_manager) 
    : driving_manager_(driving_manager) {
  SetTestRunParam();
}

void TestRunner::SetTestRunParam() {
  paramNum = kTtestRunParamsNum;

  for (int i=0; i<paramNum; i++) {
    testRunParams[i] = kTestRunParams[i];
  }
}

void TestRunner::Update() {
  DrivingParam& curr_param = testRunParams[currParamIndex];
  if (!curr_param.is_started) {
    driving_manager_->SetDriveParam(curr_param);
    curr_param.is_started = true;
  }

  driving_manager_->Update();

  if (driving_manager_->is_satisfied) {
    currParamIndex += 1;
  }

  if (currParamIndex >= paramNum) {
    is_completed = true;
  }
}