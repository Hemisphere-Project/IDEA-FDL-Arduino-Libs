/* 
*************************************************/

#ifndef DMXDIMMER_H
#define DMXDIMMER_H

#define VALUE_MIN 0
#define VALUE_MAX 255

#include <Arduino.h>

class DmxDimmer {
	public:
		DmxDimmer();

		void attach(int chan);
		void setLimits(int min, int max);

		void setIntensity(int intensity);
		void setIntensityPct(int intensityPct);

		void lightup(long startFrame, long stopFrame, int startIntensityPct, int stopIntensityPct);
		void lightup(long frame, int intensityPct);

		void randomize(long startFrame, long stopFrame);
		void randomize(long frame);

		void strobe(long startFrame, long stopFrame, int frequencyFrame);


	private:
		int channel;
		int min;
		int max;
};

#endif

