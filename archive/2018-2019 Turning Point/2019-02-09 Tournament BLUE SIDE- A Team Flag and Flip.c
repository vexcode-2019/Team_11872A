#pragma config(Motor,  port1,           leftBoost,     tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           left,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           liftLow,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           liftMid,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           liftHigh,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           clawLift0,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           clawLift1,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           right,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          rightBoost,    tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

// Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*---------------------------------------------------------------------------*/
void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/

task autonomous()
{
	// Go forward, hit flag
	motor[right] = 127;
	motor[left] = 127;
	motor[liftMid] = 20;
	wait1Msec(2250);

	// Back up
	motor[right] = -127;
	motor[left] = -127;
	wait1Msec(1200);

	// Turn 90 deg left
	motor[right] = 127;
	motor[left] = -127;
	wait1Msec(590);

	// Go forward and intake cap
	motor[right] = 127;
	motor[left] = 127;
	wait1Msec(1000);

	// Back up a bit
	motor[right] = -127;
	motor[left] = -127;
	wait1Msec(300);

	// Raise flipper while moving forward
	motor[right] = 127;
	motor[left] = 127;
	motor[clawLift0] = 127;
	motor[clawLift1] = 127;
	wait1Msec(1000);

	// Stop everything
	motor[right] = -127;
	motor[left] = -127;
	motor[clawLift0] = 0;
	motor[clawLift1] = 0;
	wait1Msec(1000);

	motor[right] = 0;
	motor[left] = 0;

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/


task boostForward()
{
	motor[leftBoost] = 127;
	motor[rightBoost] = 127;
}
task boostBackward()
{
	motor[leftBoost] = -127;
	motor[rightBoost] = -127;
}
/*
task raiseLift()
{
motor[liftLow] = 127;
motor[liftMid] = 127;
motor[liftHigh] = 127;
}
task lowerLift()
{
motor[liftLow] = -127;
motor[liftMid] = -127;
motor[liftHigh] = -127;
}
*/
task usercontrol()
{
	while (true)
	{
		// Left motors
		motor[left] = vexRT[Ch3];

		// Right motors
		motor[right] = vexRT[Ch2];

		// Handle lift
		motor[liftLow] = vexRT[Ch2Xmtr2];
		motor[liftMid] = vexRT[Ch2Xmtr2];
		motor[liftHigh] = vexRT[Ch2Xmtr2];

		// Handle claw lift
		motor[clawLift0] = vexRT[Ch3Xmtr2];
		motor[clawLift1] = vexRT[Ch3Xmtr2];

		// Handle claw open
		if (vexRT[Btn5U] == 1)
		{
			motor[claw] = 127;
		}
		// Handle claw close
		if (vexRT[Btn5D] == 1)
		{
			motor[claw] = -127;
		}
		// Handle claw stop
		if (vexRT[Btn7U] == 1)
		{
			motor[claw] = 0;
		}

		// Handle boost stop
		if (vexRT[Btn8U] == 1)
		{
			motor[leftBoost] = 0;
			motor[rightBoost] = 0;
		}
		// Handle boost forward
		if (vexRT[Btn6U] == 1)
		{
			startTask(boostForward);
		}
		// Handle boost backwards
		if (vexRT[Btn6D] == 1)
		{
			startTask(boostBackward);
		}
	}
}
