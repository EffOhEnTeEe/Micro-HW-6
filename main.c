#include <plib.h>
#include "i2cslave.h"

#pragma config FNOSC		= PRIPLL	// Oscillator selection
#pragma config POSCMOD		= XT		// Primary oscillator mode
#pragma config FPLLIDIV 	= DIV_2		// PLL input divider
#pragma config FPLLMUL		= MUL_20	// PLL multiplier
#pragma config FPLLODIV 	= DIV_1		// PLL output divider
#pragma config FPBDIV		= DIV_8		// Peripheral bus clock divider
#pragma config FSOSCEN		= OFF		// Secondary oscillator enable

#pragma config ICESEL           = ICS_PGx1      // ICE/ICD Comm Channel Select
#pragma config DEBUG            = OFF           // Debugger Disabled for Starter Kit

void InitI2C1master() {

  // TO BE DEFINED BY YOU
  // ...

}

void writeI2C1master(unsigned char address, 
                     unsigned char data) {

  // TO BE DEFINED BY YOU
  // ...

}

unsigned char readI2C1master(unsigned char address) {

  // TO BE DEFINED BY YOU
  // ...

}

void readI2C1mastermulti(unsigned char address, 
                         unsigned count,
						 unsigned char *b) {

  // TO BE DEFINED BY YOU
  // ...

}

void InitTimer1() {
   OpenTimer1(T1_ON|T1_PS_1_8, 0xFFFF);
}

void DelayMsTimer1(unsigned int n) {
  unsigned i;
  for (i = 0; i<n; i++) {
    WriteTimer1(0);
    while (ReadTimer1() < 1250);
  }
}

void InitLEDs() {
  PORTSetPinsDigitalOut (IOPORT_G, BIT_12|BIT_13| BIT_14|BIT_15);
}

void ShowLEDs(unsigned char v) {
  mPORTGClearBits(BIT_12|BIT_13| BIT_14|BIT_15);
  mPORTGSetBits((v & 0xF) << 12);
}

int main (void) {
   unsigned char n = 0;
   unsigned char t, b[256];

   // disable the JTAG port
   mJTAGPortEnable(0);

   // enable interrupts
   INTEnableSystemMultiVectoredInt();

   InitI2C2slave();
   InitI2C1master();
   InitTimer1();
   InitLEDs();

   unsigned TEST = 1;
   // TEST 1	tests writeI2C1master()
   // TEST 2    tests readI2C1master()
   // TEST 3	tests readi2C1mastermulti()

   switch (TEST) {
   
     case 1: 
		// first main loop - test writeI2C1master()
		while (1) {
			writeI2C1master(SLAVE_ADDRESS, n++);
			DelayMsTimer1(100);
			ShowLEDs(slavedata);
		}
		break;

	case 2:
		// second main loop - test readI2C1master()
		while (1) {
			writeI2C1master(SLAVE_ADDRESS, n++);
			DelayMsTimer1(100);
			t = readI2C1master(SLAVE_ADDRESS);
			ShowLEDs(t);
		}
		break;

	case 3:
		//third main loop - test readI2C1mastermulti(n, b)
		while (1) {
			writeI2C1master(SLAVE_ADDRESS, n++);
			DelayMsTimer1(100);
			readI2C1mastermulti(SLAVE_ADDRESS, 10, b);
			ShowLEDs(b[9]);
		}
		break;

	}
	
	return 0;
}