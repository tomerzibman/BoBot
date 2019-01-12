//--------------------------------------------------------------------------//
// Project: Tracking down robot---------------------------------------------//
// Name: Ron Sadovsky and Tomer Zibman--------------------------------------//
// Description: BoeBot will scan area 3 times and move to the nearest object//
// Date: January 25, 2017---------------------------------------------------//
//--------------------------------------------------------------------------//
#include <Servo.h>
#include <LiquidCrystal.h>
#define trigPin 3
#define echoPin 2
long timePeriod, distance, sensor;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//-------------------------------//
// Declaration of code variables // 
//-------------------------------//

int distance1;
int distance2;
int distance3;

Servo myservo;
Servo myservo1;
Servo myservo2;

boolean scanComplete = false;

//-------------------------------//
// Declaration of code functions // 
//-------------------------------//

void forward() { //Moves the BoeBot forward
  for (int i = 0; i < 90 ; i++) {
    myservo1.write(0);
    myservo2.write(180);
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

void lcdPrint() { // Function that determines distance and prints on LCD screen
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  timePeriod = pulseIn(echoPin, HIGH);
  distance = (timePeriod / 2 ) / 29.1;
  if (distance == 0) {
    distance = (timePeriod / 2 ) / 29.1;
  }
  lcd.print("   ");
  lcd.print(distance);
  lcd.print("cm");
  lcd.print("   ");
  delay(500);
  lcd.clear();
  Serial.print(distance);
  Serial.println("cm ");
  delay(20);
}

void servo() { //Function that controls the servo
  for (int i = 0; i < 122 ; i++) {
    myservo.write(180);
    delay(20);
  }
  delay(1000);
  lcdPrint();
  distance1 = distance;

  for (int i = 0; i < 122 ; i++) {
    myservo.write(0);
    delay(20);
  }
  delay(1000);
  lcdPrint();
  distance2 = distance;

  for (int i = 0; i < 122 ; i++) {
    myservo.write(90);
    delay(20);
  }
  delay(1000);
  lcdPrint();
  distance3 = distance;
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.begin(16, 2);
  myservo1.attach(10);
  myservo2.attach(11);
  myservo.attach(13);
}
//--------------------------//
// Main Program Begins Here //
//--------------------------//
void loop() {

  if (scanComplete == false) {
    halt();
    servo();
    scanComplete = true;
  }

  if (scanComplete == true) {
    if (distance1 < distance2 && distance1 < distance3) {
      right();
      forward();
    }
    if (distance2 < distance1 && distance2 < distance3) {
      forward();
    }
    if (distance3 < distance1 && distance3 < distance2) {
      left();
      forward();
    }
  }

  scanComplete = false;


}
