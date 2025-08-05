/* ************************************************************************************
 * displayUpdateLoop.h
 ************************************************************************************
 * Trolling Motor Controller with a number of cool features
 ************************************************************************************
 *   - Version 1.0                                         March 2020
 ************************************************************************************
 * Copyright (c)       2016-2020 Peter K  Green            - pkg40@yahoo.com
 ************************************************************************************
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
 * Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 ************************************************************************************/
#pragma once

#include <TRACE.h>

#if defined(RTOS)
#else
	#include <Arduino.h>
#endif

#ifndef SECONDS
	#define SECONDS 1000
#endif

#ifndef binSECONDS
	#define binSECONDS 1024
#endif

//* myTimer Class
class myTimer
{
protected:
	unsigned long _timeStart;
	unsigned long _timeStop;
	unsigned long _period;

public:

	myTimer(unsigned long period);
	~myTimer();

			bool 	test( bool = false );
unsigned 	long 	read();
			bool 	stop();
			bool 	start();
			void 	restart();
static		void	makeTimeString(char*, unsigned long, unsigned int, bool, bool ) ;
};

class myTimedPin : public myTimer {
	private:
		uint8_t _pin;
		uint8_t _beepCount;
		bool _beeping = false,_toggling=false;
		bool _enabled = false;
		bool _assertedLow;

	public:

	myTimedPin(uint8_t, unsigned long, bool = false);
	~myTimedPin();

	void beep(uint8_t = 1, unsigned int=0);
	bool getEnable();
	void setEnable(bool);
	void testStop();
	void suddenStop();
};