/*
 * Sequencer-micro.cpp
 *
 * Created: 2018-12-09 11:42:26 AM
 * Author : Koltin Kosik-Harvey
 */

#include "timer.h"

#include "Tasks/TaskManager.h"
#include "Tasks/Blinky.h"
#include "Tasks/InputPoll.h"
#include "Tasks/DigitalInput.h"
#include "Tasks/PrintOutput.h"
#include "Tasks/RotaryEncoder.h"
#include "Tasks/InstrumentTrigger.h"

//Define a pointer to a timer object.
Timer timer;

//Digital input task object. Shifts in input and sorts it.
DigitalInput digitalInput;

//Input poll task object latches in the input at regular intervals.
InputPoll inputPoll( timer, digitalInput );

//Acts the same as above, but operates at higher frequency for the encoders
RotaryEncoder rotaryEncoders( timer, digitalInput );

//Task object that deals with the sequencer. 
Sequencer sequencer(timer, digitalInput, rotaryEncoders );

//Task object for printing to output
PrintOutput printOutput( timer, sequencer );

//Task object for instrument trigger
InstrumentTrigger instumentTrigger( timer, sequencer );

//Pointer to

//Pointer to trigger task
//Used for triggering the instruments in the sequencer
//Trigger trigger( timer, blinky );

///////////////////////////////////////////
//TASKS
///////////////////////////////////////////

//Task for triggering
void triggerTask( void ){
	instumentTrigger.run();
}
void triggerSetHigh( void ){
	instumentTrigger.setHigh();
}
void triggerSetLow( void ){
	instumentTrigger.setLow();
}
void sequencerTimerTask( void ){
	sequencer.runTimer();
}
void updateLEDs(void){
	sequencer.updateLEDs();
}
void printOutputTask(void){
	printOutput.print();
}
void printOutputCheck(void){
	printOutput.run();
}

int main(void)
{	

	//Setup interrupts to get the timer to work
	setUpTimerInterrupts();
	timer.reset();
	
	//Initialize task manager
	TaskManager taskManager( timer );

	sequencer.loadInstrumentTriggerReference( instumentTrigger );

	uint16_t testSequence [16] = {
		0xFFFF,0x0000,0xFFFF,0x0000,0xFFFF,0x0000,0xFFFF,0x0000,
		0xFFFF,0x0000,0xFFFF,0x0000,0xFFFF,0x0000,0xFFFF,0x0000
	};
	sequencer.loadSequence(testSequence, 16);

	//Add tasks with priority 0-250. 0 is real time. 251 never runs.
	taskManager.addTask( triggerTask, 128);
	taskManager.addTask( triggerSetLow, 0 );
	taskManager.addTask( triggerSetHigh, 4);
	taskManager.addTask( sequencerTimerTask, 128);
	taskManager.addTask( updateLEDs, 250);
	taskManager.addTask( printOutputTask, 250);
	taskManager.addTask( printOutputCheck, 250);
	
    while (1) 
    {
		taskManager.runTasks();
	}
}

