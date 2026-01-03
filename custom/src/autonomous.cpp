#include "vex.h"
#include "utils.h"
#include "pid.h"
#include <ctime>
#include <cmath>
#include <thread>

#include "../include/autonomous.h"
#include "motor-control.h"

// IMPORTANT: Remember to add respective function declarations to custom/include/autonomous.h
// Call these functions from custom/include/user.cpp
// Format: returnType functionName() { code }

void linearTuning() {
  // Use this for tuning linear and turn pid
  driveTo(6, 3000);
  driveTo(12, 3000);
  driveTo(24, 3000);
  wait(5,sec);
  driveTo(-6, 3000);
  driveTo(-12, 3000);
  driveTo(-24, 3000);
  wait(5,sec);
  driveTo(60, 3000);
  wait(5,sec);
  driveTo(-60, 3000);
}

void turnTuning() {
  turnToAngle(90, 2000);
  turnToAngle(135, 2000);
  turnToAngle(150, 2000);
  turnToAngle(160, 2000);
  turnToAngle(165, 2000);
  turnToAngle(0, 2000);
}

void odomExample() {
  moveToPoint(24, 24, 1, 2000, false);
  moveToPoint(48, 48, 1, 2000, true);
  moveToPoint(24, 24, -1, 2000, true);
  moveToPoint(0, 0, 1, 2000, true);
  correct_angle = 0;
  driveTo(24, 2000, false, 8);
  turnToAngle(90, 800, false);
  turnToAngle(180, 800, true);
}

void boomerangTest(){
  boomerang(24,0,1,90,.6,3000,false,12,false);
  boomerang(36,36,1,0,.6,3000,true,12,false);
  boomerang(0,0,-1,0,.6,3000,true,12,false);
}

/*
Start of Actual Autons
*/

void intakeBlocks(){
  intake.spin(fwd,12,volt);
  second_stage.spin(fwd,1,volt);
  scoringM.spin(fwd,1,volt);
}

void scoreHigh(){
  intake.spin(fwd,12,volt);
  second_stage.spin(fwd,12,volt);
  scoringM.spin(fwd,12,volt);
}

void scoreMid(){
  intake.spin(fwd,-6,volt);
  second_stage.spin(fwd,-6,volt);
  scoringM.spin(fwd,11,volt);
  wait(200,msec);
  intake.spin(fwd,12,volt);
  second_stage.spin(fwd,1,volt);
  scoringM.spin(fwd,1,volt);
}

void scoreLow(){
  intake.spin(fwd,-12,volt);
  second_stage.spin(fwd,-12,volt);
  scoringM.spin(fwd,-12,volt);
}

void pauseIntake(){
  intake.stop();
  second_stage.stop();
  scoringM.stop();
}



void rightMatchload(){
  intakeBlocks();                                       //start intake
  boomerang(5.5,24,1,70,.3,3000);                       //move to collect 3 blocks
  scraper.set(true);                                    //open scraper
  boomerang(37.5,-20,1,180,.3,3000);                        //move to matchloader
  
  //wait(3,sec);

  correct_angle = 180;
  driveTo(6,3000,true,6);                               //move forward to unload matchloader
  wait(1,sec);                                          //wait for blocks
  moveToPoint(37.5,10,-1,3000);                           //move to long goal
  scraper.set(false);                                   //bring scraper up
  scoreHigh();                                          //score in long goal
  wait(2,sec);                                          //timer for scoring
  pauseIntake();                                        //stop intaking

  wait(3,sec);

  moveToPoint(31.5,16.223,1,3000);                      //move to set up for wing
  wing.set(true);                                       //open wings
  moveToPoint(31.5,45,-1,3000);                         //move backwards to push for control bonus
  stopChassis(hold);                                    //hold position
}

void rightLowHigh(){
  intakeBlocks();                                       //start intake
  driveTo(15,2000);
  turnToAngle(30,2000);
  scraper.set(true);
  driveTo(11,3000,true,3.5);
  wait(500,msec);
  scraper.set(false);
  //driveTo(-4,3000,true,5);
  turnToAngle(-45,2000);
  driveTo(14,2000);
  scoreLow();
  wait(2000, msec);
  driveTo(-47, 3000, true, 4);
  turnToAngle(-180,1000);
  scraper.set(true);
  wait(500, msec);
  intakeBlocks();
  driveTo(10,1000);
  wait(2500, msec);
  driveTo(-22,2000);
  scoreHigh();

}

void left4_5(){
  intakeBlocks();                                       //start intake
  boomerang(-1,31,1,-50,.3,3000,false);                 //move to collect 3 blocks
  scraper.set(true);                                    //open scraper to trap blocks
  wait(200,msec);                                       //wait .2s
  scraper.set(false);                                   //close scraper
  boomerang(-25,51,1,-80,.3,3000,false);                //move to matchloader
  scraper.set(true);                                    //open scraper to trap blocks
  wait(200,msec);                                       //wait .2s
  scraper.set(false);                                   //close scraper
  
  wait(3,sec);

  correct_angle = -80;                                  //heading for pid straight
  driveTo(3,3000,true,6);                               //move forward to unload matchloader
  boomerang(5,44,-1,-135,3000,true);                    //move to mid goal
  scoreMid();                                           //score in mid goal
  wait(1,sec);                                          //timer for scoring
  intakeBlocks();                                       //go back to intake mode

  wait(3,sec);

  scraper.set(true);                                    //open scraper
  boomerang(-30,0,1,180,.3,3000);                       //move to matchloader
  correct_angle = 180;                                  //heading for matchload
  driveTo(6,3000);                                      //move forward to unload matchloader
  wait(1,sec);                                          //wait for blocks

  wait(3,sec);

  moveToPoint(-30,24,-1,3000);                          //move to long goal
  scraper.set(false);                                   //bring scraper up
  scoreHigh();                                          //score in long goal
  wait(2,sec);                                          //timer for scoring
  pauseIntake();                                        //stop intaking

  wait(3,sec);

  moveToPoint(21.5,16.223,1,3000);                      //move to set up for wing
  wing.set(true);                                       //open wings
  moveToPoint(21.5,45,-1,3000);                         //move backwards to push for control bonus
  stopChassis(hold);                                    //hold position
}
