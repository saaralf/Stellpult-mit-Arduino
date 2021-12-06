/*
 Weichen- und Signal-Dekoder Aufsatz-Dekoder f. Basisplatine
 
 Signal-Type see signal_def.h
 
 HW         = Basisboard-RJ45-1.1 
 oder 
 HW20       = Basisplatine 02.00
 HW aufsatz = RT_Weiche_Signal 0.1
 SW Version:    0.3
 
 *  Created on: 30 Nov 2016
 *  Changed on: 06 Mar 2017   
 *  Changes marked with "@Thamm 01.03.2017"
 *  Changes necessary when using the SX30 Lib.
 *  Copyright:  Michael Blank und Reinhard Thamm
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

 */
#include <Arduino.h> 
#include <EEPROM.h>
#include "Signal.h"
#include "Turnouts.h"
#include "hwConfig.h"
#include "signal_def.h"

#define HW20      // if HW20 is defined, then "Basisplatine 2.00" is used
           // if not defined, then Basisplatine 1.1 is used
           // the pins are different and a different SX Library must be used

#ifdef HW20
#include <SX30.h>   // this is the Selectrix library SX30 for Basisplatine 2.00
                    //           @Thamm 01.03.2017
#define PROGBUTTON   (A6)    // for entering programming mode  @Thamm 01.03.2017
#define KEYPRESS   (analogRead(PROGBUTTON)>512)
#else
#include <SX22b.h>   // this is the Selectrix library SX22b for Basisplatine 1.1
#define PROGBUTTON   (3)    // for entering programming mode
#define KEYPRESS   (!digitalRead(PROGBUTTON))  
#endif


// für den Programmiervorgang über den SX-Bus:
#define PROGLED      13  


#define DEBOUNCETIME 200
boolean programming = false;

//======= take configuration from hwConfig. h ================================

//================== config end ===============================================

uint32_t timer = 0;
uint32_t greenTime = 0;
uint32_t keyPressTime = 0;

#ifdef HW20
SX30 sx;                // library  @Thamm 01.03.2017
#else
SX22b sx;                // library
#endif


//SX22Command sxcmd;       // holds command data

static byte oldSXData, SXAddr;


Signal sigA(0);
Signal sigB(1);

// A0 beim Arduino

void sxisr(void) {
	// if you want to understand this, see:
	// http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1239522239   
	sx.isr();
	static uint8_t fast = 0;
	fast++;
	uint8_t v = fast >> 4;
	// counting with higher 4 bits of "fast" only
	if (sigA.actual[0] > v) {
		SIG_A_R_ (HIGH);
	} else {
		SIG_A_R_ (LOW);
	}
	if (sigA.actual[1] > v) {
		SIG_A_G_ (HIGH);
	} else {
		SIG_A_G_ (LOW);
	}
	if (sigA.actual[2] > v) {
		SIG_A_Y_ (HIGH);
	} else {
		SIG_A_Y_ (LOW);
	}
	if (sigA.actual[3] > v) {
		SIG_A_4_ (HIGH);
	} else {
		SIG_A_4_ (LOW);
	}

	// signal b
	if (sigB.actual[0] > v) {
		SIG_B_R_ (HIGH);
	} else {
		SIG_B_R_ (LOW);
	}
	if (sigB.actual[1] > v) {
		SIG_B_G_ (HIGH);
	} else {
		SIG_B_G_ (LOW);
	}
	if (sigB.actual[2] > v) {
		SIG_B_Y_ (HIGH);
	} else {
		SIG_B_Y_ (LOW);
	}
	if (sigB.actual[3] > v) {
		SIG_B_4_ (HIGH);
	} else {
		SIG_B_4_ (LOW);
	}

}

void setup() {
	programming = false;
	pinMode(PROGLED, OUTPUT);
	digitalWrite(PROGLED, LOW);
	pinMode(PROGBUTTON, INPUT);
	digitalWrite(PROGBUTTON, HIGH);  // pull up

	// init signal and turnout outputs
	sigA.init();
	sigB.init();
	turnouts.init(enablePin);
	
	// check, if decoder address in EEPROM
	SXAddr = EEPROM.read(EEPROM_ADDR);
	if ((SXAddr == 0) || (SXAddr > MAX_ADDR)) {    // never stored before or invalid
		SXAddr = DECODER_ADDR;   // use default address
		EEPROM.write(EEPROM_ADDR, SXAddr);  // store address
		delay(10);
	}

	sx.init();

	

#ifdef HW20
// changing slope on INT0 triggers the interrupt routine sxisr (see above)
	attachInterrupt(0, sxisr, CHANGE);  // @Thamm 01.03.2017
#else
// RISING slope on INT0 triggers the interrupt routine sxisr (see above)
  attachInterrupt(0, sxisr, RISING);
#endif

}

void startModuleProgramming() {
	programming = true;
	keyPressTime = millis();
	digitalWrite(PROGLED, HIGH);
	
	// try to write current address on the sx-bus
	// returns "0" when successful
	while (sx.set(SX_CHAN_ADDR, SXAddr) != 0) { 
		delay(10);
	}

}

void finishModuleProgramming() {
	programming = false;
	uint8_t newAddress = sx.get(SX_CHAN_ADDR);   //get sx data from bus
	if ((newAddress > 0) && (newAddress <= MAX_ADDR)) {
		SXAddr = newAddress;   // use default address
		EEPROM.write(EEPROM_ADDR, SXAddr);  // store address
		delay(10);	
	}
	digitalWrite(PROGLED, LOW);
}

boolean keypressed() {
	if ((millis()- keyPressTime) < 5*DEBOUNCETIME) {
		// totzeit von 1sec
		return false;
	}

  if (KEYPRESS) {   
		delay(DEBOUNCETIME);
		if (KEYPRESS) {   // @Thamm 01.03.2017
			keyPressTime = millis();
			return true;
		}
	} else {
		return false;
	}
}

void loop() {
	sigA.process();   // for led fading
	sigB.process();

	// check selectrix channels for changes
	byte d = sx.get(SXAddr);

	if (d != oldSXData) {
		// signal 0 = highest 2 bits
		byte v = (d & 0xC0) >> 6;
		sigA.set(v);

		// signal 1 = bit 5/6
		v = (d & 0x30) >> 4;
		sigB.set(v);

		//turnouts bits 1,2,3,4
		v = (d & 0x0ff);
		for (uint8_t i = 0; i < 4; i++) {
			turnouts.set(i, bitRead(v, i));
		}
		
		oldSXData = d;
	}

	uint8_t track = sx.getTrackBit();
	if (programming) { 
		if (track || keypressed() ) {
			// finish programming when track voltage is enabled again
			finishModuleProgramming();
		} 
	} else if ( (track == 0) && keypressed()) {
		// start programming only if track voltage is disabled and
		// key is pressed and not already programming
		startModuleProgramming();
	}
	
}

