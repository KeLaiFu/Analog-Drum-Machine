/* 
* SevenSeg.cpp
*
* Created: 2018-12-23 11:15:31 PM
* Author: k0s
*/
#include "SevenSeg.h"

// default constructor
SevenSeg::SevenSeg( uint8_t numberOfDisplays )
{
	//Store this variable for later.
	size = numberOfDisplays;
	
	//Allocate memory for numbers to print
	//if we print the number 123, then the array would look like
	// [1, 2, 3]. And those single digit numbers will be printed to the seven seg display
	numbersToPrint = new uint8_t[size];
	
	//Seven Seg bitmaps for the above
	bitMaps = new uint8_t[size];

} //SevenSeg

void SevenSeg::loadValue( uint16_t value )
{
	for(uint8_t i = 0; i < size ; i++)
	{
		//numberToPrint[1++] gets the 10s, 100s, etc.
		numbersToPrint[i] = (value / pow10[i]) % 10;
		
		//Prepare shift registers to hold bit map for seven segment display
		//If input number is too large just make it 10 (a dot on the seven seg)
		if ( numbersToPrint[i] > 9 ){
			numbersToPrint[i] = 10;
		}
		
		//Get bitmaps
		bitMaps[i] = sevenSegBitMap[ numbersToPrint[i] ];
	}
}

// default destructor
SevenSeg::~SevenSeg()
{
	delete numbersToPrint;
	delete bitMaps;
} //~SevenSeg
