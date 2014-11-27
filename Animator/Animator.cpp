/* 
*************************************************/
#include <Arduino.h>
#include "Animator.h"

#if defined(__AVR_ATmega2560__)
#define RESET_INTERRUPT 2 
#else
#define RESET_INTERRUPT 0
#endif

AnimatorClass::AnimatorClass()
{
	endPin = 0;

	currentFrameGlobal = 1;
	totalFrameGlobal = 0;
	
	totalFrameStep = 0;
	offsetFrameStep = 1; 

	lastFrameTime = 0;
	fps = 25;
}

//absolute frame in the global timeline
int AnimatorClass::getFrame() {
	return currentFrameGlobal;
}

//calculate relative frame in the step specific timeline
int AnimatorClass::getFrameStep() 
{
	return ((getFrame()-offsetFrameStep)%totalFrameStep)+1;
}

void AnimatorClass::setFPS(int n_fps)
{
	fps = n_fps;
}

void AnimatorClass::extSync(int _endPin)
{
	endPin = _endPin;
	pinMode(endPin,OUTPUT);
	
	attachInterrupt(RESET_INTERRUPT, reinterpret_cast<void (*)()>(&extRestart), RISING);
}

void AnimatorClass::extRestart()
{
	Animator.restart();
}

void AnimatorClass::restart()
{
	currentFrameGlobal = 1;
}

bool AnimatorClass::nextFrame()
{
	//External SYNC => catch the end and wait for interrupt
	if (endPin > 0 && currentFrameGlobal == totalFrameGlobal)
	{
		digitalWrite(endPin,LOW);
		delay(10);
		digitalWrite(endPin,HIGH); //alert others that i'm done
		while(currentFrameGlobal == totalFrameGlobal) delay(1); //go to sleep
	}
	
	//GLOBAL progress
	currentFrameGlobal++;
	if (currentFrameGlobal > totalFrameGlobal) restart();

	//FPS Delay
	int delayTime = lastFrameTime+(1000/fps)-millis();
	if (delayTime > 0) delay(delayTime);
	lastFrameTime = millis();
}

bool AnimatorClass::check(long startFrame, long stopFrame)
{
	totalFrameStep = max(totalFrameStep, stopFrame);
	return (getFrameStep() >= startFrame && getFrameStep() < stopFrame);
}

bool AnimatorClass::checkStep(long startFrame, long stopFrame)
{
	totalFrameGlobal = max(totalFrameGlobal, stopFrame);
	bool isIn = (currentFrameGlobal >= startFrame && currentFrameGlobal < stopFrame);
	
	//set reference for the current step
	if (isIn)
	{
		offsetFrameStep = startFrame;
		totalFrameStep = 0;
	}
		
	return isIn;
}

int AnimatorClass::linearAnim(long startFrame, long stopFrame, int startValue, int stopValue)
{
	return startValue + int(1.0 * (stopValue - startValue) * (getFrameStep() - startFrame) / (stopFrame-startFrame));
}

int AnimatorClass::strobeAnim(int frequencyFrame, int min, int max)
{
	return (getFrameStep() % frequencyFrame > 0) ? min : max;
}

int AnimatorClass::strobeAnim(int frequencyFrame)
{
	return strobeAnim(frequencyFrame,0,100);
}

int AnimatorClass::randAnim(int min, int max)
{
	return round(random(min,max));
}

int AnimatorClass::randAnim()
{
	return randAnim(0,100);
}

AnimatorClass Animator;