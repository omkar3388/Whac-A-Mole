#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11); //Pin 10 of arduino as RX |Pin 11 of arduino TX
int gameDelay = 1000; //This is the game speed
int hitButton = 1;
boolean playing = 1; //boolean flag that we'll use to determine where in the scoring cycle we are
int score = 0; //This is the score
int Highscore=0;
void setup(){
  Serial.begin(9600);
  BTserial.begin(9600);                          
  pinMode(2,INPUT);   //set the button pins
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
 
  pinMode(6,OUTPUT);    //set the led pins
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
}


void loop(){

  while(keyPress()==0){ 
    
   
    } //Tap on  a key  to start the game
    
  gameDelay = 1000;
  playing = 1; //Reset the flag from last game
  gameRunning(); //Start the Game
  
}

//This function will flash all buttons and wait for a button press to start the game.
//Speed will be set depending on which button is pressed
boolean keyPress(){

    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    delay(50);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    delay(50);
  boolean pressed = 0;
  
  if(digitalRead(2)==LOW || digitalRead(3)==LOW || digitalRead(4)==LOW || digitalRead(5)==LOW){
  pressed = 1; 
    }
          
  return pressed;
  
}


void gameRunning(){
   score=0;
  BTserial.print("Player 1");
  BTserial.print(",");
  BTserial.print(score);
  BTserial.print(",");
  BTserial.print(Highscore);
  BTserial.print(";");
 
int newLED;           //This is the the LED that we're goign to light next
randomSeed(analogRead(A0)); //Random Seed
delay(1000); 

while(playing == 1){
   
      playing=0; 
      byte randomLed = random(6,10);              // pick a random LED
      
while(newLED == randomLed){              //to make sure it's not the same as the last one
        randomLed = random(6,10); 
      }
      newLED = randomLed; 

int newButton = getButton(newLED); //The getButton function returns the button number corresponding to the LED that's on.

digitalWrite(newLED, HIGH); //Light up the random LED.

for(int t=0; t<gameDelay; t++){        //Game cycles delay
  hitButton = digitalRead(newButton); //Grab the button status
  if(hitButton==0){
    playing=1;
    //delay(100);
    break;
    } //if button was pressed
  delay(1);
}
digitalWrite(newLED, LOW);            //turn off the LED
if(hitButton==0){
score=score+1;                         //increase the score
}
Highscore=max(Highscore,score);
BTserial.print("Player 1");
BTserial.print(",");
BTserial.print(score);
BTserial.print(",");
BTserial.print(Highscore);
BTserial.print(";");

gameDelay=(gameDelay-15); //Speed up the game after every button press
} 
}

int getButton(int newLED){ 

int Button; 
  
 switch (newLED) {
  
   case 6:
   Button = 2;
   break;
   case 7:
   Button = 4;   
   break;
   case 8:
   Button = 5;   
   break;
   case 9:
   Button = 3;   
   break;
  
   
 } 
  
  return Button; 
  
}
