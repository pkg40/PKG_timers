/*************************************************************************************
 * PKG_Timers.cpp
 ************************************************************************************
 * Timer Class
 ************************************************************************************
 *   - Version 0.1                                         March 2020
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

#if defined(RTOS) 
#else
	#include <Arduino.h>
#endif
#include <PKG_timers.hpp>

void myTimer::makeTimeString(char* timeStr, unsigned long time, unsigned int mask, bool hundredths, bool verbose) {
		if (hundredths) {
		unsigned int	seconds = time / 100;
		unsigned int	hun = time % 100;
		unsigned int	minutes	=  seconds / 60;
						seconds = seconds % 60;
		if (minutes > 511) {minutes=511;}
		mask = 0x7ff&mask;
		snprintf(timeStr,12, "%4d:%02d:%02d", minutes, seconds, hun);
		}

		else { 
		unsigned int	minutes = time / 60;
		unsigned int	seconds = time % 60;
		unsigned int	hours	= minutes / 60;
						minutes = minutes % 60;
		if (hours > 511) {hours=511;}
		mask = 0x7ff&mask;
		snprintf(timeStr,12, "%4d:%02d:%02d", hours, minutes, seconds);
		}
};

	myTimer::myTimer(unsigned long period){
		_period=period;
		_timeStop=0;
		_timeStart=millis();
	};
	
	myTimer::~myTimer(){}

	unsigned long  myTimer::read() {
		if (_timeStop) { return (_timeStop -_timeStart); }
		else			{ return (millis()-_timeStart);}
	};

	void myTimer::restart() {
		_timeStart = millis();
		_timeStop=0;
	};

	bool myTimer::start() {
		if (_timeStop) {
			_timeStart = millis() - (_timeStop-_timeStart);
			return (true);
		}
		else			{ 
			_timeStart = millis();
			return (false);
		}
	};

	bool  myTimer::stop() {
		if (_timeStop) {return (false);}
		else {
			_timeStop = millis();
			return (true);
		}
	}

	bool myTimer::test(bool verbose) {
		if (_period && ((millis()-_timeStart) > _period)){
			_timeStart = millis();
			if (verbose) {Serial.println("TIME");}
			return (true);
		}
		else {
			return (false);
		}
	};


	myTimedPin::myTimedPin(uint8_t pin, unsigned long time, bool assertedLow): myTimer (time) {
		_pin = pin;
		_assertedLow=assertedLow;
		pinMode(_pin, OUTPUT);
		digitalWrite(_pin, _assertedLow ? HIGH:LOW);
	};

	myTimedPin::~myTimedPin() { }

	void myTimedPin::beep(uint8_t count, unsigned int time) {
		if (_enabled ) {
			if ( time != 0) { _period=time; }
			digitalWrite(_pin, _assertedLow ? LOW:HIGH);
			this->start();
			_beeping=true;
			_beepCount=count;
		}
		else {
			digitalWrite(_pin, _assertedLow ? HIGH:LOW);
		}
	};

	void myTimedPin::setEnable(bool enable) { _enabled=enable;}
	bool myTimedPin::getEnable() { return(_enabled);}

	void myTimedPin::testStop() { 
		if (!_beeping ) return;
		else {
			if (this->test()&&_beepCount == 1) {
				digitalWrite(_pin, _assertedLow ? HIGH:LOW);
				_beeping=false;
				_beepCount=0;
			}
			else if (this->test()) {
				digitalWrite(_pin, _assertedLow ? HIGH:LOW);
				_beepCount--;
			}
		}
	};

	void myTimedPin::suddenStop() { 
		digitalWrite(_pin, _assertedLow ? HIGH:LOW);
		_beeping=false;
		_beepCount=0;
	};
