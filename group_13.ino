/*
  ELEC1100 Your Lab#06 & Project Template

  To program the car tracking the white line on a dark mat

  Group No. (number of your project box):  13
  Group Member 1 (name & SID): Pun Chun Cheung 21052680
  Group Member 2 (name & SID):
  
*/

// assign meaningful names to those pins that will be used

const int pinL_Sensor = A5;      //pin A5: left sensor 
const int pinB_Sensor = A4;      //pin A4: bumper sensor
const int pinR_Sensor = A3;      //pin A3: right sensor 
// not yet install
const int pinL_Far_Sensor = A2;  // far left sensor
const int pinR_Far_Sensor = A1;  // far right sensor

const int pinL_PWM = 9;          //pin D9: left motor speed
const int pinL_DIR = 10;         //pin D10: left motor direction

const int pinR_PWM = 11;         //pin D11: right motor speed
const int pinR_DIR = 12;         //pin D12: right motor direction

//define variables to be used in script

int bumperSensor = 1;  // not sensing white
int leftSensor = 1;    // not sensing white
int rightSensor = 1;   // not sensing white
int leftFarSensor = 1;
int rightFarSensor = 1;

int countBumper = 0;   // bumper sensor not triggered yet
int countT = 1; // on the first T-junction at the beginning
bool in_C = false // for task7

const int global_spd = 100;
const int L_Motor_spd = global_spd+15;
const int backward_time = ?;

// declare all functions
void forward(void); // go forward
void trace_line(void);  // tracing the line
void turn_left(void); // turnings at L,T-junctions
void turn_right(void);
// not yet implement
void circumference(void); // circulation clockwise for the final C
void task1(void);
void task2(void);
void task3(void);
void task4(void);
void task5(void);
void task6(void);
void task7(void);
void task8(void);

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
  leftFarSensor = digitalRead(pinL_Far_Sensor);
  rightFarSensor = digitalRead(pinR_Far_Sensor);

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

void trace_line(void){  // tracing the line
  if ( leftSensor && rightSensor ) {  // black, black -> go straight
      forward(); 
   }else if ( !leftSensor && rightSensor ) { // white, black -> too right
      analogWrite(pinL_PWM, L_Motor_spd);
      analogWrite(pinR_PWM, global_spd*2);
      digitalWrite(pinL_DIR, HIGH);
      digitalWrite(pinR_DIR, LOW);  
   }else if ( leftSensor && !rightSensor ) { // black, white -> too left
      analogWrite(pinL_PWM, L_Motor_spd);
      analogWrite(pinR_PWM, 0);
      digitalWrite(pinL_DIR, HIGH);
      digitalWrite(pinR_DIR, HIGH);  
  }
}

void turn_left(void){ // turnings at L,T-junctions
  analogWrite(pinL_PWM, L_Motor_spd*2);
  analogWrite(pinR_PWM, global_spd*2);
  digitalWrite(pinL_DIR, LOW);
  digitalWrite(pinR_DIR, HIGH);
}

void turn_right(void){
  analogWrite(pinL_PWM, L_Motor_spd*2);
  analogWrite(pinR_PWM, global_spd*2);
  digitalWrite(pinL_DIR, HIGH);
  digitalWrite(pinR_DIR, LOW);
}

void circumference(void); // circulate clockwise for the final C

void task1(void){
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
    turn_right();
    countT++;
  }else
    trace_line();
}

void task2(void){
  if ( !left_Far_Sensor && !right_Far_Sensor ) {  // T-junction
    countT++;
    // 360 degree turn

    // prevent detect the same T-junction at next task
    forward();
    delay(100);
  } // L-junctions
  else if (!left_Far_Sensor && right_Far_Sensor)
    turn_left();
  else if (left_Far_Sensor && !right_Far_Sensor)
    turn_right();
  else  // straight line
    trace_line();
}

void task3(void){
  if ( !left_Far_Sensor && !right_Far_Sensor ) {  // T-junction
    countT++;
    // stop for 1 second
    analogWrite(pinL_PWM, 0);
    analogWrite(pinR_PWM, 0);
    delay(1000);
    // prevent detect same T-junction at next task
    forward();
    delay(100);
  }else
    trace_line();
}

void task4(void){
  if ( !left_Far_Sensor && !right_Far_Sensor ) {  // T-junction
    countT++;
    turn_left();
  }else
    trace_line();
}

void task5(void){
  if ( !left_Far_Sensor && !right_Far_Sensor ) {  // T-junction
    countT++;
    // 180 degree turn

    forward();
    delay(100);
  }else if (!right_Far_Sensor)  // only turn right, ignore left junction
    turn_right();
  else
    trace_line();
}

void task6(void){
  if ( !left_Far_Sensor && !right_Far_Sensor ) {  // T-junction
    countT++;
    turn_left();
  }else
    trace_line();
}

void task7(void){
  if (!bumper_sensor) {  // last T-junction
    countT++;
    countBumper++;
  }else if (!right_Far_Sensor){  // into the C
    turn_right();
    in_C = true;
  }else if (in_C)
    circumference();
  else
    trace_line();
}

void task8(void){
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
