/* 
*************************************************/

#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <Arduino.h>


class AnimatorClass {
	public:
		AnimatorClass();

		void setFPS(int n_fps);
		bool nextFrame();
		bool check(long startFrame, long stopFrame);
		bool checkStep(long startFrame, long stopFrame);
		
		int linearAnim(long startFrame, long stopFrame, int startValue, int stopValue);

		int strobeAnim(int frequencyFrame, int min, int max);
		int strobeAnim(int frequencyFrame);
		
		int randAnim(int min, int max);
		int randAnim();


	private:
		int fps;
		int stepCount;
		int activeStep;
		long currentFrameGlobal;
		long totalFrameGlobal;
		long currentFrameStep;
		long totalFrameStep;
		long lastFrameTime;
};
extern AnimatorClass Animator;

#endif

