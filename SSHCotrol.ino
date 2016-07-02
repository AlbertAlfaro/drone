#include <Console.h>
const int ledPin = 13; // se declara el pin donde se conectará el LED
int ByteResivido;      // la variable que contendrá la información de entrada

void setup() {
  // Se inicia la comunicación 
  Bridge.begin();
  Console.begin(); 

  while (!Console){
    ; // Se espera hasta que se conecte la consola
    Console.println("Hola Cliente Bienvenido");
  }
  Console.println("Digite H para encender el led, digite L para apagarlo y P parpadeo  ");
  // Se establece el pin donde se conecta el LED como salida
  pinMode(ledPin, OUTPUT);
}

void loop() {
  
  // Se verifica si hay información entrante
  if (Console.available() > 0) {
    
    // Se lee la información entrante
    ByteResivido = Console.read();
    
    // Se hace la comparación. Si la entrada es una H  se enciende el LED
    if (ByteResivido == 'H' || ByteResivido == 'h') {
      digitalWrite(ledPin, HIGH);
    } 
    // Si la entrada es una L, se apaga el LED
    if (ByteResivido == 'L' || ByteResivido == 'l' ) {
      digitalWrite(ledPin, LOW);
    }
    // Se hace la comparación. Si la entrada es una P para hacer parpadear un LED por unos segundos
    if (ByteResivido == 'P' || ByteResivido == 'p' ) {
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      delay(100);
      digitalWrite(ledPin, HIGH);
      delay(100);
       digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      delay(100);
      digitalWrite(ledPin, HIGH);
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      delay(100);
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      delay(100);
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
    }

    
  }
  delay(100);
}
