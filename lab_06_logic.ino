/*
  ELEC1100 Your Lab#06 & Project Template

  To program the car tracking the white line on a dark mat

  Group No. (number of your project box):  13
  Group Member 1 (name & SID):
  Group Member 2 (name & SID):
  
*/

// assign meaningful names to those pins that will be used

const int pinL_Sensor = A4;      //pin A5: left sensor 
const int pinB_Sensor = A0;      //pin A4: bumper sensor
const int pinR_Sensor = A3;      //pin A3: right sensor
const int pinL2_Sensor = A5;
const int pinR2_Sensor = A2;

const int pinL_PWM = 9;          //pin D9: left motor speed
const int pinL_DIR = 10;         //pin D10: left motor direction

const int pinR_PWM = 11;         //pin D11: right motor speed
const int pinR_DIR = 12;         //pin D12: right motor direction

//define variables to be used in script

int bumperSensor = 1;  // not sensing white
int leftSensor = 1;    // not sensing white
int rightSensor = 1;   // not sensing white
int adjustleftsensor = 1;
int adjustrightsensor = 1;
  

int countBumper = 0;   // bumper sensor not triggered yet

const int global_spd = 100;
const int L_Motor_spd = global_spd+15;


// the setup function runs once when you press reset or power the board

void setup ()
{
  // define pins as input and output
  pinMode(pinB_Sensor, INPUT);
  pinMode(pinL_Sensor, INPUT);
  pinMode(pinR_Sensor, INPUT);
  pinMode(pinL2_Sensor, INPUT);
  pinMode(pinR2_Sensor, INPUT);
  pinMode(pinL_DIR, OUTPUT);
  pinMode(pinR_DIR, OUTPUT);
  
  pinMode(pinL_PWM, OUTPUT);
  pinMode(pinR_PWM, OUTPUT);
  
  // initialize output pins
  digitalWrite(pinL_DIR, HIGH);   //forward direction    
  digitalWrite(pinR_DIR, HIGH);   //forward direction
  analogWrite(pinL_PWM, 0);       //stop at the start position 
  analogWrite(pinR_PWM, 0);       //stop at the start position 
}

// the loop function runs over and over again forever

void loop() {

  // Arduino is reading the sensor measurements
  bumperSensor = digitalRead(pinB_Sensor);
  leftSensor = digitalRead(pinL2_Sensor);
  rightSensor = digitalRead(pinR2_Sensor);
  adjustleftsensor = digitalRead(pinL_Sensor);
  adjustrightsensor = digitalRead(pinR_Sensor);
  
  // car stops at the start position when bumper sensor no trigger
  if ( bumperSensor && countBumper == 0 ) {
    analogWrite(pinL_PWM, 0);
    analogWrite(pinR_PWM, 0);
  }

  // bumper sensor is triggered at the start position for the 1st time
  else if ( !bumperSensor && countBumper == 0) {
    analogWrite(pinL_PWM, L_Motor_spd);
    analogWrite(pinR_PWM, global_spd);
    countBumper = countBumper + 1;
    delay(350);     //to let the car leave the start position with no miscount
  }
  
  // car is tracking on the white line
  else if ( bumperSensor && countBumper == 1) 
  { 
    if ( !leftSensor && !rightSensor ) {  // white, white -> turn right
        analogWrite(pinL_PWM, L_Motor_spd*2);
        analogWrite(pinR_PWM, global_spd*2);
        digitalWrite(pinL_DIR, HIGH);
        digitalWrite(pinR_DIR, LOW); 
      }
    
    if ( !leftSensor && rightSensor ) { // white, black -> too right
        analogWrite(pinL_PWM, L_Motor_spd);
        analogWrite(pinR_PWM, global_spd*2);
        digitalWrite(pinL_DIR, HIGH);
        digitalWrite(pinR_DIR, LOW);  
      }
    
    if ( leftSensor && !rightSensor ) { // black, white -> too left
        analogWrite(pinL_PWM, L_Motor_spd);
        analogWrite(pinR_PWM, 0);
        digitalWrite(pinL_DIR, HIGH);
        digitalWrite(pinR_DIR, HIGH);  
      }
    
    if ( leftSensor && rightSensor ) {  // black, black -> go straight
        analogWrite(pinL_PWM, L_Motor_spd);
        analogWrite(pinR_PWM, global_spd);
        digitalWrite(pinL_DIR, HIGH);
        digitalWrite(pinR_DIR, HIGH);  
      }
  }
}
