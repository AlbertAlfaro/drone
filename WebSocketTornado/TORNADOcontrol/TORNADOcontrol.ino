/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/
int state = 0; 
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
 if(Serial.available()){
   state = Serial.read(); 
       switch (state)
       {
       case 'N':
       digitalWrite(13, HIGH);
       Serial.println("LED: OFF");
       break;
       case 'F':
       digitalWrite(13, LOW);
       Serial.println("LED: ON");
       break;
       
       }
  
  
  }
}
