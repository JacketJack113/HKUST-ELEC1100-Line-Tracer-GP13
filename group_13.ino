/*
  ELEC1100 Your Lab#06 & Project Template

  To program the car tracking the white line on a dark mat

  Group No. (number of your project box):  13
  Group Member 1 (name & SID): Pun Chun Cheung 21052680
  Group Member 2 (name & SID): Poon Wing Yin 21053531
  
*/

/*  metadata
distance between sensors (mm): 28 19 (tilted 1.847 degree) 21 (tilted -1.847 degree) 18.5 22
distance between sensors and ground (mm): 35
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
int L_junct = 0;
bool in_C = false; // for task7

const int global_spd = 195;  // base forward speed
const int trace_spd = 120;  // base speed for tracing line
const int backward_time = 500;
// delay for different turning angles
const int delay_90 = 320;
const int delay_180 = 575;
const int delay_360 = 1000;

// declare all functions
void forward(void); // go forward
void trace_line(void);  // tracing the line
// turnings at L,T-junctions
void turn_left(int delay_time);
void turn_right(int delay_time);
void self_turn(int delay_time);
// splitting tasks by T-junctions
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
  left_Far_Sensor = digitalRead(pinL_Far_Sensor);
  right_Far_Sensor = digitalRead(pinR_Far_Sensor);

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
  analogWrite(pinL_PWM, global_spd+20);
  analogWrite(pinR_PWM, global_spd);
  digitalWrite(pinL_DIR, HIGH);
  digitalWrite(pinR_DIR, HIGH); 
}

// min() for calibration: sometimes larger than 255
void trace_line(){  // tracing the line
  if (leftSensor == rightSensor) {  // black, black (or white, white) -> go straight
      forward(); 
   } else if ( !leftSensor ) { // white, black -> too right
      analogWrite(pinL_PWM, trace_spd/1.25);  // trace_spd/1.25
      analogWrite(pinR_PWM, min((trace_spd*1.5),255));  // min((trace_spd*1.5),255))
      digitalWrite(pinL_DIR, LOW);
      digitalWrite(pinR_DIR, HIGH);
   } else if ( !rightSensor ) { // black, white -> too left
      analogWrite(pinL_PWM, min((trace_spd*1.5),255));  // min((trace_spd*1.5),255))
      analogWrite(pinR_PWM, trace_spd/1.25);  // trace_spd/1.25
      digitalWrite(pinL_DIR, HIGH);
      digitalWrite(pinR_DIR, LOW);
  }
}

void turn_left(int delay_time){
  forward();
  analogWrite(pinL_PWM, 165);
  analogWrite(pinR_PWM, 235);
  digitalWrite(pinL_DIR, LOW);
  digitalWrite(pinR_DIR, HIGH);
  delay(delay_time);
  // sharp turn by cancelling inertia
  analogWrite(pinL_PWM, 165);
  analogWrite(pinR_PWM, 235);
  digitalWrite(pinL_DIR, HIGH);
  digitalWrite(pinR_DIR, LOW);
  delay(15);
  forward();
}

void turn_right(int delay_time){
  forward();
  analogWrite(pinL_PWM, 210);
  analogWrite(pinR_PWM, 170);
  digitalWrite(pinL_DIR, HIGH);
  digitalWrite(pinR_DIR, LOW);
  delay(delay_time);
  // sharp turn by cancelling inertia
  analogWrite(pinL_PWM, 210);
  analogWrite(pinR_PWM, 170);
  digitalWrite(pinL_DIR, LOW);
  digitalWrite(pinR_DIR, HIGH);
  delay(15);
  forward();
}

// for 180 and 360
void self_turn(int delay_time){
  analogWrite(pinL_PWM, 255);
  analogWrite(pinR_PWM, 195);
  digitalWrite(pinL_DIR, HIGH);
  digitalWrite(pinR_DIR, LOW);
  delay(delay_time);
  // sharp turn by cancelling inertia
  digitalWrite(pinL_DIR, LOW);
  digitalWrite(pinR_DIR, HIGH);
  analogWrite(pinL_PWM, 255);
  analogWrite(pinR_PWM, 195);
  delay(50);
}

void task1(void){
  // car stops at the start position when bumper sensor no trigger
  if ( bumperSensor && countBumper == 0 ) {
    analogWrite(pinL_PWM, 0);
    analogWrite(pinR_PWM, 0);
  }
  // bumper sensor is triggered at the start position for the 1st time
  else if ( !bumperSensor && countBumper == 0) {
    forward();
    countBumper = countBumper + 1;
    delay(350);     //to let the car leave the start position with no miscount
  }
  // if encounter the 2nd T-junction
  else if ( !left_Far_Sensor && !right_Far_Sensor ) {
    turn_right(delay_90);
    forward();
    delay(240);
    countT++;
  }else
    trace_line();
}

void task2(void){
  if ((!left_Far_Sensor || !right_Far_Sensor) && L_junct >= 7){
    // for detecting T-junctions as only L-junction will probably be detected
    forward();
    delay(55);
    left_Far_Sensor = digitalRead(pinL_Far_Sensor);
    right_Far_Sensor = digitalRead(pinR_Far_Sensor);
  }
  
  if (!left_Far_Sensor && !right_Far_Sensor)  {// turn 360 T
    countT++;
    self_turn(delay_360);
    forward();
    delay(100);
    // trace to right angle and position
    for (int i = 0; i < 150; ++i){
      leftSensor = digitalRead(pinL_Sensor);
      rightSensor = digitalRead(pinR_Sensor);
      trace_line();
      delay(1);
    }
    L_junct = 0;  // reset L-junction count for other task
  } else if (!left_Far_Sensor && !leftSensor){    //L-junction
    turn_left(delay_90);
    L_junct++;
  } else if (!right_Far_Sensor && !rightSensor){
    turn_right(delay_90);
    L_junct++;
  } else {          // straight line
    trace_line();
  }
}

void task3(void){  
  if (!left_Far_Sensor || !right_Far_Sensor){
    // for detecting T-junctions as only L-junction will probably be detected
    forward();
    delay(55);
    left_Far_Sensor = digitalRead(pinL_Far_Sensor);
    right_Far_Sensor = digitalRead(pinR_Far_Sensor);
  }
  if ( !left_Far_Sensor && !right_Far_Sensor ) {  // T-junction
    countT++;
    // stop for 1 second
    // sharp stop by cancelling inertia
    analogWrite(pinL_PWM, global_spd+20);
    analogWrite(pinR_PWM, global_spd);
    digitalWrite(pinL_DIR, LOW);
    digitalWrite(pinR_DIR, LOW);
    delay(25);
    analogWrite(pinL_PWM, 0);
    analogWrite(pinR_PWM, 0);
    delay(975);
    // prevent detect same T-junction at next task
    for (int i = 0; i < 100; ++i){
      leftSensor = digitalRead(pinL_Sensor);
      rightSensor = digitalRead(pinR_Sensor);
      trace_line();
      delay(1);
    }
  } else
    trace_line();
}

void task4(void){
  if (!left_Far_Sensor || !right_Far_Sensor){
    // for detecting T-junctions as only L-junction will probably be detected
    forward();
    delay(25);
    left_Far_Sensor = digitalRead(pinL_Far_Sensor);
    right_Far_Sensor = digitalRead(pinR_Far_Sensor);
  }
  if ( !left_Far_Sensor && !right_Far_Sensor ) {  // T-junction
    countT++;
    turn_left(delay_90);
    forward();
    delay(100);
  } else
    trace_line();
}

void task5(void){
  if ((!left_Far_Sensor || !right_Far_Sensor) && L_junct == 1){
    // for detecting T-junctions as only L-junction will probably be detected
    forward();
    delay(25);
    left_Far_Sensor = digitalRead(pinL_Far_Sensor);
    right_Far_Sensor = digitalRead(pinR_Far_Sensor);
  }
  if ( !left_Far_Sensor && !right_Far_Sensor ) {  // T-junction
    countT++;
    // 180 degree turn
    self_turn(delay_180);
    // prevent detecting same T-junction
    forward();
    delay(50);
    for (int i = 0; i < 250; ++i){
      leftSensor = digitalRead(pinL_Sensor);
      rightSensor = digitalRead(pinR_Sensor);
      trace_line();
      delay(1);
    }
    L_junct = 0;
  }else if (!right_Far_Sensor && !rightSensor){  // only turn right, ignore left junction
    turn_right(delay_90);
    L_junct++;
  }
  else{
    trace_line();
  }
}

void task6(void){
  if (!left_Far_Sensor || !right_Far_Sensor){
    // for detecting T-junctions as only L-junction will probably be detected
    forward();
    delay(55);
    left_Far_Sensor = digitalRead(pinL_Far_Sensor);
    right_Far_Sensor = digitalRead(pinR_Far_Sensor);
  }
  if ( !left_Far_Sensor && !right_Far_Sensor ) {  // T-junction
    countT++;
    turn_left(delay_90);
  }else
    trace_line();
}

void task7(void){
  if (!bumperSensor) {  // last T-junction
    countT++;
    countBumper++;
  }else if (!in_C && !right_Far_Sensor && !rightSensor){  // into the C
    turn_right(delay_90);
    in_C = true;
  }else if (in_C)
    trace_line();
  else
    trace_line();
}

void task8(void){
  // going backward for around 30 cm
  analogWrite(pinL_PWM, global_spd+20);
  analogWrite(pinR_PWM, global_spd);
  digitalWrite(pinL_DIR, LOW);
  digitalWrite(pinR_DIR, LOW);
  delay(backward_time); // need to calibrate
  forward();
  delay(15);

  while(true){  // end of project, stop the car
    analogWrite(pinL_PWM, 0);
    analogWrite(pinR_PWM, 0);
  }
}
