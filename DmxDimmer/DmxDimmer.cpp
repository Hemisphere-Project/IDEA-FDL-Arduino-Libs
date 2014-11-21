/* 
*************************************************/
#include <Arduino.h>
#include <DmxMaster.h>
#include "DmxDimmer.h"
#include "Animator.h"

DmxDimmer::DmxDimmer()
{
	channel = 0;
	min = VALUE_MIN;
	max = VALUE_MAX;
}

void DmxDimmer::attach(int chan)
{
	channel = chan;
}

void DmxDimmer::setLimits(int n_min, int n_max)
{
	min = n_min;
	max = n_max;
}


void DmxDimmer::setIntensity(int intensity)
{
	DmxMaster.write(channel,intensity);
}

void DmxDimmer::setIntensityPct(int intensityPct)
{
	setIntensity( map(intensityPct,0,100,min,max) );
}


void DmxDimmer::lightup(long startFrame, long stopFrame, int startIntensityPct, int stopIntensityPct)
{
	if (Animator.check(startFrame,stopFrame))
		setIntensityPct( Animator.linearAnim(startFrame,stopFrame,startIntensityPct,stopIntensityPct) );
}

void DmxDimmer::lightup(long frame, int intensityPct)
{
	lightup(frame,frame+1,intensityPct,intensityPct);
}

void DmxDimmer::randomize(long startFrame, long stopFrame)
{
	if (Animator.check(startFrame,stopFrame))
		setIntensityPct( Animator.randAnim() );
}

void DmxDimmer::randomize(long frame)
{
	randomize(frame,frame+1);
}

void DmxDimmer::strobe(long startFrame, long stopFrame, int frequencyFrame)
{
	if (Animator.check(startFrame,stopFrame))
		setIntensityPct( Animator.strobeAnim(frequencyFrame) );
}


