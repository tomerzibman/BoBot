#include <Servo.h>
///////////////////////
//Variable initiation//
///////////////////////
Servo myservo1;
Servo myservo2;
int counter = 0;
char INBYTE;
int pictureState = 0;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  myservo1.attach(10);
  myservo2.attach(11);
}
//////////////
//Functions//
/////////////
void picture() { //Prints in the Serial Monitor for the pi to check
  // pictureState = 1;
  Serial.println(1);
  delay(20);
}
void forward() { //Moves the BoeBot forward
  for (int i = 0; i < 90 ; i++) {
    myservo1.write(0);
    myservo2.write(180);
    delay(20);
  }
}
void backwards() { //Moves the BoeBot forward
  for (int i = 0; i < 90 ; i++) {
    myservo1.write(180);
    myservo2.write(0);
    delay(20);
  }
}
void halt() { // Stops the BoeBot
  myservo1.write(90);
  myservo2.write(90);
}

void right() { //Moves the BoeBot right
  for (int i = 0; i < 64; i++) {
    myservo1.write(180);
    myservo2.write(180);
    delay(2);
  }
  delay(1000);
}

void left() { //Moves the BoeBot left
  for (int i = 0; i < 64 ; i++) {
    myservo1.write(0);
    myservo2.write(0);
    delay(2);
  }

  delay(1000);
}

/////////////
//Main Loop//
/////////////
void loop() {
  halt();
  while (!Serial.available());   // stay here so long as COM port is empty
  INBYTE = Serial.read();        // read next available byte
  if ( INBYTE == 's' ) backwards();
  if ( INBYTE == 'w' ) forward();
  if ( INBYTE == 'a' ) left();
  if ( INBYTE == 'd' ) right();
  if ( INBYTE == 'h' ) halt();
  if ( INBYTE == 'p' ) picture();
  delay(50);
}
