/* 
*************************************************/
#include <Arduino.h>
#include "Animator.h"

AnimatorClass::AnimatorClass()
{
	stepCount = 0;
	activeStep = 0;

	currentFrameGlobal = 1;
	totalFrameGlobal = 0;
	
	currentFrameStep = 1;
	totalFrameStep = 0;

	lastFrameTime = 0;
	fps = 25;
}

void AnimatorClass::setFPS(int n_fps)
{
	fps = n_fps;
}

bool AnimatorClass::nextFrame()
{
	currentFrameStep++;
	if (currentFrameStep > totalFrameStep) currentFrameStep = 1;
    
	currentFrameGlobal++;
	if (currentFrameGlobal > totalFrameGlobal) currentFrameGlobal = 1;

  	int delayTime = lastFrameTime+(1000/fps)-millis();
  	if (delayTime > 0) delay(delayTime);
  	lastFrameTime = millis();

  	stepCount = 0;
}

bool AnimatorClass::check(long startFrame, long stopFrame)
{
	totalFrameStep = max(totalFrameStep, stopFrame);
	return (currentFrameStep >= startFrame && currentFrameStep < stopFrame);
}

bool AnimatorClass::checkStep(long startFrame, long stopFrame)
{
	stepCount++;
	totalFrameGlobal = max(totalFrameGlobal, stopFrame);
	bool isIn = (currentFrameGlobal >= startFrame && currentFrameGlobal < stopFrame);
	
	//change active step
	if (isIn && activeStep != stepCount)
	{
		currentFrameStep = 1;
		totalFrameStep = 0;
		activeStep = stepCount;
	} 
		
	return isIn;
}

int AnimatorClass::linearAnim(long startFrame, long stopFrame, int startValue, int stopValue)
{
	return startValue + int(1.0 * (stopValue - startValue) * (currentFrameStep - startFrame) / (stopFrame-startFrame));
}

int AnimatorClass::strobeAnim(int frequencyFrame, int min, int max)
{
	return (currentFrameStep % frequencyFrame > 0) ? min : max;
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