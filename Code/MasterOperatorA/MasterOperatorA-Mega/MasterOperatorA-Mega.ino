#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(53, 52, 50, 49, 48, 47);

//analog stick
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = A0; // analog pin connected to X output
const int Y_pin = A1; // analog pin connected to Y output
int xValue, yValue;

//the motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 13;           //control pin 1 on the motor driver for the right motor
const int AIN2 = 12;            //control pin 2 on the motor driver for the right motor
const int PWMA = 11;            //speed control pin on the motor driver for the right motor

// SonicDistance
const int trigPin = 22;           //6connects to the trigger pin on the distance sensor
const int echoPin = 24;           //5connects to the echo pin on the distance sensor

//IRDistance
const int irPin1 = 23;
const int ePin1 = 25;
float distance = 0;               //stores the distance measured by the distance sensor

//Tilt
int blueLed = 7;
int redLed = 6;
int tiltOut = 4;
int tiltIn = A2;

//LEDs
int led1 = 45;    //pin number 11 has led1
int led2 = 43;    //pin number 10 has led2
int led3 = 41;     //pin number 9 has led3
int led4 = 39;     //pin number 6 has led4
int led5 = 37;     //pin number 5 has led5
const int full = 255;
const int low = 51;
const int off = LOW;

// Game code
int over = 0;
int count = 10; // Our blink counter
int sensor =0;
int win = 3;
float redValue;
float greenValue;
float blueValue;
int inputFromDB;
int switchCase = 6;

//win and lose considtions
//15s = 639
//3 mins = 7680
int currentTime;
int gameoverTime = 639;
int gameCount[] = {0,0,0};
int gameSum;
String incomingText = "";

void setup() 
{
  currentTime = 0;
  pinMode(trigPin, OUTPUT);   //the trigger pin will output pulses of electricity
  pinMode(echoPin, INPUT);    //the echo pin will measure the duration of pulses coming back from the distance sensor
  pinMode(irPin1, OUTPUT);   
  pinMode(ePin1, INPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);

 // set up the LCD's number of columns and rows:
 lcd.begin(16, 2);
 // Print a message to the LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.println("  game start  ");

  pinMode(blueLed, OUTPUT);  //led1 is an output  
  pinMode(redLed, OUTPUT);  //led3 is an output
  pinMode(tiltOut, OUTPUT);
  pinMode(tiltIn, INPUT);
  pinMode(led1, OUTPUT);  //led1 is an output
  pinMode(led2, OUTPUT);  //led2 is an output  
  pinMode(led3, OUTPUT);  //led3 is an output
  pinMode(led4, OUTPUT);  //led4 is an outut
  pinMode(led5, OUTPUT);  //led5 is an outut
}
  
void loop() {
 mainMethod();
}

void mainMethod(){
   while(currentTime < gameoverTime){
    gameSum = arraySum(gameCount);
    if(gameSum == 3){
      Serial.println("WE HAVE A WINNER");
      break;
    }

     incomingText = Serial1.readString();
     
    if(incomingText.indexOf("0")>=0){
      inputFromDB = 0;
    }else if(incomingText.indexOf("1")>=0){
      inputFromDB = 1;
    }else if(incomingText.indexOf("2")>=0){
      inputFromDB = 2;
    }else if(incomingText.indexOf("3")>=0){
      inputFromDB = 3;
    }else if(incomingText.indexOf("4")>=0){
      inputFromDB = 4;
    }else if(incomingText.indexOf("5")>=0){
      inputFromDB = 5;
    }else{
      inputFromDB = 5;
    }

      switch (inputFromDB) {
        case 0:
          printStates(1);
          break;
        case 1:
          printStates(2);
          break;
        case 2:
          printStates(3);
          break;
        default:
          Serial.println("OP. B");
          break;
      }
    Serial.println();
    Serial.print("Current Time: ");
    Serial.println(currentTime); 
    currentTime++;
    //
  }

  //LCD---> GAMEOVER
  Serial.println("Game Over");
  delay(1000000000);
}

void ultrasonicSensor() {
  distance = getDistances();
    if (distance <= 5) 
  {                       //if the object is close
      rightMotor(-200); //max 255
  } 
  else if (5 < distance && distance <= 10) 
  {                       //if the object is a medium distance
      rightMotor(-100);
  }
  else if (10 < distance && distance <= 15) 
  {                       
      rightMotor(-50);
  }
  else 
  {                       //if the object is far away
      rightMotor(0);
  }
  }

void tiltSwitch() {
  digitalWrite(tiltOut,HIGH);
  int sensorValue = analogRead(tiltIn);
  if (sensorValue <= 1023 && sensorValue > 900)
  {
  digitalWrite(blueLed,HIGH);
  digitalWrite(redLed,LOW);
  }
   if (sensorValue <= 900)
  {
  digitalWrite(blueLed,LOW);
  digitalWrite(redLed,HIGH);
  delay(100);
  }
  }

void distanceSensor() {
    distance = getDistance();
    if (distance <= 9)
    {
    digitalWrite(led1,full);
    digitalWrite(led2,off);
    digitalWrite(led3,off);
    digitalWrite(led4,off);
    digitalWrite(led5,off);
    delay(200); 
    }
    else if (9 < distance && distance <= 14)
    {
    digitalWrite(led1,full);
    digitalWrite(led2,full);
    digitalWrite(led3,off);
    digitalWrite(led4,off);
    digitalWrite(led5,off);
    delay(200);
    }
    else if (14 < distance && distance <= 19) 
    {
    digitalWrite(led1,full);
    digitalWrite(led2,full);
    digitalWrite(led3,full);
    digitalWrite(led4,off);
    digitalWrite(led5,off); 
    delay(200);
    }
    else if (19 < distance && distance <= 24) 
    {
    digitalWrite(led1,full);
    digitalWrite(led2,full);
    digitalWrite(led3,full);
    digitalWrite(led4,full);
    digitalWrite(led5,off);
    delay(200);
    }
    else if(distance > 24)
    {
    digitalWrite(led1,full);
    digitalWrite(led2,full);
    digitalWrite(led3,full);
    digitalWrite(led4,full);
    digitalWrite(led5,full);
    delay(200);
    }
  }
  
void printStates(int i){
  Serial.println(i);
}

int arraySum(int arr[]){
  int sum = 0;
  for(int i = 0; i <= sizeof(arr);i++){
    sum = sum + arr[i];
  }
  return sum;
}

void rightMotor(int motorSpeed)                       //function for driving the right motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(AIN1, HIGH);                         //set pin 1 to high
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMA, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}

float getDistance()
{
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  echoTime = pulseIn(echoPin, HIGH);      //use the pulsein command to see how long it takes for the pulse to bounce back to the sensor
  calculatedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)
  return calculatedDistance;              //send back the distance that was calculated
}

float getDistances()
{
  float irTime;  
  float cDistance;
  digitalWrite(irPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(irPin1, LOW);
  irTime = pulseIn(ePin1, HIGH);
  cDistance = irTime / 148.0;
  return cDistance;
}
