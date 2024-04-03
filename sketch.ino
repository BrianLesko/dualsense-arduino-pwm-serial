//Test Routine Program - By Stezipoo

#include <Servo.h>

//create servo objects
Servo steering; 
Servo throttle;

int ledPin = 13;
int center = 95;
int right = 55;
int left = 130;

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);     //sets pin 9 to output
  pinMode(10, OUTPUT);
 
  steering.attach(9);   // attach steering servo to pin 9
  throttle.attach(10);  // attach ESC to pin 10
 
  steering.write(95);   // centers steering
  throttle.write(90);   // sets mid throttle
}

int previousPower = 0;

void loop() {
  if (Serial.available() > 0) {
    String incomingMessage = Serial.readStringUntil('\n');

    if (incomingMessage.startsWith("throttle:")) {
      int power = incomingMessage.substring(9).toInt();
      // If the new power is significantly lower than the previous power, decrease it gradually
      if (power < previousPower - 2) { // Change 10 to the maximum amount you want the power to decrease each time
        power = previousPower - 2; // Again, change 10 to the maximum decrease
      }

      throttle.write(power);
      previousPower = power;
    } 
    else if (incomingMessage.startsWith("servo:")) {
      int angle = incomingMessage.substring(6).toInt();
      steering.write(angle);
    }
  }
}
 
 void goLeft(){  // turn left, then go foward and stop
  steering.write(left);  // turn left
  delay(10);
  digitalWrite(ledPin, HIGH);
  delay(500);
  throttle.write(120);  // go forward 
  delay(500);
  throttle.write(90);
  digitalWrite(ledPin, LOW);
  delay(2000);
}
  
void goRight(){  // turn right, then go backward and stop
  steering.write(right);  // turn right
  delay(10);
  digitalWrite(ledPin, HIGH);
  delay(500);
  throttle.write(60);  // go backward
  delay(500);
  throttle.write(90);
  digitalWrite(ledPin, LOW);
  delay(2000);
}