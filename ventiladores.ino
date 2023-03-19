/*-------(libraries)-------*/
#include <IRremote.h>

/*-------(objects)-------*/
IRrecv IR(12);
decode_results results;

/*-------(variables)-------*/
int num_leds = 5;
int ledPin[] = {11, 10, 9, 8, 7};

bool leds_state = true;// Conserva el estado de todos los leds

void setup() {
  IR.enableIRIn(); // Inicializa la librería
  Serial.begin(9600);
  for (int i = 0; i < 5; i++) {
    pinMode(ledPin[i], OUTPUT);
  }
}

void onLed(int led){
  bool led_state = !digitalRead(ledPin[led]);
  digitalWrite(ledPin[led], led_state);
}

// encender o apagar leds
void allLed(){
  for (int i = 0; i < 5; i++) {
      digitalWrite(ledPin[i], leds_state);
  }
  leds_state = !leds_state;
}

void loop() {
  if (IR.decode()) {
    Serial.println(IR.decodedIRData.decodedRawData, HEX);
    switch (IR.decodedIRData.decodedRawData) {
      case 0XF30CFF00:  // boton 1
        onLed(0);
        break; 
      case 0xE718FF00:  // boton 2
        onLed(1);
        break;
      case 0xA15EFF00:  // boton 3
        onLed(2);
        break;
      case 0xF708FF00:  // boton 4
        onLed(3);
        break;
      case 0xE31CFF00:  // boton 5
        onLed(4);
        break;
      case 0xBC43FF00:  // boton de encendido
        allLed();
        break;         
    }
    IR.resume();
  }
}
