/* 
*************************************************/

#ifndef TOURELLE_H
#define TOURELLE_H

#include <Arduino.h>
#include <Servo.h>
#include <SoftPWM.h>
#include <SoftPWM_timer.h>

#define ANGLE_MIN 0
#define ANGLE_MAX 179

#define FOOT_MIN 50
#define FOOT_MAX 130

#define ARM_MIN 60
#define ARM_MAX 150

#define LED_MIN 0
#define LED_MAX 40


/*** SERVO ***/
class MiniServo : public Servo {

	public:
		MiniServo();
		void setLimits(int min, int max);
		void setAngle(int angle);
		void setAnglePct(int anglePct);

	private:
		int angleMin;
		int angleMax;
};


/*** LED ***/
class MiniLed {
	public:
		MiniLed();
		void attach(int pin);
		void setLimits(int min, int max);
		void setIntensity(int intensity);
		void setIntensityPct(int intensityPct);

	private:
		int pinNumber;
		int ledMin;
		int ledMax;

};

/*** TOURELLE ***/
class Tourelle
{
	public:
		/*INIT*/
		Tourelle();
		void attach(int pinFoot, int pinArm, int pinLed);
		
		/*ANIM*/
		void rotate(long startFrame, long stopFrame, int startAnglePct, int stopAnglePct);
		void rotate(long frame, int anglePct);

		void elevate(long startFrame, long stopFrame, int startAnglePct, int stopAnglePct);
		void elevate(long frame, int anglePct);

		void lightup(long startFrame, long stopFrame, int startIntensityPct, int stopIntensityPct);
		void lightup(long frame, int intensityPct);

		void animate(long startFrame, long stopFrame, int *startState, int *endState);
		void animate(long frame, int *state);

		void randomize(long startFrame, long stopFrame);
		void randomize(long frame);

		void strobe(long startFrame, long stopFrame, int frequencyFrame);

		/*STATE*/
		void setState(int *state);
		void setStatePct(int *state);

	private:
		MiniServo Foot;
		MiniServo Arm;
		MiniLed Led;
};

#endif

