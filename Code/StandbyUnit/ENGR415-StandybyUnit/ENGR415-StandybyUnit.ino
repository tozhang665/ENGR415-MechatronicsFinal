#include <Servo.h>

int xPIN = A8;
int yPIN = A10;

int topPos = 78;
int botPos = 122;

int topMax = 0;//40;//50
int topMin = 180;//104;//85
int botMax = 0; //56;//114
int botMin = 180; //150;//141

//point 1,1 = top = 56, bot = 86
//point 1,2 = top = 34, bot = 98
//point 2,1 = top = 78, bot = 122
//point 2,2 = top = NA
//point 3,1 = top = 103, bot = 146
//point 3,2 = top = 101, bot = 168

int xValue = 0;
int yValue = 0;

int topArray[] = {49,33,67,67,101,103};
int botArray[] = {96,102,128,128,153,171};

int xPOS = 0;
int yPOS = 0;


int pin1 = A0;
int pin2 = A1;
int pin3 = A2;
int pin4 = A3;
int pin5 = A4;
int pin6 = A5;

int toggle = 0;

int pin1val = 0;
int pin2val = 0;
int pin3val = 0;
int pin4val = 0;
int pin5val = 0;
int pin6val = 0;


int irArray[6];


Servo myservoTOP;  // create servo object to control a servo
Servo myservoBOT;
// twelve servo objects can be created on most boards

int topPOS = 0;    // variable to store the servo position
int botPOS = 0;

int looper = 0;

int indexArray = 3;

String statement;

String ESPData;

int i = 3;

String acceptUpWord = "UpA";
String acceptDownWord = "DownA";


void setup() {
  myservoBOT.attach(9);  // attaches the servo on pin 9 to the servo object
  myservoTOP.attach(6);
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);

}

void loop() {
  //ESPData= Serial1.readString();
  //Serial.print(ESPData);
  //myservoBOT.write(topArray[i]);
  //delay(1000);
  //myservoTOP.write(topArray[i]);
  
  newMethod();
}
void oldMethod(){
  xValue = analogRead(xPIN);
  yValue = analogRead(yPIN);
  //Serial.print("X value : ");
  //Serial.println(xValue);
  //Serial.print("Y value: ");
  //Serial.println(yValue);
  //Serial.println("");

  if(xValue > 600){
    topPos = topPos + 1;
    if(topPos > topMin){
      topPos = topMin;
    }
  }
  if(xValue < 50){
    topPos = topPos - 1;
    if(topPos < topMax){
      topPos = topMax;
    }
  }
  if(yValue > 600){
    botPos = botPos + 1;
    if(botPos > botMin){
      botPos = botMin;
    }
  }
  if(yValue < 50){
    botPos = botPos - 1;
    if(botPos < botMax){
      botPos = botMax;
    }
  }
  myservoTOP.write(topPos);
  myservoBOT.write(botPos);
  Serial.print("topPOS: ");
  Serial.println(topPos);
  Serial.print("botPOS: ");
  Serial.println(botPos);
  Serial.println();
  delay(15);

  pin1val = analogRead(pin1);
  pin2val = analogRead(pin2);
  pin3val = analogRead(pin3);
  pin4val = analogRead(pin4);
  pin5val = analogRead(pin5);
  pin6val = analogRead(pin6);

  if(pin1val > 1){
    toggle = 1;
  }else if(pin2val > 1){
    toggle = 2;
  }else if(pin3val > 1){
    toggle = 3;
  }else if(pin4val > 1){
    toggle = 4;
  }else if(pin5val > 1){
    toggle = 5;
  }else if(pin6val > 1){
    toggle = 6;
  }
  looper = looper + 1;

  if(looper == 250){
  Serial.print("val1: ");
  Serial.println(pin1val);
  Serial.print("val2: ");
  Serial.println(pin2val);
  Serial.print("val3: ");
  Serial.println(pin3val);
  Serial.print("val4: ");
  Serial.println(pin4val);
  Serial.print("val5: ");
  Serial.println(pin5val);
  Serial.print("val6: ");
  Serial.println(pin6val);
  Serial.print("Toggle: ");
  Serial.println(toggle);
  looper = 0;
  }
  toggle = 0;

}



void newMethod(){
  xValue = analogRead(xPIN);
  ESPData= Serial1.readString();
  //Serial.print(ESPData);
  
 //if(xValue > 600){
    //indexArray = indexArray + 1;
    //if(indexArray > 5){
    //  indexArray = 5;
    //}
  //}
  //if(xValue < 50){
    //indexArray = indexArray - 1;
    //if(indexArray < 0){
      //indexArray = 0;
    //}
  //}


  if(analogRead(A13) > 500){
    acceptUpWord = "UpA";
    acceptDownWord = "DownA";    
  }else{
  acceptUpWord = "UpB";
  acceptDownWord = "DownB"; 
  }
  if(ESPData.indexOf(acceptUpWord)>=0){
    indexArray = indexArray + 1;
    if(indexArray > 5){
      indexArray = 5;
    }
  }
  if(ESPData.indexOf(acceptDownWord)>=0){
    indexArray = indexArray - 1;
    if(indexArray < 0){
      indexArray = 0;
    }
  }

  
  
  topPOS = topArray[indexArray];
  botPOS = botArray[indexArray];

   
  myservoTOP.write(topPOS);
  myservoBOT.write(botPOS);
  //Serial.print("indexArray: ");
  //Serial.println(indexArray);
  //Serial.print("topPOS: ");
  //Serial.println(topPOS);
  //Serial.print("botPOS: ");
  //Serial.println(botPOS);
  //Serial.println();
  
  irArray[0] = analogRead(pin1);
  irArray[1] = analogRead(pin2);
  irArray[2] = analogRead(pin3);
  irArray[3] = analogRead(pin4);
  irArray[4] = analogRead(pin5);
  irArray[5] = analogRead(pin6);


  //toggle = biggestArray(irArray);
  String toggleS = (String)indexArray;
  //Serial.print("Toggle: ");
  //Serial.print("index Array = ");
  //Serial.println(indexArray);
  //Serial.print("top pos");
  //Serial.println(topPOS);
  //Serial.print("bot pos");
  //Serial.println(botPOS);
  Serial.println(toggleS);
  toggle = 0;
  delay(1000);
}



int biggestArray(int a[]){
  int largest = a[0];
  int i;
  int pos;
  for(i = 1; i < 5; i++){
    if(a[i] > largest){
      pos = i;
    }
  }
  return pos + 1;
}

void reader(){
  if(Serial2.available()){      //Checks if there is data in UART1
    ESPData= Serial2.readString();
    Serial.print(ESPData);
  } 
}
