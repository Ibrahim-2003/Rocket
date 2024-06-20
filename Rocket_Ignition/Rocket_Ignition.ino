#include <IRremote.h>

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;
long code;
bool activated = 0;

#define OK_CODE 0xE31CFF00
#define CONTROL_PIN 4
#define LED_PIN 3

/*
Remote Control Codes
--------------------
OK: E31CFF00
UP: E718FF0
DOWN: AD52FF0
LEFT: F708FF00
RIGHT: A55AFF00
1: BA45FF00
2: B946FF00
3: B847FF00
4: BB44FF00
5: BF40FF00
6: BC43FF00
7: F807FF00
8: EA15FF00
9: F609FF00
0: E619FF00
*: E916FF00
#: F20DFF00
*/

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  pinMode(CONTROL_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(CONTROL_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
}

void loop(){
  if (IrReceiver.decode()) {

    code = IrReceiver.decodedIRData.decodedRawData;
    // Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Print "old" raw data
    if(code == OK_CODE){
      if(!activated){
        turn_on();
        activated = true;
      }else{
        turn_off();
        activated = false;
      }
    }

    IrReceiver.resume(); // Enable receiving of the next value

  }
}

void turn_on(void){
  Serial.println(F("ON"));
  digitalWrite(CONTROL_PIN, HIGH);
  digitalWrite(LED_PIN, HIGH);
}

void turn_off(void){
  Serial.println(F("OFF"));
  digitalWrite(CONTROL_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
}