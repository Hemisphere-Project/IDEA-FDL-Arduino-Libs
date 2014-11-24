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
		void restart();
		
		bool check(long startFrame, long stopFrame);
		bool checkStep(long startFrame, long stopFrame);
		
		int linearAnim(long startFrame, long stopFrame, int startValue, int stopValue);

		int strobeAnim(int frequencyFrame, int min, int max);
		int strobeAnim(int frequencyFrame);
		
		int randAnim(int min, int max);
		int randAnim();
		
		void extSync(int _endPin);
		static void extRestart();


	private:
		int endPin;
		int fps;
		int stepCount;
		int activeStep;
		volatile long currentFrameGlobal;
		long totalFrameGlobal;
		volatile long currentFrameStep;
		long totalFrameStep;
		long lastFrameTime;
};
extern AnimatorClass Animator;

#endif

