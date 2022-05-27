#include "utils.h"

#include "app.h"

PidControl::PidControl()
    : kp_(0), ki_(0), kd_(0), dt_(EXEC_ACTION_DT_MS/1000.0) {
}

void PidControl::SetGain(float kp, float ki, float kd) {
  kp_ = kp;
  ki_ = ki;
  kd_ = kd;
}

float PidControl::CalcMv(float target_val, float current_val) {
  float mv = kp_ * (target_val - current_val);

  return mv;
}