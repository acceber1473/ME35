
// SET VARIABLES FOR THE MAX AND MIN OF EACH PLANT SO ITS MUCH EASIER LATER 

#include"TFT_eSPI.h"
#include <DHT.h>
#include <DHT_U.h>
#include <Servo.h>

#include "Seeed_FS.h" //Including SD card library
#include"Free_Fonts.h"
#include"RawImage.h"  //Including image processing library
#include"seeed_line_chart.h" //include the library
TFT_eSPI tft;
 
#define max_size 50 //maximum size of data
#define DHTPIN A6
#define DHTTYPE DHT11

doubles data; //Initilising a doubles type to store data
TFT_eSprite spr = TFT_eSprite(&tft);  // Sprite 

int soilSensor = A2;
int soilValue = 0;
int lightValue = 0;
int humidityValue = 0;
int tempValue = 0;
int pos = 0; 
int lightDiff = 0;
int tempDiff = 0;
int humidityDiff = 0;
int soilDiff = 0;

bool keyA; 
bool keyB;
bool keyC;
bool keyRight; 
bool keyLeft; 
bool keyUp;
bool keyDown;
bool motorStatus1;
bool motorStatus2;
bool motorStatus3;
bool motorStatus4;
bool motorStatus5;
bool motorStatus6;

DHT dht(DHTPIN, DHTTYPE);

Servo myservo;
 
void setup() {
    pinMode(WIO_LIGHT, INPUT);
    pinMode(WIO_KEY_A, INPUT);
    pinMode(WIO_KEY_B, INPUT);
    pinMode(WIO_KEY_C, INPUT);

    pinMode(WIO_5S_UP, INPUT);
    pinMode(WIO_5S_DOWN, INPUT);
    pinMode(WIO_5S_LEFT, INPUT);
    pinMode(WIO_5S_RIGHT, INPUT);
    pinMode(WIO_5S_PRESS, INPUT);

    myservo.attach(D0);
   
    tft.begin();
    tft.setRotation(3);

    tft.fillScreen(TFT_WHITE);
    
    if (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI)) {
        while (1);
      }
    
    tft.setTextSize(2);
    tft.setTextColor(tft.color565(0,204,0));
    tft.setFreeFont(&FreeSansBold12pt7b);
    tft.drawString("Plant Monitor",1,25);
    delay(200);

    drawImage<uint8_t>("sprout2.bmp", 5, 95);
    delay(200);

    drawImage<uint8_t>("sprout2.bmp", 5, 140);
    delay(200);

    drawImage<uint8_t>("sprout2.bmp", 5, 185);
    delay(200);
    
    tft.setTextSize(1);
    tft.setTextColor(TFT_BLACK);
    tft.setFreeFont(&FreeSansOblique12pt7b);
    tft.drawString("Press A for stats", 45, 100);
    tft.drawString("Press B for graphs", 45, 145);
    tft.drawString("Press C for plant thoughts", 45, 191);

    spr.createSprite(TFT_HEIGHT,TFT_WIDTH);
    dht.begin();
    
    keyA = HIGH;
    keyB = HIGH;
    keyC = HIGH;

    motorStatus1 = HIGH;
    motorStatus2 = HIGH;

    motorStatus3 = HIGH;
    motorStatus4 = HIGH;

    motorStatus5 = HIGH;
    motorStatus6 = HIGH;

}
 
void loop() {
  
  if (digitalRead(WIO_KEY_A) == LOW){
    keyA = LOW;
    keyB = HIGH;
    keyC = HIGH;
    }

  if (digitalRead(WIO_KEY_B) == LOW){
    keyB = LOW;
    keyA = HIGH;
    keyC = HIGH;
    }

  if (digitalRead(WIO_KEY_C) == LOW){
    keyC = LOW;
    keyA = HIGH;
    keyB = HIGH;
    }  

  // PRESSING A GIVES YOU THE STATS //  

  if (keyA == LOW){
      
      tft.fillScreen(TFT_WHITE);
      tft.fillRect(0,0,62,240,tft.color565(204, 229, 255));
      tft.setTextSize(2);
      tft.setTextColor(TFT_BLACK);
      tft.setFreeFont(&FreeSansBoldOblique12pt7b);
      tft.drawString("S",8,0);
      tft.drawString("T",8,45);
      tft.drawString("A",8,90);
      tft.drawString("T",8,135);
      tft.drawString("S",8,180);
      delay(1000); 

// 4 BOXES
      
      // TEMPERATURE // 
      
      tempValue = dht.readTemperature();
      if (tempValue <= 14 or tempValue >= 31){ 
          tft.fillRect(65, 15, 205, 37, tft.color565(255, 102, 102));  // fills red
        }  
      else if (tempValue <= 17 and tempValue >= 15){
          tft.fillRect(65, 15, 205, 37, tft.color565(255, 255, 153));  // fills yellow
        } 
      else if (tempValue <= 30 and tempValue >= 27){
          tft.fillRect(65, 15, 205, 37, tft.color565(255, 255, 153));  // fills yellow
        }     
      else if (tempValue >= 18 and tempValue <= 26){
          tft.fillRect(65, 15, 205, 37, tft.color565(153, 255, 153));  // fills green
        } 
        
      tft.setTextSize(0.75);
      tft.setTextColor(TFT_BLACK);
      tft.setFreeFont(&FreeSansOblique12pt7b);  
      tft.drawString("Temperature :     C",68,21);  

      tft.setTextSize(1);
      tft.setTextColor(TFT_BLACK);
      tft.setFreeFont(&FreeSansBold12pt7b);
      tft.drawNumber(tempValue,223, 21);
      delay(500);

      // LIGHT // 
      
      lightValue = analogRead(WIO_LIGHT);
        
      if (lightValue <= 75 or lightValue >= 2000){ 
          tft.fillRect(65, 75, 202, 37, tft.color565(255, 102, 102));  // fills red
          motorStatus3 = LOW;
        }  
      else if (lightValue > 75 and lightValue < 100){
          tft.fillRect(65, 75, 202, 37, tft.color565(255, 255, 153));  // fills yellow
          motorStatus3 = LOW;
        }   
      else if (lightValue > 1614 and lightValue < 2000){
          tft.fillRect(65, 75, 202, 37, tft.color565(255, 255, 153));  // fills yellow
          motorStatus3 = LOW;
        }    
      else if (lightValue >= 100 and lightValue <=1614){
          tft.fillRect(65, 75, 202, 37, tft.color565(153, 255, 153));  // fills green
          motorStatus3 = HIGH;
        }  
        
      tft.setTextSize(0.75);
      tft.setTextColor(TFT_BLACK);
      tft.setFreeFont(&FreeSansOblique12pt7b);  
      tft.drawString("Light :       lux",68,81);

      tft.setTextSize(1);
      tft.setTextColor(TFT_BLACK);
      tft.setFreeFont(&FreeSansBold12pt7b);
      tft.drawNumber(lightValue,137, 81);  
      delay(100);

      if (motorStatus3 == LOW and motorStatus4 == HIGH){
        for (pos = 100; pos >= 0; pos -= 1) {
           myservo.write(pos);
           delay(10);
          }
        for (pos = 0; pos <= 100; pos += 1) {
           myservo.write(pos);
           delay(10);
          } 
        motorStatus4 = LOW;  
        }

      if (motorStatus3 == HIGH and motorStatus4 == LOW){
        for (pos = 100; pos >= 0; pos -= 1) {
           myservo.write(pos);
           delay(10);
          }
        for (pos = 0; pos <= 100; pos += 1) {
           myservo.write(pos);
           delay(10);
          } 
        for (pos = 100; pos >= 0; pos -= 1) {
           myservo.write(pos);
           delay(10);
          }
        for (pos = 0; pos <= 100; pos += 1) {
           myservo.write(pos);
           delay(10);
          }   
        motorStatus4 = HIGH;
        
        }
       
      // HUMIDITY // 
      
      humidityValue = dht.readHumidity();

      if (humidityValue <= 75 or humidityValue >= 2000){ 
          tft.fillRect(65, 135, 200, 37, tft.color565(255, 102, 102));  // fills red
          motorStatus5 = LOW;
        }  
      else if (humidityValue >= 76 and humidityValue <= 269){
          tft.fillRect(65, 135, 200, 37, tft.color565(255, 255, 153));  // fills yellow
          motorStatus5 = LOW;
        }   
      else if (humidityValue >= 1615 and humidityValue <= 1999){
          tft.fillRect(65, 135, 200, 37, tft.color565(255, 255, 153));  // fills yellow
          motorStatus5 = LOW;
        }    
      else if (humidityValue >= 270 and humidityValue <= 1614){
          tft.fillRect(65, 135, 200, 37, tft.color565(153, 255, 153));  // fills green
          motorStatus5 = LOW;
        } 
      
      tft.setTextSize(0.75);
      tft.setTextColor(TFT_BLACK);
      tft.setFreeFont(&FreeSansOblique12pt7b);
      tft.drawString("Humidity :      %",68,141);

      tft.setTextSize(1);
      tft.setTextColor(TFT_BLACK);
      tft.setFreeFont(&FreeSansBold12pt7b);
      tft.drawNumber(dht.readHumidity(),180, 141);
      delay(200);

      if (motorStatus5 == LOW and motorStatus6 == HIGH){
        for (pos = 100; pos <= 180; pos += 1) {
           myservo.write(pos);
           delay(15);
          }
        for (pos = 180; pos >= 100; pos -= 1) {
           myservo.write(pos);
           delay(15);
          } 
        motorStatus6 = LOW;  
        }

      if (motorStatus5 == HIGH and motorStatus6 == LOW){
        for (pos = 0; pos <= 85; pos += 1) {
           myservo.write(pos);
           delay(10);
          }
        for (pos = 85; pos >= 0; pos -= 1) {
           myservo.write(pos);
           delay(10);
          }
        for (pos = 0; pos <= 85; pos += 1) {
           myservo.write(pos);
           delay(10);
          }
        for (pos = 85; pos >= 0; pos -= 1) {
           myservo.write(pos);
           delay(10);
          }
        for (pos = 0; pos <= 85; pos += 1) {
           myservo.write(pos);
           delay(10);
          }
        for (pos = 85; pos >= 0; pos -= 1) {
           myservo.write(pos);
           delay(10);
          }   
        for (pos = 85; pos >= 0; pos -= 1) {
           myservo.write(pos);
           delay(10);
          }       
        motorStatus6 = HIGH;
        
        }

      // HUMIDITY // 
      
      soilValue = analogRead(soilSensor);

      if (soilValue >= 1000){ 
          tft.fillRect(65, 195, 200, 37, tft.color565(255, 102, 102));  // fills red
          motorStatus1 = LOW;
        }  
      else if (soilValue >= 800 and soilValue <= 999){
          tft.fillRect(65, 195, 200, 37, tft.color565(255, 255, 153));  // fills yellow
           
          motorStatus1 = LOW;
        }    
      else if (soilValue < 800){
          tft.fillRect(65, 195, 200, 37, tft.color565(153, 255, 153));  // fills green
          motorStatus1 = HIGH;
        }

      tft.setTextSize(0.75);
      tft.setTextColor(TFT_BLACK);
      tft.setFreeFont(&FreeSansOblique12pt7b);
      tft.drawString("Soil : ",68,201);

      tft.setTextSize(1);
      tft.setTextColor(TFT_BLACK);
      tft.setFreeFont(&FreeSansBold12pt7b);
      tft.drawNumber(soilValue,125,201);
      delay(200); 

      if (motorStatus1 == LOW and motorStatus2 == HIGH){
        for (pos = 100; pos <= 180; pos += 1) {
           myservo.write(pos);
           delay(15);
          }
        for (pos = 180; pos >= 100; pos -= 1) {
           myservo.write(pos);
           delay(15);
          } 
        motorStatus2 = LOW;  
        }

      if (motorStatus1 == HIGH and motorStatus2 == LOW){
        for (pos = 0; pos <= 85; pos += 1) {
           myservo.write(pos);
           delay(10);
          }
        for (pos = 85; pos >= 0; pos -= 1) {
           myservo.write(pos);
           delay(10);
          }
        for (pos = 0; pos <= 85; pos += 1) {
           myservo.write(pos);
           delay(10);
          }
        for (pos = 85; pos >= 0; pos -= 1) {
           myservo.write(pos);
           delay(10);
          }
        for (pos = 0; pos <= 85; pos += 1) {
           myservo.write(pos);
           delay(10);
          }
        for (pos = 85; pos >= 0; pos -= 1) {
           myservo.write(pos);
           delay(10);
          }   
        for (pos = 85; pos >= 0; pos -= 1) {
           myservo.write(pos);
           delay(10);
          }       
        motorStatus2 = HIGH;
        
        }

      delay(5000);
      
      spr.pushSprite(0,0);
      delay(200);
      
       } 
      

  // PRESSING B GIVES YOU THE GRAPHS ///  

  if (keyB == LOW){

        if(digitalRead(WIO_5S_LEFT) == LOW){   // LIGHT
          
            spr.fillSprite(TFT_WHITE);
            if (data.size() == max_size) {
                data.pop();//this is used to remove the first read variable
            }
            lightValue = analogRead(WIO_LIGHT);
            data.push(lightValue); //read variables and store in data
         
            //Settings for the line graph title
            auto header =  text(0, 0)
                        .value("Light Values")
                        .align(center)
                        .valign(vcenter)
                        .width(tft.width())
                        .thickness(3);
         
            header.height(header.font_height() * 2);
            header.draw(); //Header height is the twice the height of the font

            if (lightValue <= 75 or lightValue >= 2000){    // RED
                 auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
                   content
                          .height(tft.height() - header.height() * 1.5) //actual height of the line chart
                          .width(tft.width() - content.x() * 2) //actual width of the line chart
                          .based_on(0.0) //Starting point of y-axis, must be a float
                          .show_circle(false) //drawing a cirle at each point, default is on.
                          .value(data) //passing through the data to line graph
                          .color(TFT_RED)
                          .draw();

              }  
            else if (lightValue > 75 and lightValue < 100){   // YELLOW
                  auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
                   content
                          .height(tft.height() - header.height() * 1.5) //actual height of the line chart
                          .width(tft.width() - content.x() * 2) //actual width of the line chart
                          .based_on(0.0) //Starting point of y-axis, must be a float
                          .show_circle(false) //drawing a cirle at each point, default is on.
                          .value(data) //passing through the data to line graph
                          .color(TFT_YELLOW)
                          .draw();
              }   
            else if (lightValue > 1614 and lightValue < 2000){  //yellow
                  auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
                   content
                          .height(tft.height() - header.height() * 1.5) //actual height of the line chart
                          .width(tft.width() - content.x() * 2) //actual width of the line chart
                          .based_on(0.0) //Starting point of y-axis, must be a float
                          .show_circle(false) //drawing a cirle at each point, default is on.
                          .value(data) //passing through the data to line graph
                          .color(TFT_YELLOW)
                          .draw();
              }    
            else if (lightValue >= 100 and lightValue <=1614){  // green
                  auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
                   content
                          .height(tft.height() - header.height() * 1.5) //actual height of the line chart
                          .width(tft.width() - content.x() * 2) //actual width of the line chart
                          .based_on(0.0) //Starting point of y-axis, must be a float
                          .show_circle(false) //drawing a cirle at each point, default is on.
                          .value(data) //passing through the data to line graph
                          .color(TFT_GREEN)
                          .draw();
              } 
            
         
          //Settings for the line graph
         
            spr.pushSprite(0, 0);
            delay(50);
        }

        else if(digitalRead(WIO_5S_RIGHT) == LOW){   // Temperature
          
            spr.fillSprite(TFT_WHITE);
            if (data.size() == max_size) {
                data.pop();//this is used to remove the first read variable
            }
            tempValue = dht.readTemperature();
            data.push(tempValue); //read variables and store in data
         
            //Settings for the line graph title
            auto header =  text(0, 0)
                        .value("Temperature Values")
                        .align(center)
                        .valign(vcenter)
                        .width(tft.width())
                        .thickness(3);
         
            header.height(header.font_height() * 2);
            header.draw(); //Header height is the twice the height of the font

            if (tempValue <= 14 or tempValue >= 31){ 
                auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
                 content
                        .height(tft.height() - header.height() * 1.5) //actual height of the line chart
                        .width(tft.width() - content.x() * 2) //actual width of the line chart
                        .based_on(0.0) //Starting point of y-axis, must be a float
                        .show_circle(false) //drawing a cirle at each point, default is on.
                        .value(data) //passing through the data to line graph
                        .color(TFT_RED) //Setting the color for the line
                        .draw();  // fills red
              }  
              
            else if (tempValue <= 17 and tempValue >= 15){
                auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
                 content
                        .height(tft.height() - header.height() * 1.5) //actual height of the line chart
                        .width(tft.width() - content.x() * 2) //actual width of the line chart
                        .based_on(0.0) //Starting point of y-axis, must be a float
                        .show_circle(false) //drawing a cirle at each point, default is on.
                        .value(data) //passing through the data to line graph
                        .color(TFT_YELLOW) //Setting the color for the line  // yellow
                        .draw();
              } 
              
            else if (tempValue <= 30 and tempValue >= 27){
                auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
                 content
                        .height(tft.height() - header.height() * 1.5) //actual height of the line chart
                        .width(tft.width() - content.x() * 2) //actual width of the line chart
                        .based_on(0.0) //Starting point of y-axis, must be a float
                        .show_circle(false) //drawing a cirle at each point, default is on.
                        .value(data) //passing through the data to line graph
                        .color(TFT_YELLOW) //Setting the color for the line
                        .draw();  // fills yellow
              }
                   
            else if (tempValue >= 18 and tempValue <= 26){
                auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
                 content
                        .height(tft.height() - header.height() * 1.5) //actual height of the line chart
                        .width(tft.width() - content.x() * 2) //actual width of the line chart
                        .based_on(0.0) //Starting point of y-axis, must be a float
                        .show_circle(false) //drawing a cirle at each point, default is on.
                        .value(data) //passing through the data to line graph
                        .color(TFT_GREEN) //Setting the color for the line
                        .draw();  // fills green
              }
         
            spr.pushSprite(0, 0);
            delay(50);
        }

        else if(digitalRead(WIO_5S_UP) == LOW){   // Humidity  THERE'S SOMETHING WRONG WITH THE HUMIDITY/TEMP SENSOR
          
           spr.fillSprite(TFT_WHITE);
            if (data.size() == max_size) {
                data.pop();//this is used to remove the first read variable
            }
            humidityValue = dht.readHumidity();
            data.push(humidityValue); //read variables and store in data
         
            //Settings for the line graph title
            auto header =  text(0, 0)
                        .value("Humidity Values")
                        .align(center)
                        .valign(vcenter)
                        .width(tft.width())
                        .thickness(3);
         
            header.height(header.font_height() * 2);
            header.draw(); //Header height is the twice the height of the font

            if (humidityValue <= 75 or humidityValue >= 2000){ 
                auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
                 content
                        .height(tft.height() - header.height() * 1.5) //actual height of the line chart
                        .width(tft.width() - content.x() * 2) //actual width of the line chart
                        .based_on(0.0) //Starting point of y-axis, must be a float
                        .show_circle(false) //drawing a cirle at each point, default is on.
                        .value(data) //passing through the data to line graph
                        .color(TFT_RED) //Setting the color for the line
                        .draw();  // fills red
              }  
            else if (humidityValue >= 76 and humidityValue <= 269){
                auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
                 content
                        .height(tft.height() - header.height() * 1.5) //actual height of the line chart
                        .width(tft.width() - content.x() * 2) //actual width of the line chart
                        .based_on(0.0) //Starting point of y-axis, must be a float
                        .show_circle(false) //drawing a cirle at each point, default is on.
                        .value(data) //passing through the data to line graph
                        .color(TFT_YELLOW) //Setting the color for the line
                        .draw();  // fills yellow
              }   
            else if (humidityValue >= 1615 and humidityValue <= 1999){
                auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
                 content
                        .height(tft.height() - header.height() * 1.5) //actual height of the line chart
                        .width(tft.width() - content.x() * 2) //actual width of the line chart
                        .based_on(0.0) //Starting point of y-axis, must be a float
                        .show_circle(false) //drawing a cirle at each point, default is on.
                        .value(data) //passing through the data to line graph
                        .color(TFT_YELLOW) //Setting the color for the line
                        .draw();  // fills yellow
              }    
            else if (humidityValue >= 270 and humidityValue <= 1614){
                auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
                 content
                        .height(tft.height() - header.height() * 1.5) //actual height of the line chart
                        .width(tft.width() - content.x() * 2) //actual width of the line chart
                        .based_on(0.0) //Starting point of y-axis, must be a float
                        .show_circle(false) //drawing a cirle at each point, default is on.
                        .value(data) //passing through the data to line graph
                        .color(TFT_GREEN) //Setting the color for the line
                        .draw();  // fills green
              }
            
         
            spr.pushSprite(0, 0);
            delay(50);
        }

        else if(digitalRead(WIO_5S_DOWN) == LOW){   // Soil
          
            spr.fillSprite(TFT_WHITE);
            if (data.size() == max_size) {
                data.pop();//this is used to remove the first read variable
            }
            soilValue = analogRead(soilSensor);
            data.push(soilValue); //read variables and store in data
         
            //Settings for the line graph title
            auto header =  text(0, 0)
                        .value("Soil Values")
                        .align(center)
                        .valign(vcenter)
                        .width(tft.width())
                        .thickness(3);
         
            header.height(header.font_height() * 2);
            header.draw(); //Header height is the twice the height of the font

            if (soilValue >= 1000){ 
                auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
                 content
                        .height(tft.height() - header.height() * 1.5) //actual height of the line chart
                        .width(tft.width() - content.x() * 2) //actual width of the line chart
                        .based_on(0.0) //Starting point of y-axis, must be a float
                        .show_circle(false) //drawing a cirle at each point, default is on.
                        .value(data) //passing through the data to line graph
                        .color(TFT_RED) //Setting the color for the line
                        .draw();  // fills red
              }  
              
            else if (soilValue >= 800 and soilValue <= 999){
                auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
                 content
                        .height(tft.height() - header.height() * 1.5) //actual height of the line chart
                        .width(tft.width() - content.x() * 2) //actual width of the line chart
                        .based_on(0.0) //Starting point of y-axis, must be a float
                        .show_circle(false) //drawing a cirle at each point, default is on.
                        .value(data) //passing through the data to line graph
                        .color(TFT_YELLOW) //Setting the color for the line
                        .draw();  // fills yellow
                 
              }    
              
            else if (soilValue < 800){
                auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
                 content
                        .height(tft.height() - header.height() * 1.5) //actual height of the line chart
                        .width(tft.width() - content.x() * 2) //actual width of the line chart
                        .based_on(0.0) //Starting point of y-axis, must be a float
                        .show_circle(false) //drawing a cirle at each point, default is on.
                        .value(data) //passing through the data to line graph
                        .color(TFT_GREEN) //Setting the color for the line
                        .draw();  // fills green
              }
         
          //Settings for the line graph
            
         
            spr.pushSprite(0, 0);
            delay(50);
        }  
       // while (digitalRead(WIO_KEY_A) == HIGH and digitalRead(WIO_KEY_B) == HIGH and digitalRead(WIO_KEY_C) == HIGH){  
       // }    

        
    }



// PRESSING C GIVES YOU THE THOUGHT BUBBLE //    

  if (keyC == LOW){

      tft.fillScreen(TFT_WHITE);
      tft.drawEllipse(150,100,140,90,TFT_BLACK);
      
      delay(500);

      tft.drawCircle(257,190,15,TFT_BLACK);

      tft.drawCircle(284,218,12,TFT_BLACK);

      tft.setTextSize(1);
      tft.setTextColor(TFT_BLACK);
      tft.setFreeFont(&FreeSansOblique12pt7b);

      humidityValue = dht.readHumidity();
      tempValue = dht.readTemperature();
      lightValue = analogRead(WIO_LIGHT);
      soilValue = analogRead(soilSensor);

      // LIGHT

      if (abs(2000 - lightValue) >= abs(lightValue - 10)){
        lightDiff = abs(2000 - lightValue);
        }

      else {
        lightDiff = abs(lightValue - 10);
        }  

      // TEMP  

      if (abs(31 - tempValue) >= abs(tempValue - 14)){
        tempDiff = abs(31 - tempValue);
        }

      else {
        tempDiff = abs(tempValue - 14);
        } 

      // HUMIDITY

       if (abs(2000 - humidityValue) >= abs(humidityValue - 75)){
        humidityDiff = abs(2000 - humidityValue);
        }

       else {
        humidityDiff = abs(humidityValue - 75);
        } 

     // SOIL

       if (abs(1000 - soilValue) >= abs(soilValue - 800)){
        soilDiff = abs(1000 - soilValue);
        }

       else {
        soilDiff = abs(soilValue - 800);
        }    
        

       if (lightDiff > soilDiff and lightDiff > tempDiff and lightDiff > humidityDiff){
          tft.drawString("Am I underground?? :(", 45, 90);
        }  

       else if (soilDiff > lightDiff and soilDiff > tempDiff and soilDiff > humidityDiff){
          tft.drawString("Water, please!", 65, 99);
        }  
      
       else if (tempDiff > lightDiff and tempDiff > soilDiff and tempDiff > humidityDiff){
            tft.drawString("brrrrr", 75, 99);
        } 

       else if (humidityDiff > lightDiff and humidityDiff > soilDiff and humidityDiff > tempDiff){
            tft.drawString("Am I in the desert???", 50, 90);
        } 

        delay(5000);
      }
     
    
}
