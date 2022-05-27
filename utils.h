#ifndef ETRC22_UTILS_H_
#define ETRC22_UTILS_H_

class PidControl {
 public:
  PidControl();
  void SetGain(float kp, float ki, float kd);
  float CalcMv(float target_val, float current_val);

 private:
  float kp_;
  float ki_;
  float kd_;
  float dt_;
};

#endif  // ETRC22_UTILS_H_