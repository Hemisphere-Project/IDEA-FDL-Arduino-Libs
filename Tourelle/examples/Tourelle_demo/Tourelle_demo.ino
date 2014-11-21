/******don't remove !****/
#include <Servo.h>        
#include <SoftPWM.h>
#include <SoftPWM_timer.h>
#include <Animator.h>
#include <Tourelle.h>
/***********************/

#define NBR_TOURELLE 3   //Change that if needed

/******don't remove !****/
int *state(int a, int b, int c) {
  return (int[]) {a,b,c};
}

Tourelle tour[NBR_TOURELLE];
/***********************/

void setup() {
    //when the setup begin  
	SoftPWMBegin(); //don't remove !

    //optional FPS adjustment
	Animator.setFPS(25);
	
    //sample tower declaration
	tour[0].attach(9,6,7);
    tour[1].attach(3,5,4);
    tour[2].attach(10,11,12);
}

void loop() {

	if (Animator.checkStep(1,70) ) step1();
    if (Animator.checkStep(71,200) ) step2();
    /*** ADD MORE STEPS HERE **/

    //when the loop end
	Animator.nextFrame(); //don't remove !
}


void step1() {

	//sample animate all
    tour[0].animate(1, 10, state(0,0,0), state(100,50,20) );
    tour[0].animate(11, 20, state(100,50,20), state(50,100,100) );
    tour[0].animate(21, 30, state(50,100,100), state(0,0,0) );
}

void step2() {

    //sample animate detailed 
    tour[0].rotate(1,50,0,100);
    
    tour[0].elevate(1,40,0,100);
    tour[0].elevate(41,50,100,0);
    
    tour[0].strobe(1,50,5);    
}

