// THIS DISPLAYS MOTOR DEGREES ON THE WIO //
// TERMINAL CODE: 

#include"TFT_eSPI.h"
TFT_eSPI tft;

// initialize string being sent over
String line = "";
// initialize previous set of coordinates
int previous_x = 0;
int previous_y = 0;
// initialize new set of coordinates
int x;
int y;

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_WHITE);
}

void loop() {
  // Doesn't draw anything out for the first set of coordinates
  while(Serial1.available()){
    if (previous_x == 0 && previous_y == 0){
      line = Serial1.readStringUntil(',');   
      x = 0.4*parseInput(line);
      line = Serial1.readStringUntil('\n');   
      y = 0.4*parseInput(line);
      previous_x = x;
      previous_y = y;
      }
      
    else{
      // takes the x values
      line = Serial1.readStringUntil(','); 
      x = 0.3*parseInput(line);
      delay(100);
      // takes the y value
      line = Serial1.readStringUntil('\n');  
      y = 0.3*parseInput(line);
      // draws line from previous and new coordinates 
      tft.drawLine(previous_x,previous_y+83,x,y+83,TFT_BLACK);

      // printing out to troubleshoot 
      Serial.println(previous_x);
      Serial.println(previous_y);
      Serial.println(x);
      Serial.println(y);
      Serial.println();

      // updating previous coordinates
      previous_x = x;
      previous_y = y;
      } 
    }
}

// function to change string sent over to int 
int parseInput(String msg) {
  int msg_num = msg.toInt();
  return msg_num;
} 


/*import hub, utime

rightMotor = hub.port.A.motor
leftMotor = hub.port.B.motor
wio = hub.port.D
wio.mode(hub.port.MODE_FULL_DUPLEX)
wio.baud(9600)

rightMotor.mode(2)
leftMotor.mode(2)

utime.sleep(1)
rightMotor.get()
leftMotor.get()
wio.write(str(leftMotor.get()[0]) + ' \n')
utime.sleep(1)


#set position
rightMotor.run_to_position(4,10)
leftMotor.run_to_position(0,10)

rightMotor.run_to_position(-39,10)
leftMotor.run_to_position(-1,10)
utime.sleep(1)

rightMotor.run_to_position(-32,10)
leftMotor.run_to_position(-45,10)
utime.sleep(1)

rightMotor.run_to_position(-20,10)
leftMotor.run_to_position(-86,10)
utime.sleep(1)

rightMotor.run_to_position(-8,10)
leftMotor.run_to_position(-90,10)
utime.sleep(1)

rightMotor.run_to_position(18,10)
leftMotor.run_to_position(-64,10)
utime.sleep(1)

rightMotor.run_to_position(41,10)
leftMotor.run_to_position(-32,10)
utime.sleep(1)

rightMotor.run_to_position(39,10)
leftMotor.run_to_position(-21,10)*/
