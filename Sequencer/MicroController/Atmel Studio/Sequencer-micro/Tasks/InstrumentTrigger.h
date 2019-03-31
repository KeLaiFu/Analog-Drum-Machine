/* 
* InstrumentTrigger.h
*
* Created: 2019-03-28 7:05:49 PM
* Author: Koltin Kosik-Harvey
*/


#ifndef __INSTRUMENTTRIGGER_H__
#define __INSTRUMENTTRIGGER_H__

//Global timer
#include "../timer.h"

//Interface to a SIPO shift register.
#include "../Shift_Register/ShiftRegister_SIPO.h"

//Reference to the sequencer task
#include "Sequencer.h"

#define NUM_TRIGGER_SHIFT_REGISTERS 2

class InstrumentTrigger : public ShiftRegister_SIPO
{
	//variables
	public:
		uint8_t * bytesToPrint;
	protected:
	private:
		//Object references.
		Sequencer * sequencer;
		Timer * timer;
	//functions
	public:
		InstrumentTrigger(Timer & timerRef, Sequencer & sequencerRef);

		//Triggers instruments on a beat.
		void run( void );

		//Builds output shift register.
		void buildOutputBuffer( void );

		~InstrumentTrigger();
	protected:
	private:

}; //InstrumentTrigger

#endif //__INSTRUMENTTRIGGER_H__