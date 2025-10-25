/*
Drinking game

Author: Andreas Amundal (anamu2004)

This code is made to get a servo to point at someone to get them to drink.

Components:
1x Pushbutton
1x Switch (To turn it on and off)
1x Servo
1x LCD Display (16, 2)
1x 10k ohm Potentoimeter
1x 220 ohm resistor

Pins:
2 button
3 DB7
4 DB6
5 DB5
6 DB4
9 servo
11 en / e
12 RS 



*/

#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;

const int button = 2;
const int ppl_input = A0;
const int rs=12, en=11, d4=6, d5=5, d6=4, d7=3;

bool Drunk = true;
int prevRandInt;
int nbr_of_ppl = 2;
int pos = 0;
bool nbr_ppl_select = false;
int max_nbr_ppl = 10;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(ppl_input, INPUT);

  myservo.attach(9); //Set servoen til pin 9

  Serial.begin(9600);
  lcd.begin(16, 2);

  Serial.println("Start the game");

  lcd.setCursor(0, 0);
  lcd.print("Start the game:");
  lcd.setCursor(0, 1);
  lcd.print("Press the button");
  lcd.noCursor();
  
  myservo.write(0);
}

void loop() {
  int buttonPress = digitalRead(button);
  
  if(nbr_ppl_select == false){
    Serial.print("hah");
    lcd.clear();
    while(buttonPress == HIGH){

      int val = analogRead(ppl_input);
      
      nbr_of_ppl = map(val, 0, 1023, 1, max_nbr_ppl);
      if(nbr_of_ppl == 10){
        nbr_of_ppl = 9;
      }
      
      lcd.setCursor(1, 0);
      lcd.print("");
      lcd.setCursor(0, 0);
      lcd.print(nbr_of_ppl);
      lcd.setCursor(2, 0);
      lcd.print("player(s)");
      lcd.setCursor(0, 1);
      lcd.print("selected");
      lcd.noCursor();

      buttonPress = digitalRead(button);
      delay(20);
    }
    nbr_ppl_select = true;
  }
  
  
  int randInt = random(1,nbr_of_ppl + 1);

  int servoDegInterval = 180/nbr_of_ppl;

  if(Drunk == true){

    if(buttonPress == LOW){

      prevRandInt = randInt;

      Serial.print(servoDegInterval);
      Serial.print(",");
      Serial.print(servoDegInterval * randInt);
      Serial.print(",");
      Serial.println(randInt);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Person number");
      lcd.setCursor(14, 0);
      lcd.print(randInt);
      lcd.setCursor(0, 1);
      lcd.print("has to drink");
      lcd.noCursor();
      
      Drunk = false;
      
      
      buttonPress = digitalRead(button);
      
      
      for (pos = 0; pos <= servoDegInterval * randInt; pos += 1) { // servo rotates to person that has to drink
        myservo.write(pos);               // tell servo to go to position in variable 'pos'
        delay(15);                        // waits 15ms for the servo to reach the position
      }

      
      Serial.println("ready to drink");
      delay(10);
    }
    
  }
  else if(Drunk == false){
    if(buttonPress == LOW){  

      Serial.println("Returning to start");
      Drunk = true;

      
      buttonPress = digitalRead(button);
      
      for ( pos = servoDegInterval * prevRandInt; pos >= 0; pos -= 1) { // servo returns to 0
        myservo.write(pos);               // tell servo to go to position in variable 'pos'
        delay(15);                        // waits 15ms for the servo to reach the position
      }
      Serial.println("Choose another player");

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Press button");
      lcd.setCursor(0, 1);
      lcd.print("for next drink");
      lcd.noCursor();

      delay(10);
    }
  }
}
