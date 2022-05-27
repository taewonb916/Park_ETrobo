#include "app.h"

#include "device_io.h"
#include "etrc_info.h"
#include "driving.h"
#include "test_runner.h"
#include "game_play.h"
#include "state_manager.h"

static const bool kLcourse = true;

MotorIo* motor_io;
SensorIo* sensor_io;
Camera* camera;
Luminous* luminous;
Localize* localize;
WheelsControl* wheels_control;
BasicDriver* basic_driver;
LineTracer* line_tracer;
EndCondition* end_condition;
DrivingManager* driving_manager;
TimeAttacker* time_attacker;
BonusGetter* bonus_getter;
TestRunner* test_runner;
BingoAgent* bingo_agent;
StateManager* state_manager;

static void initialize() {
  motor_io = new MotorIo();
  sensor_io = new SensorIo();
  camera = new Camera();
  luminous = new Luminous(sensor_io, camera);
  localize = new Localize(motor_io);
  wheels_control = new WheelsControl(motor_io);
  basic_driver = new BasicDriver(wheels_control);
  line_tracer = new LineTracer(wheels_control, luminous);
  end_condition = new EndCondition(luminous, localize);
  driving_manager = new DrivingManager(basic_driver, line_tracer, end_condition);
  time_attacker = new TimeAttacker(driving_manager, kLcourse);
  bonus_getter = new BonusGetter(driving_manager, kLcourse);
  test_runner = new TestRunner(driving_manager);
  bingo_agent = new BingoAgent(kLcourse);
  state_manager = new StateManager(time_attacker, bonus_getter, test_runner);
}

static void finalize() {
  delete state_manager;
  delete bingo_agent;
  delete test_runner;
  delete bonus_getter;
  delete time_attacker;
  delete driving_manager;
  delete end_condition;
  delete line_tracer;
  delete basic_driver;
  delete wheels_control;
  delete localize;
  delete luminous;
  delete camera;
  delete sensor_io;
  delete motor_io;
}


void main_task(intptr_t unused) {
  initialize();
  sta_cyc(UPDATE_INFO_CYC);

  while (true) {
    if (sensor_io->touch_sensor_pressed_) break;
    tslp_tsk(TASK_INTERVAL_DT_MS*1000U);
  }
  tslp_tsk(START_INTERVAL_DT_MS*1000U);

  sta_cyc(EXEC_ACTION_CYC);

  tslp_tsk(TASK_INTERVAL_DT_MS*1000U);

  while (true) {
    if (sensor_io->touch_sensor_pressed_) break;
    tslp_tsk(100*1000U);
  }

  stp_cyc(EXEC_ACTION_CYC);
  stp_cyc(UPDATE_INFO_CYC);
  finalize();
  ext_tsk();
}

void exec_action_task(intptr_t unused) {
  state_manager->Update();
  ext_tsk();
}

void update_info_task(intptr_t unused) {
  motor_io->Update();
  sensor_io->Update();
  luminous->Update();
  camera->Update();
  ext_tsk();
}

void solve_bingo_task(intptr_t unused) {
  bingo_agent->SolveBingo();
  ext_tsk();
}
