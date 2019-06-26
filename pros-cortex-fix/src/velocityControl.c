#include "main.h"

// Variables to hold target velocity
double targetLeftVelocity = 0.0;
double targetRightVelocity = 0.0;

// Keeps track of the prevous power given to the wheels
int prevLeftPower = 0;
int prevRightPower = 0;

// Handles velocity control
TaskHandle velocityTask;

enum PIDControllers
{
  PID_LEFT,
  PID_RIGHT
};
PID controllers[2];

void velocityController(void *ignore)
{
  pidInit(&controllers[PID_LEFT], 0.5, 0.0, 0.0);
  pidInitCopy(&controllers[PID_RIGHT], &controllers[PID_LEFT]);

  while(true)
  {
    // Get needed info
    mutexTake(mutexes[MUTEX_TARGET_VELOCITY], -1);
    double currentLeftTarget = targetLeftVelocity;
    double currentRightTarget = targetRightVelocity;
    mutexGive(mutexes[MUTEX_TARGET_VELOCITY]);

    mutexTake(mutexes[MUTEX_VELOCITY], -1);
    double currentLeftVelocity = leftWheelLinearVelocity;
    double currentRightVelocity = rightWheelLinearVelocity;
    mutexGive(mutexes[MUTEX_VELOCITY]);

    // Calculate the target value, limiting the max change to 15
    int leftPowerDiff = pidCalculate(&controllers[PID_LEFT], currentLeftTarget, currentLeftVelocity) * 15;
    int rightPowerDiff = pidCalculate(&controllers[PID_RIGHT], currentRightTarget, currentRightVelocity) * 15;

    // power the motors
    powerMotors(prevLeftPower + leftPowerDiff, prevRightPower + rightPowerDiff);

    // Set previous values
    prevLeftPower = prevLeftPower + leftPowerDiff;
    prevRightPower = prevRightPower + rightPowerDiff;

    delay(20);
  }
}
void initializeVelocityController()
{
  if (taskGetState(velocityTask) == TASK_DEAD || taskGetState(velocityTask) == TASK_RUNNABLE)
  {
    velocityTask = taskCreate(velocityController, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT + 2);
  }
}
void stopVelocityController()
{
  if (taskGetState(velocityTask) != TASK_DEAD || taskGetState(velocityTask) != TASK_RUNNABLE)
  {
    taskDelete(velocityTask);
    targetLeftVelocity = 0.0;
    targetRightVelocity = 0.0;
    stopMotors();
    prevLeftPower = 0;
    prevRightPower = 0;
  }
}
void setTargetVelocity(double leftV, double rightV)
{
  mutexTake(mutexes[MUTEX_TARGET_VELOCITY], -1);
  targetLeftVelocity = leftV;
  targetRightVelocity = rightV;
  mutexGive(mutexes[MUTEX_TARGET_VELOCITY]);
}
