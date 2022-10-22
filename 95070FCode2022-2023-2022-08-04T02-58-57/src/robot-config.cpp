#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor rightFront = motor(PORT1, ratio18_1, false);
motor leftFront = motor(PORT3, ratio18_1, true);
motor leftBack = motor(PORT12, ratio18_1, true);
motor rightBack = motor(PORT8, ratio18_1, false);
motor Intake = motor(PORT21, ratio18_1, true);
motor Intake2 = motor(PORT20, ratio18_1, false);
motor Catapult = motor(PORT19, ratio18_1, false);
motor Roller = motor(PORT9, ratio18_1, false);
motor Expansion = motor(PORT10, ratio18_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}