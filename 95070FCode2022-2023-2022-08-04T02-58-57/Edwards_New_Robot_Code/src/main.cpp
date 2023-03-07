/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Edward C                                                  */
/*    Created:      Feb 2023                                                  */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// FrontLeft            motor         1               
// FrontRight           motor         2               
// MidLeft              motor         3               
// MidRight             motor         4               
// BackLeft             motor         5               
// BackRight            motor         6               
// Indexer              motor         7               
// IR                   motor         8               
// Flywheel             motor         9               
// Expansion            digital_out   A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  
}
int selected = 0;
int size = 10;
std::string autons[] = {"", "", "", "", "", "", "", "", "", "", ""};
//put auton names here

void autonSelector(){
  Controller1.Screen.clearScreen();
  task::sleep(100);
  while(true){
  Controller1.Screen.clearScreen();
  task::sleep(100);
  Controller1.Screen.newLine();
   Controller1.Screen.print(autons[selected].c_str());
  task::sleep(100);
  if(Controller1.ButtonRight.pressing()){
  selected = (selected + 1 + size) % size;
  }else if(Controller1.ButtonLeft.pressing()){
  selected = (selected - 1 + size) % size;
  }else if(Controller1.ButtonDown.pressing()){
  task::sleep(100);
  if(Controller1.ButtonDown.pressing()){
  goto slctEnd;
}
}
}
slctEnd:
Controller1.rumble("..");
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
int flywheel = 0;
digital_out Expansion = digital_out(Brain.ThreeWirePort.A);
int getSign(double a){
if(a<0){
return -1;
}
else if(a>0){
return 1;
}
else{
return 0;
}}

void PID (double kP, double kI, double kD, double maxIntegral, double tolerance, double maximumSpeed, double minimumSpeed, double target){
double error = target;
double derivative = 0;
double integral = 0;
double LastError=error;
double total = 0;
BackLeft.setPosition(0, turns);
while(fabs(tolerance)<fabs(error)){
double SensorValue = BackLeft.position(turns)*5*3.25*M_PI/3;                    change this
error = target - SensorValue;
integral = integral + error;
if(fabs(integral)>fabs(maxIntegral)){
integral=getSign(integral)*maxIntegral;
}
derivative = error-LastError;
LastError = error;
total = kP*error + kI*integral + kD*derivative;
if(fabs(total) > fabs(maximumSpeed)){
Flywheel.setVelocity(getSign(total)*maximumSpeed, percent);
}
else if(fabs(total) < fabs(minimumSpeed)){
Flywheel.setVelocity(getSign(total)*minimumSpeed, percent);
}
else{
Flywheel.setVelocity(total, percent);
}
Flywheel.spin(forward);
}
Flywheel.setStopping(brake);
Flywheel.stop();
wait(10, msec);
}

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.


    FrontLeft.setVelocity(Controller1.Axis3.position(percent) + Controller1.Axis1.position(percent), percent);
    FrontRight.setVelocity(Controller1.Axis3.position(percent) + Controller1.Axis1.position(percent)*-1, percent);
    MidLeft.setVelocity(Controller1.Axis3.position(percent) + Controller1.Axis1.position(percent), percent);
    MidRight.setVelocity(Controller1.Axis3.position(percent) + Controller1.Axis1.position(percent)*-1, percent);
    BackLeft.setVelocity(Controller1.Axis3.position(percent) + Controller1.Axis1.position(percent), percent);
    BackRight.setVelocity(Controller1.Axis3.position(percent) + Controller1.Axis1.position(percent)*-1, percent);
    FrontLeft.spin(forward);
    FrontRight.spin(forward);
    MidLeft.spin(forward);
    MidRight.spin(forward);
    BackLeft.spin(forward);
    BackRight.spin(forward);
  //Expansion code
  if (Controller1.ButtonX.pressing() && Controller1.ButtonY.pressing()){
    Expansion.set(true);
  }
  if (Controller1.ButtonB.pressing()){
    Expansion.set(false);
  }
  //Intake and Roller code
  if (Controller1.ButtonR1.pressing()){
    IR.setVelocity(100,percent);
    IR.spin(forward);
  }
  else if (Controller1.ButtonR2.pressing()){
    IR.setVelocity(100,percent);
    IR.spin(reverse);
  }

  //Indexer code
  if (Controller1.ButtonL1.pressing()){
    Indexer.setVelocity(100,percent);
    Indexer.spin(forward);
  }
  else if (Controller1.ButtonL2.pressing()){
    Indexer.setVelocity(100,percent);
    Indexer.spin(reverse);
  }

  //Flywheel code
  if (Controller1.ButtonUp.pressing() && flywheel == 0){
    flywheel = 1;
    Flywheel.setVelocity(80,percent);
    Flywheel.spin(forward);
    PID(3, 0.01, 0.05, 600, 0.5, 100, 90, 44);        tune these numbers as needed
  }
  else if (Controller1.ButtonDown.pressing() && flywheel == 1){
    Flywheel.stop();
    flywheel = 0;
  }
  else {
    Flywheel.stop();
    flywheel = 0;
  }
    

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}


//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
