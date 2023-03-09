/*-------(libraries)-------*/
#include <IRremote.h>

/*-------(objects)-------*/
IRrecv IR(12);
decode_results results; //

/*-------(variables)-------*/
int num_leds = 5;
int ledPin[] = {11, 10, 9, 8, 7};
int current_LED = 0;

bool leds_state = true;

//---------------------------------------------------------Selector de leds----------------------------------------------------------------------------------------------------

void setup() {
  IR.enableIRIn(); // Inicializa la librería
  Serial.begin(9600);
  for (int i = 0; i < 5; i++) {
    pinMode(ledPin[i], OUTPUT);
  }
}

// seleccionar leds
void selectLed(){
  for (int i = 0; i < 5; i++) {
    if (i == current_LED) {
        digitalWrite(ledPin[i], HIGH);
      } else {
        digitalWrite(ledPin[i], LOW);
    }
  }
}

// encender o apagar leds
void onLED(){
  for (int i = 0; i < 5; i++) {
      digitalWrite(ledPin[i], leds_state);
  }
  leds_state = !leds_state;
}

// Compara los datos de entrada del control y responde con una función
void irloop(){
  if (IR.decode()) {
    switch (IR.decodedIRData.decodedRawData) {
      case 0xBB44FF00:  // Botón de retroceso
      if(current_LED > 0){
        current_LED--;
      }
      else{
        current_LED = num_leds-1;
      }
      selectLed();
      break;
      case 0xBF40FF00:  // Botón de avance
      if(current_LED < num_leds-1){
        current_LED++;
      }
      else{
        current_LED = 0;
      }
      selectLed();
      break;
      case 0xBC43FF00: // Botón de encendido y apagado
        onLED();
        break;
    }
    IR.resume(); // Se prepara para recibir mas datos
  }
}


void loop() {
  Serial.println(current_LED);
  irloop();
}
