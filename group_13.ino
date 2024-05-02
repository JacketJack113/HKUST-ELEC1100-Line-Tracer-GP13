/*
  ELEC1100 Your Lab#06 & Project Template
  To program the car tracking the white line on a dark mat

  Group No. (number of your project box):  13
  Group Member 1 (name & SID): Pun Chun Cheung 21052680
  Group Member 2 (name & SID): Poon Wing Yin 21053531
  
*/

// assign meaningful names to those pins that will be used

const int pinL_Sensor = A4;      //pin A5: left sensor 
const int pinB_Sensor = A0;      //pin A4: bumper sensor
const int pinR_Sensor = A3;      //pin A3: right sensor 
const int pinL_Far_Sensor = A5;  // far left sensor
const int pinR_Far_Sensor = A2;  // far right sensor

const int pinL_PWM = 9;          //pin D9: left motor speed
const int pinL_DIR = 10;         //pin D10: left motor direction

const int pinR_PWM = 11;         //pin D11: right motor speed
const int pinR_DIR = 12;         //pin D12: right motor direction

//define variables to be used in script

int bumperSensor = 1;  // not sensing white
int leftSensor = 1;    // not sensing white
int rightSensor = 1;   // not sensing white
int left_Far_Sensor = 1;
int right_Far_Sensor = 1;

int countBumper = 0;   // bumper sensor not triggered yet
int countT = 1; // on the first T-junction at the beginning
bool in_C = false; // for task7

const int global_spd = 195;
const int L_Motor_spd = 200;
const int backward_time = 800;
// delay for different turning angles
const int delay_90 = 320;
const int delay_180 = 425;
// const int delay_360 = 850;
const int forward_time = 50; // time going forward after turning


// declare all functions
void forward(); // go forward
void trace_line();  // tracing the line
void turn_left(int delay_time); // turnings at L,T-junctions
void turn_right(int delay_time);
void self_turn(int delay_time);
void circumference(); // circulating clockwise for the final C
void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();
void task8();

// the setup function runs once when you press reset or power the board

void setup ()
{
  // define pins as input and output
  pinMode(pinB_Sensor, INPUT);
  pinMode(pinL_Sensor, INPUT);
  pinMode(pinR_Sensor, INPUT);
  pinMode(pinL_Far_Sensor, INPUT);
  pinMode(pinR_Far_Sensor, INPUT);
  
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

void loop(){
  bumperSensor = digitalRead(pinB_Sensor);
  leftSensor = digitalRead(pinL_Sensor);
  rightSensor = digitalRead(pinR_Sensor);
  left_Far_Sensor = digitalRead(pinL_Far_Sensor);
  right_Far_Sensor = digitalRead(pinR_Far_Sensor);
  bumperSensor == 1;

  if (countBumper == 0 || countBumper == 1)
    switch(countT){
      case 1: task1(); break;
      case 2: task2(); break;
      case 3: task3(); break;
      case 4: task4(); break;
      case 5: task5(); break;
      case 6: task6(); break;
      case 7: task7(); break;
    }
  else if (countBumper == 2)
    task8();
}

void forward(){
  analogWrite(pinL_PWM, L_Motor_spd);
  analogWrite(pinR_PWM, global_spd);
  digitalWrite(pinL_DIR, HIGH);
  digitalWrite(pinR_DIR, HIGH); 
}

void trace_line(){  // tracing the line
  if ((leftSensor == HIGH )&&(rightSensor == HIGH)) {  // black, black (or white, white) -> go straight
      forward(); 
   }else if ( !leftSensor ) { // white, black -> too right
      analogWrite(pinL_PWM, global_spd);
      analogWrite(pinR_PWM, global_spd / 1.7);
      digitalWrite(pinL_DIR, HIGH);
      digitalWrite(pinR_DIR, HIGH);
   }else if ( !rightSensor ) { // black, white -> too left
      analogWrite(pinL_PWM, L_Motor_spd / 1.7);
      analogWrite(pinR_PWM, global_spd);
      digitalWrite(pinL_DIR, HIGH);
      digitalWrite(pinR_DIR, HIGH);
  }
}

// turnings at L,T-junctions
//void turn_left(int delay_time){
////  forward();
////  delay(50);
//  analogWrite(pinL_PWM, L_Motor_spd);
//  analogWrite(pinR_PWM, global_spd);
//  digitalWrite(pinL_DIR, LOW);
//  digitalWrite(pinR_DIR, LOW);
//  delay(10);
//  analogWrite(pinL_PWM, L_Motor_spd*0.75);
//  analogWrite(pinR_PWM, global_spd);
//  digitalWrite(pinL_DIR, LOW);
//  digitalWrite(pinR_DIR, HIGH);
//  delay(delay_time-50);
//  // prevent sensing junctions as the car go back a little bit after turning
////  forward();
////  delay(forward_time);
//}
//
//void turn_right(int delay_time){
////  forward();
////  delay(50);
//  analogWrite(pinL_PWM, L_Motor_spd);
//  analogWrite(pinR_PWM, global_spd);
//  digitalWrite(pinL_DIR, LOW);
//  digitalWrite(pinR_DIR, LOW);
//  delay(10);
//  analogWrite(pinL_PWM, L_Motor_spd);
//  analogWrite(pinR_PWM, global_spd*0.75);
//  digitalWrite(pinL_DIR, HIGH);
//  digitalWrite(pinR_DIR, LOW);
//  delay(delay_time);
//  // prevent sensing junctions as the car go back a little bit after turning
////  forward();
////  delay(forward_time);
//}

void turn_left(int delay_time){
  forward();
//  delay(50);
//  analogWrite(pinL_PWM, L_Motor_spd);
//  analogWrite(pinR_PWM, global_spd);
//  digitalWrite(pinL_DIR, LOW);
//  digitalWrite(pinR_DIR, LOW);
//  delay(10);
  analogWrite(pinL_PWM, 165);
  analogWrite(pinR_PWM, 235);
  digitalWrite(pinL_DIR, LOW);
  digitalWrite(pinR_DIR, HIGH);
  delay(delay_time);
  analogWrite(pinL_PWM, 165);
  analogWrite(pinR_PWM, 235);
  digitalWrite(pinL_DIR, HIGH);
  digitalWrite(pinR_DIR, LOW);
  delay(15);
  forward();
//  for (int i = 0; i < 260; ++i){
//    leftSensor = digitalRead(pinL_Sensor);
//    rightSensor = digitalRead(pinR_Sensor);
//    trace_line();
//    delay(1);
//  }
}

void turn_right(int delay_time){
  forward();
//  delay(50);
//  analogWrite(pinL_PWM, L_Motor_spd);
//  analogWrite(pinR_PWM, global_spd);
//  digitalWrite(pinL_DIR, LOW);
//  digitalWrite(pinR_DIR, LOW);
//  delay(10);
  analogWrite(pinL_PWM, 210);
  analogWrite(pinR_PWM, 170);
  digitalWrite(pinL_DIR, HIGH);
  digitalWrite(pinR_DIR, LOW);
  delay(delay_time);
  analogWrite(pinL_PWM, 210);
  analogWrite(pinR_PWM, 170);
  digitalWrite(pinL_DIR, LOW);
  digitalWrite(pinR_DIR, HIGH);
  delay(15);
  forward();
//  for (int i = 0; i < 260; ++i){
//    leftSensor = digitalRead(pinL_Sensor);
//    rightSensor = digitalRead(pinR_Sensor);
//    trace_line();
//    delay(1);
//  }
}
void self_turn(int delay_time){
  analogWrite(pinL_PWM, 255);
  analogWrite(pinR_PWM, 195);
  digitalWrite(pinL_DIR, HIGH);
  digitalWrite(pinR_DIR, LOW);
  delay(delay_time);
  analogWrite(pinL_PWM, 255);
  analogWrite(pinR_PWM, 195);
  digitalWrite(pinL_DIR, LOW);
  digitalWrite(pinR_DIR, HIGH);
  delay(25);
}

// circumference not tested
void circumference(){ // circulate clockwise for the final C
  if (leftSensor && rightSensor){ // black black
    analogWrite(pinL_PWM, L_Motor_spd);
    analogWrite(pinR_PWM, global_spd / 1.5);
    digitalWrite(pinL_DIR, HIGH);
    digitalWrite(pinR_DIR, HIGH); 
  }else if (!leftSensor && rightSensor){ // white, black
    analogWrite(pinL_PWM, L_Motor_spd);
    analogWrite(pinR_PWM, global_spd);
    digitalWrite(pinL_DIR, HIGH);
    digitalWrite(pinR_DIR, HIGH);
  }else if (leftSensor && !rightSensor){ // black, white
    analogWrite(pinL_PWM, L_Motor_spd);
    analogWrite(pinR_PWM, global_spd / 2);
    digitalWrite(pinL_DIR, HIGH);
    digitalWrite(pinR_DIR, HIGH);
  }
}

void task1(){
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
  // if encounter the 2nd T-junction
  else if ( !left_Far_Sensor && !right_Far_Sensor ) {
    turn_right(delay_90);
    forward();
    delay(250);
    countT++;
  }else
    trace_line();
}

void task2(){
  // if (!left_Far_Sensor && !right_Far_Sensor )  {// turn 360 T
  //   countT++;
  //   self_turn(delay_180*2);
  //   for (int i = 0; i < 350; ++i){
  //     leftSensor = digitalRead(pinL_Sensor);
  //     rightSensor = digitalRead(pinR_Sensor);
  //     trace_line();
  //     delay(1);
  //   }
  // } // L-junctions
  // else if (!left_Far_Sensor && !leftSensor){
  //   turn_left(delay_90);
  // } else if (!right_Far_Sensor && !rightSensor){
  //   turn_right(delay_90);
  // } else {          // straight line
  //   trace_line();
  // }
  while ((left_Far_Sensor == HIGH)&&(right_Far_Sensor == HIGH)) {
    if (!left_Far_Sensor) {
      turn_left(delay_90);
    } else if (!right_Far_Sensor) {
      turn_right(delay_90);
    } else {
      trace_line();
    }
    bumperSensor = digitalRead(pinB_Sensor);
    leftSensor = digitalRead(pinL_Sensor);
    rightSensor = digitalRead(pinR_Sensor);
    left_Far_Sensor = digitalRead(pinL_Far_Sensor);
    right_Far_Sensor = digitalRead(pinR_Far_Sensor);
  }
  countT++;
  self_turn(delay_180*2);
  trace_line();
  delay(200);
}

void task3(){
  if ( !left_Far_Sensor && !right_Far_Sensor ) {  // T-junction
    countT++;
    // stop for 1 second
    analogWrite(pinL_PWM, L_Motor_spd);
    analogWrite(pinR_PWM, global_spd);
    digitalWrite(pinL_DIR, LOW);
    digitalWrite(pinR_DIR, LOW);
    delay(15);
    digitalWrite(pinL_DIR, 0);
    digitalWrite(pinR_DIR, 0);
    delay(975);
    // prevent detect same T-junction at next task
    forward();
    delay(300);
  } else
    trace_line();
}

void task4(){
  if ( !left_Far_Sensor && !right_Far_Sensor ) {  // T-junction
    countT++;
    turn_left(delay_90);
  }else
    trace_line();
}

void task5(){
  if ( !left_Far_Sensor && !right_Far_Sensor ) {  // T-junction
    countT++;
    // 180 degree turn
    self_turn(delay_180);
  }else if (!right_Far_Sensor && !rightSensor){  // only turn right, ignore left junction
    turn_right(delay_90);
  }
  else{
    trace_line();
//    delay(delay_90);
  }
}

void task6(){
  if ( !left_Far_Sensor && !right_Far_Sensor ) {  // T-junction
    countT++;
    turn_left(delay_90);
  }else
    trace_line();
}

void task7(){
  if (!bumperSensor) {  // last T-junction
    countT++;
    countBumper++;
  }else if (!in_C && !right_Far_Sensor && !rightSensor){  // into the C
    turn_right(delay_90);
    in_C = true;
  }else if (in_C)
    circumference();
  else
    trace_line();
}

void task8(){
  // going backward for around 30 cm
  analogWrite(pinL_PWM, L_Motor_spd);
  analogWrite(pinR_PWM, global_spd);
  digitalWrite(pinL_DIR, LOW);
  digitalWrite(pinR_DIR, LOW);
  delay(backward_time); // need to calibrate

  while(true){  // end of project, stop the car
    analogWrite(pinL_PWM, 0);
    analogWrite(pinR_PWM, 0);
  }
}
