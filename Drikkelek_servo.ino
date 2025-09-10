/*
Drinking game

Author: Andreas Amundal (anamu2004)

This code is made to get a servo to point at someone to get them to drink.
I'am going to make a 3D printed case for the game.

It takes:
1 Pushbutton
1 Servo
1 LCD Display
1 Potentoimeter



*/

#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;

const int nbr_of_people = 3;
const int button = 2;
bool Drunk = true;
int prevRandInt;

int pos = 0;

void setup() {
  pinMode(button, INPUT);

  myservo.attach(9); //Set servoen til pin 9

  Serial.begin(9600);
  Serial.println("Start the game");

}

void loop() {
  int buttonPress = digitalRead(button);

  int randInt = random(1,nbr_of_people + 1);

  int servoDegInterval = 180/nbr_of_people;
  if(Drunk == true){
    if(buttonPress == HIGH){

      prevRandInt = randInt;

      Serial.print(servoDegInterval);
      Serial.print(",");
      Serial.print(servoDegInterval * randInt);
      Serial.print(",");
      Serial.println(randInt);
      Drunk = false;
      
      while(buttonPress == HIGH){
        buttonPress = digitalRead(button);
      }
      
      for (pos = 0; pos <= servoDegInterval * randInt; pos += 1) { // goes from 0 degrees to 180 degrees
        myservo.write(pos);               // tell servo to go to position in variable 'pos'
        delay(15);                        // waits 15ms for the servo to reach the position
      }

      
      Serial.println("ready to drink");
      delay(100);
    }
    
  }
  else if(Drunk == false){
    if(buttonPress == HIGH){  

      Serial.println("Returning to start");
      Drunk = true;

      while(buttonPress == HIGH){
        buttonPress = digitalRead(button);
      }
      for ( pos = servoDegInterval * prevRandInt; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
        myservo.write(pos);               // tell servo to go to position in variable 'pos'
        delay(15);                        // waits 15ms for the servo to reach the position
      }
      Serial.println("Choose another player");
      delay(100);
    }
  }
}
