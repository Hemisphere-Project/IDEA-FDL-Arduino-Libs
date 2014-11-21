/* 



*************************************************/
#include <Arduino.h>
#include "Tourelle.h"
#include "Animator.h"


/****
MINI SERVO
****/
MiniServo::MiniServo()
{
	angleMin = ANGLE_MIN;
	angleMax = ANGLE_MAX;
}

void MiniServo::setLimits(int min, int max)
{
	angleMin = min;
	angleMax = max;
}

void MiniServo::setAngle(int angle)
{
	angle = 179-constrain(angle,angleMin,angleMax);
	write(angle);
}

void MiniServo::setAnglePct(int anglePourcent)
{
	setAngle( angleMin+round(anglePourcent*(angleMax-angleMin)/100.0) );
	//setAngle( map(anglePourcent,0,100,angleMin, angleMax) );
}


/****
MINI LED
****/
MiniLed::MiniLed()
{

}

void MiniLed::attach(int pin)
{
	pinNumber = pin;
	SoftPWMSet(pinNumber, 0);
	//pinMode(pinNumber,OUTPUT);
	ledMin = LED_MIN;
	ledMax = LED_MAX;
}

void MiniLed::setLimits(int min, int max)
{
	ledMin = min;
	ledMax = max;
}

void MiniLed::setIntensity(int intensite)
{
	intensite = constrain(intensite,ledMin,ledMax);
	SoftPWMSet(pinNumber, intensite);
	//analogWrite(pinNumber,intensite);
}

void MiniLed::setIntensityPct(int intensitePourcent)
{
	setIntensity( map(intensitePourcent,0,100,ledMin,ledMax) );
}


/****
TOURELLE
****/
Tourelle::Tourelle() {
}

/************
INIT
*************/
void Tourelle::attach(int pinFoot, int pinArm, int pinLed)
{
	Foot.attach(pinFoot);
	Foot.setLimits(FOOT_MIN,FOOT_MAX);

	Arm.attach(pinArm);
	Arm.setLimits(ARM_MIN,ARM_MAX);

	Led.attach(pinLed);
}

/************
FRAMED STATE
*************/

void Tourelle::rotate(long startFrame, long stopFrame, int startAnglePct, int stopAnglePct)
{
	if (Animator.check(startFrame,stopFrame))
		Foot.setAnglePct( Animator.linearAnim(startFrame,stopFrame,startAnglePct,stopAnglePct) );
}

void Tourelle::rotate(long frame, int anglePct)
{
	rotate(frame,frame+1,anglePct,anglePct);
}


void Tourelle::elevate(long startFrame, long stopFrame, int startAnglePct, int stopAnglePct)
{
	if (Animator.check(startFrame,stopFrame))
		Arm.setAnglePct( Animator.linearAnim(startFrame,stopFrame,startAnglePct,stopAnglePct) );
}

void Tourelle::elevate(long frame, int anglePct)
{
	elevate(frame,frame+1,anglePct,anglePct);
}


void Tourelle::lightup(long startFrame, long stopFrame, int startIntensityPct, int stopIntensityPct)
{
	if (Animator.check(startFrame,stopFrame))
		Led.setIntensityPct( Animator.linearAnim(startFrame,stopFrame,startIntensityPct,stopIntensityPct) );
}

void Tourelle::lightup(long frame, int intensityPct)
{
	lightup(frame,frame+1,intensityPct,intensityPct);
}


void Tourelle::animate(long startFrame, long stopFrame, int *startState, int *stopState)
{
	rotate(startFrame,stopFrame,startState[0],stopState[0]);
	elevate(startFrame,stopFrame,startState[1],stopState[1]);
	lightup(startFrame,stopFrame,startState[2],stopState[2]);
}

void Tourelle::animate(long frame, int *state)
{
	animate(frame,frame+1,state,state);
}


void Tourelle::randomize(long startFrame, long stopFrame)
{
	if (Animator.check(startFrame,stopFrame)) 
	{
		Foot.setAnglePct( Animator.randAnim() );
		Arm.setAnglePct( Animator.randAnim() );
		Led.setIntensityPct( Animator.randAnim() );
	}
}

void Tourelle::randomize(long frame)
{
	randomize(frame,frame+1);
}

void Tourelle::strobe(long startFrame, long stopFrame, int frequencyFrame)
{
	if (Animator.check(startFrame,stopFrame))
		Led.setIntensityPct( Animator.strobeAnim(frequencyFrame) );
}


/************
INSTANT STATE
*************/
void Tourelle::setState(int *state)
{
	Foot.setAngle(state[0]);
	Arm.setAngle(state[1]);
	Led.setIntensity(state[2]);
}

void Tourelle::setStatePct(int *state)
{
	Foot.setAnglePct(state[0]);
	Arm.setAnglePct(state[1]);
	Led.setIntensityPct(state[2]);
}