#include <DHT.h>
#include <LiquidCrystal.h>
#define DHTPIN 46 
#define GREEN 48
#define RED 50
#define BLUE 52
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

// FSR
#define fsrpin A0
#define led1 42
#define led2 40
#define led3 38
#define led4 36
#define led5 34
int fsrreading;

// PIR
#define pir 7
#define motor 8 
 int state = 2;

//LCD
LiquidCrystal lcd (2, 3, 28, 26, 24, 22);


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
void setup() {
  // put your setup code here, to run once:
        Serial.begin(9600); 
          Serial.println("game starts");
          pinMode(RED, OUTPUT);
          pinMode(GREEN, OUTPUT);
          pinMode(BLUE, OUTPUT);
          dht.begin();
        
        // FSR
          pinMode(led1, OUTPUT);
          pinMode(led2, OUTPUT);
          pinMode(led3, OUTPUT);
          pinMode(led4, OUTPUT);
          pinMode(led5, OUTPUT);
        
        // PIR
          pinMode(pir, INPUT);
          pinMode(motor, OUTPUT);
        // LCD
        // set up the LCD's number of columns and rows:
        lcd.begin(16, 2);
        currentTime = 0;
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
          //humiditySensor();
          printStates(1);
          break;
        case 1:
          //FSRSensor();
          printStates(2);
          break;
        case 2:
          //PIRSensor()
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

void humiditySensor(){

        gameCount[0] = 1;
         // DHT11
         
        float h = dht.readHumidity();
        // Check if any reads failed and exit early (to try again).
        if (isnan(h) ) {
          Serial.println("Failed to read from DHT sensor!");
          return;
        }
        float hi = dht.computeHeatIndex( h);
        delay(200);
      
        if ((h>57) && (h<60.2))
        {
          digitalWrite (GREEN, HIGH);
          digitalWrite (RED, LOW);
          digitalWrite (BLUE, LOW);
          sensor = sensor +1;
          Serial.println(sensor);
          lcd.setCursor(0,0);
          lcd.print(sensor);
         
        }
        
        if ((h>60) && (h<80.2))
        {
          digitalWrite (GREEN, LOW);
          digitalWrite (RED, HIGH);
          digitalWrite (BLUE, LOW);
        }
   if ((h>80) && (h<100)){
      digitalWrite (GREEN, LOW);
      digitalWrite (RED, LOW);
      digitalWrite (BLUE, HIGH);
   }
   if ((h>0) && (h<50)){ 
      digitalWrite (GREEN, LOW);
      digitalWrite (RED, LOW);
      digitalWrite (BLUE, LOW);
   }
}
void FSRSensor(){
       gameCount[1] = 1;
        //FSR  
        fsrreading = analogRead(fsrpin);
        if (fsrreading > 200) {
          digitalWrite(led1, HIGH);
      
        }
        else digitalWrite(led1, LOW);
        
        if (fsrreading > 550) {
          digitalWrite(led2, HIGH);
        }
        else digitalWrite(led2, LOW);
        if (fsrreading > 650) {
          digitalWrite(led3, HIGH);
        }
        else digitalWrite(led3, LOW);
        if (fsrreading > 800) {
          digitalWrite(led4, HIGH);
        }
        else digitalWrite(led4, LOW);
        if (fsrreading > 900) {
          digitalWrite(led5, HIGH);
              sensor = sensor +1;
          Serial.println(sensor);
          lcd.setCursor(0,0);
          lcd.print(sensor);
        }
        else digitalWrite(led5, LOW);
      
}

void PIRSensor(){
    gameCount[2] = 1;
    state = digitalRead(pir);
    if (state == HIGH)
     {
           sensor = 1;
           Serial.println(sensor);
           lcd.setCursor(0,0);
           lcd.print(sensor);
           digitalWrite(motor, HIGH);    
          }
          else{
            digitalWrite(motor, LOW);
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
