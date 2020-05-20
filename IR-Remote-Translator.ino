// Josh Sooknanan 5/19/2020
// IR Remote Translator
// Use my Samsung TV remote to control my Vizio sound bar nicely 

#include <IRremote.h>

int recvPin = 11;
IRrecv irrecv(recvPin);

IRsend irsend;

// SAMSUNG Codes, decode_type 7
const unsigned long samsung_vol_up = 0xE0E0E01F;
const unsigned long samsung_vol_down = 0xE0E0D02F;
const unsigned long samsung_power = 0xE0E040BF;

// Vizio codes, decode_type NEC
const unsigned long viz_vol_up = 0xFF827D;
const unsigned long viz_vol_down = 0xFFA25D;
const unsigned long viz_power = 0xFF02FD;
const unsigned long viz_optical = 0xFF13EC;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:
  decode_results results;
          
  if (irrecv.decode(&results)) {
    Serial.print("Received: ");
    Serial.print(results.decode_type);
    Serial.print(" ");
    Serial.println(results.value);
    
    if (results.decode_type == 7) {
      
      switch(results.value) {
        
        case samsung_power:
          Serial.println("Received Samsung power, sending Vizio power.");
          irsend.sendNEC(viz_power, 32);
          delay(10000);
          irsend.sendNEC(viz_optical, 32);
          delay(40);
          break;
          
        case samsung_vol_up:
          Serial.println("Received Samsung volume up, sending Vizio volume up");
          irsend.sendNEC(viz_vol_up, 32);
          delay(40);
          break;
          
        case samsung_vol_down:
          Serial.println("Received Samsung volume down, sending Vizio volume down");
          irsend.sendNEC(viz_vol_down, 32);
          delay(40);
          break;

        default:
          Serial.println("No selection made.");
          break;
      }
    }
    irrecv.enableIRIn();
    irrecv.resume();
  }
}
