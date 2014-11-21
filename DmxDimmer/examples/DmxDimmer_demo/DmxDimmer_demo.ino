/******don't remove !****/
#include <Animator.h>
#include <DmxMaster.h>
#include <DmxDimmer.h>
/***********************/

#define NBR_DMXDIMMER 27    //Change that if needed


/******don't remove !****/
DmxDimmer dimmer[NBR_DMXDIMMER];
/***********************/

void setup() {
  
        //when the setup begin  
	DmxMaster.usePin(3); //don't remove !

        //optional FPS adjustment
        Animator.setFPS(25);
	
        //sample dmx declaration
        int addressDmx = 1;
	for (int i=0; i<NBR_DMXDIMMER; i++) dimmer[i].attach(addressDmx+i);
}

void loop() {


        if (Animator.checkStep(1,70) ) step1();
        if (Animator.checkStep(71,200) ) step2();
        /*** ADD MORE STEPS HERE **/

	Animator.nextFrame();
}

void step1() {

        //sample animate all
        for (int i=0; i<NBR_DMXDIMMER; i++)
        {
                dimmer[i].strobe(1,50,5);
        }

}

void step2() {

        //sample animate all
        for (int i=0; i<NBR_DMXDIMMER; i++)
        {
                dimmer[i].lightup(1,50,0,100);
                dimmer[i].lightup(51,100,100,0);
        }
        
}


