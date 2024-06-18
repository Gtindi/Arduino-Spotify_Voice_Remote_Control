#include <Arduino.h>
#include <IRremote.h>

// Bluetooth HC-05 module pins
String voice;


// Define IR receiver pin
const int RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the IR receiver
}

void loop() {

  // Check for Bluetooth commands
  while(Serial.available()) {
    delay(10);
    char c=Serial.read();
    Serial.println(c);
    if (c=='\n')
    break;
    voice += c;
  }

  // Voice commnds from bluetooth
  if (voice.length() > 0) {
    Serial.println("Received: " + voice);
    if (voice == "next") {
      Serial.println("Sending next command to Spotify");
    }
    else if (voice == "previous") {
      Serial.println("Sending previous command to Spotify");
    }
    else if (voice == "playpause") {
      Serial.println("Sending playpause command to Spotify");
    }
    voice ="";
  }

    // IR remote control handling
  if (irrecv.decode(&results)) {
    switch(results.value) {
      case 0xFFC23D: // IR signal for PLAY/PAUSE
        Serial.println("playpause");
        executeCommand("playpause");
        break;
      case 0xFF22DD: // IR signal for NEXT
        Serial.println("previous");
        executeCommand("next");
        break;
      case 0xFF02FD: // IR signal for PREVIOUS
        Serial.println("next");
        executeCommand("previous");
        break;
      default:
        break;
    }
    irrecv.resume(); // Receive the next value
  }

}

void executeCommand(String command) {
  if (voice.length() > 0) {
    Serial.println("Received: " + voice);
    if (voice == "next") {
      Serial.println("Sending next command to Spotify");
    }
    else if (voice == "previous") {
      Serial.println("Sending previous command to Spotify");
    }
    else if (voice == "playpause") {
      Serial.println("Sending playpause command to Spotify");
    }
    voice ="";
  }
  command = voice;
}