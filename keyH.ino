#include <Keypad.h>
#include "pitch.h"
const byte ROWS = 4;
const byte COLS = 4;

/*int keys [ROWS][COLS] = {
{55, 56, 57, 58},
{50, 51, 52, 53},
{45, 46, 47, 48},
{40, 41, 42, 43}
};*/

int keys[ROWS][COLS] = {
{NOTE_G3, NOTE_GS3, NOTE_A3, NOTE_AS3},
{NOTE_D3, NOTE_DS3, NOTE_E3, NOTE_F3},
{NOTE_A2, NOTE_AS2, NOTE_B2, NOTE_C3},
{NOTE_E2, NOTE_F2, NOTE_FS2, NOTE_G2}
};

byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the kpd

Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int duration;
unsigned long startTime;
 
int rawVal;
int potVal;

String msg;

int note; 
float hz; 

void setup() {
	
 Serial.begin(9600);
 startTime = millis();
 msg = "";
}

void loop() {	
 if ( (millis()-startTime)>1000 ) {
	rawVal=analogRead(A1);
 potVal = constrain(rawVal,10,1000)	;
	duration = potVal;
 startTime = millis();
}
	
if (kpd.getKeys()){
 for (int i=0; i<LIST_MAX; i++) {  // Scan the whole key list.
  if (kpd.key[i].stateChanged) { // Only find keys that have changed state.
   switch (kpd.key[i].kstate) {
     case PRESSED:
        msg = " PRESSED.";
					  //tone(8, notes[thisSensor], 20);
					//hz = pow (2.0, ((float)(note-69)/12.0));
					   tone(11,kpd.key[i].kchar,duration);
					
					
        break;
     case HOLD:
    //    msg = " HOLD.";
        break;
     case RELEASED:
        msg = " RELEASED.";
					noTone(11);
        break;
     case IDLE:
    //    msg = " IDLE.";
					   break;
     }
   Serial.print("Key ");
   Serial.print(kpd.key[i].kchar);
   Serial.println(msg);
   }
  }
 }
	
	
//	finalValue = map(potV)
}  


/*void frequencyFromNoteNumber( note ) {	return 440 * Math.pow(2,(note-69)/12);
	
}*/





