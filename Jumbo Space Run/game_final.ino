// ME35 Game //
// Olif and Rebecca //

#include <SoftwareSerial.h>
#include "Free_Fonts.h"
#include "pitches.h"
#include"TFT_eSPI.h"
#define BUZZER_PIN WIO_BUZZER 

TFT_eSPI tft;   // initialize TFT library
TFT_eSprite spr = TFT_eSprite(&tft);

//--------------- BIT MAPS ----------------//

// ELEPHANT
const int elephantImgW = 27; const int elephantImgH = 15;
char elephantImg[] =
  "ZZZZZZZZZBBBBBZZBBBBBZZZZZZZZZZZZZBBBWWWBBBWWWWBBZZZZZZ"
  "ZZZZZBBWWWWWWWBWWWWWBBZZZZZZZZZZBWWWWWWWWBWWWWWWBZZZZBB"
  "BBZBBWWWWWWWWBWWWWWWBZZZZBWWBBBWWWBWWWWWBWWWWWWBZZZZBWWW"
  "BBWWWBWWWWWBWWWWWWBBZZZBBWWWWWWWRRWWWWBWWWWWWBBBZBZBBWWW"
  "WWWWWWWWWWBBWWWBBWBBBZZBBBBWWWWWWWWWWWBBBBBWWBZZZZZZZBBBB"
  "WWWWBWWWWWWWWWWBZZZZZZZZZZBBBBBWWWWWWWWWWWBZZZZZZZZZZZZZB"
  "WWWWBBBBWWWWBZZZZZZZZZZZZZBRRWBBZZBRRWBBZZZZZZZZZZZZZBBBBB"
  "ZZZBBBBBZZZ";

// GREEN ENEMY BEFORE HIT
const int alienImgW = 14; const int alienImgH = 11;
char alienImg[] =
  "GGGZZZZZZZZGGGZZZGZZZZZZGZZZZZGGGGGGGGGGZZZGGGGGGGGGGGGZ"
  "GGGZGGGGGGZGGGGGGZZGGGGZZGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"
  "GZZZGGZZGGZZZGZGGZGGZZGGZGGZZZZZZGZZGZZZZZ";
  
// GREEN ENEMY AFTER HIT

const int alien2ImgW = 14; const int alien2ImgH = 11;
char alien2Img[] =
  "TTTZZZZZZZZTTTZZZTZZZZZZTZZZZZTTTTTTTTTZZZTTTTTTTTTTTTZ"
  "TTTZTTTTTTZTTTTTTZZTTTTZZTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT"
  "TZZZTTZZTTZZZTZTTZTTZZTTZTTZZZZZZTZZTZZZZZ";

// UFO BEFORE HIT 
const int ufoImgW = 32; const int ufoImgH = 22;
char ufoImg[] =
  "ZZZZZZZZZZZZZZBBBBBZZZZZZZZZZZZZZZZZZZZZZZZZBBGGGGGBBZZZZZZZZZZZZZZZZZZZZZZBGGGGGGGGGBZZZZZZZZZZ"
  "ZZZZZZZZZZBGGGGGGGGGGGBZZZZZZZZZZZZBBBBBBBGGGGGGGGGGGGBZZZZZZZZZZBBWWWWWWBGGGGGGGGGGGGGBZZZZZZZZB"
  "WWWBBWWWBGGGGGGGGGGGGGBZZZZZZZZBWWBRRBWWWBGGGGGGGGGGGGBBBBZZZZZBWWBRRBWWWWBBGGGGGGGGGBWWWWBBZZZ"
  "BWWWBBWWWBBWWBBBBBBBBBWWWWWWWBZZZBWWWWWWBRRBWWWBBWWWWBBWWWWBBWBZZZBBWWWWBRRBWWBRRBWWBRRBWWBRRBBZ"
  "ZZZZBBBWWBBWWWBRRBWWBRRBWWBRRBWBZZZZZZBWWWWWWWWBBWWWWBBWWWWBBWWBZZZZZBWWBBBBBWWWWWWWWWWWWWWWWWBZZZZZZ"
  "ZZZZZBWBZZZZZBBBBBBBWWWWBBBBBBZZZZZZBWBZZZZZZZZZZZZZBWWBZZZZZZZZZZZZBBZZZZZZZZZZZZZZBWWBZZZZZZZZ"
  "ZZZZBZZZZZZZZZZZZZZZZBWBZZZZZZZZZZZZZZZZZZZZZZZZZZZZZBWBZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZBZZZZZZZZZ"
  "ZZZZZZZZZZZZZZZZZZZZZZBZZZZZZZZZ";

// RED LEVEL 2 ENEMY BEFORE HIT
const int alienRedImgW = 14; const int alienRedImgH = 11;
char alienRedImg[] =
  "RRRZZZZZZZZRRRZZZRZZZZZZRZZZZZRRRRRRRRRRZZZRRRRRRRRRRRRZ"
  "RRRZRRRRRRZRRRRRRZZRRRRZZRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"
  "RZZZRRZZRRZZZRZRRZRRZZRRZRRZZZZZZRZZRZZZZZ";


//---------------- VARIABLES ------------------//


// for the elephant 
 

int rect_x = 5;   // x and y starting positions 
int rect_y = 200;

int rect_color = TFT_BLACK;

// for the bullets 

int bullet_x;      
int bullet_y;         
int bullet_color = TFT_BLUE;

// for the enemies- 7 of them 

int enemy_x = 15; 
int enemy_y = 0;

int enemy_x_2 = 15;
int enemy_y_2 = 0;

int enemies_hit = 0;

int score_num = 0;

int hit_enemy = 0;

bool block_1;
bool block_2;
bool block_3;
bool block_4;
bool block_5;
bool block_6;
bool block_7;
bool block_enemy_2;

bool enemy_2_start;

bool level_2;

bool keyC;

//------------------ SET UP -------------------//

void setup() {

  Serial1.begin(9600);
  Serial.begin(9600);
  tft.begin();
  tft.setRotation(3);
  spr.createSprite(TFT_HEIGHT,TFT_WIDTH);

 // Setting buttons as inputs

  pinMode(WIO_KEY_C, INPUT);   
 
  pinMode(WIO_5S_LEFT, INPUT);   
  pinMode(WIO_5S_RIGHT, INPUT);


// Setting buttons as outputs

  pinMode(BUZZER_PIN, OUTPUT);  // buzzer for fun sound effects 

  keyC = HIGH;
  block_1 = LOW;
  enemy_2_start = HIGH;
  level_2 = LOW;
  
  spr.fillSprite(TFT_BLACK);
  spr.setTextSize(1);
  spr.setTextColor(TFT_WHITE);
  spr.setFreeFont(&FreeSansBoldOblique12pt7b);  
  spr.drawString("Press C to play",55,87);
  spr.pushSprite(0,0);

  while (digitalRead(WIO_KEY_C) == HIGH){
    
    }
  }


//------------------------- MAIN LOOP --------------------------//

void loop() {

   spr.fillSprite(TFT_BLACK);
   
   controls();
   
   score();
  
    
    if(digitalRead(WIO_KEY_C) == LOW){
      keyC = LOW;
      }
  
    bullet_start();
  
    gameOver();
    
    spr.pushSprite(0,0);
    delay(50); 
    
  }
  
    

// ------------ DRAW BITMAP -------------- //
 
void drawBitmap(char img[], int imgW, int imgH, int x, int y, int scale) {
  uint16_t cellColor;
  char curPix;
  for (int i = 0; i < imgW * imgH; i++) {
    curPix = img[i];
    if (curPix == 'W') {
      cellColor = tft.color565(192, 192, 192);
    }
    else if (curPix == 'Y') {
      cellColor = TFT_YELLOW;
    }
    else if (curPix == 'B') {
      cellColor = TFT_BLUE;
    }
    else if (curPix == 'R') {
      cellColor = TFT_RED;
    }
    else if (curPix == 'G') {
      cellColor = 0x5E85;
    }
    else if (curPix == 'T') {
      cellColor = TFT_BLACK;
    }
    if (curPix != 'Z' and scale == 1) {
      spr.drawPixel(x + i % imgW, y + i / imgW, cellColor);
    }
    else if (curPix != 'Z' and scale > 1) {
      spr.fillRect(x + scale * (i % imgW), y +
                   scale * (i / imgW), scale, scale, cellColor);
    }
  }
}

// CONTROLS // 
  // ** 5 way switch corresponds to the rectangle moving left or right / up or down 
  // ** the numbers give rough boundaries so that the rectangle square thing doesn't move past the screen 
  // ** but can also change this so that the screen is continuous- would just need to reset x to 0 or something idk 
void controls() {

  if (digitalRead(WIO_5S_LEFT) == LOW){
    if (rect_x > 4 and rect_x < 320){
      rect_x = rect_x - 8;
      } 
    }

  else if (digitalRead(WIO_5S_RIGHT) == LOW){
    if (rect_x < 310){
      rect_x = rect_x + 8;
      }
    }  

  drawBitmap(elephantImg, elephantImgW, elephantImgH, rect_x, rect_y, 2);
  
  }    


/////////////////// STARTING POSITION FOR BULLETS ////////////////////// 

void bullet_start(){

  bullet_x = rect_x; 
  bullet_y = rect_y;
  if (level_2 == LOW){
    if (enemy_y >= 50){
       enemy_2_start = LOW;
    }
    enemies();
    }
    
  else if (level_2 == HIGH){
    enemies_level_2();
    }
  
  
  if (keyC == LOW){
    shooting();
   }  
  
  }

/////////////////////////// SCORE /////////////////////////////

void score() {

  spr.setTextSize(1);
  spr.setTextColor(TFT_WHITE);
  spr.setFreeFont(&FreeSansBoldOblique12pt7b);  
  spr.drawString("Score:  ",185,10);
  spr.drawNumber(enemies_hit, 265,10);
  
  }

/////////////////////////// COLLISION /////////////////////////////
void collision() {

  if (bullet_x >= enemy_x and bullet_x <= enemy_x + 15 and bullet_y >= 0 and bullet_y <= enemy_y){
     block_1 = HIGH;
     tone(BUZZER_PIN, NOTE_G3, 250);
     enemies_hit +=1;
    } 
    
  if (bullet_x >= 57 and bullet_x <= 78  and bullet_y >= 0 and bullet_y <= 30){
     block_2 = HIGH;
     tone(BUZZER_PIN, NOTE_G3, 250);
     enemies_hit +=1;
    } 

  if (bullet_x >= 100 and bullet_x <= 120  and bullet_y >= 0 and bullet_y <= 30){
     block_3 = HIGH;
     tone(BUZZER_PIN, NOTE_G3, 250);
     enemies_hit +=1;
    } 

  if (bullet_x >= 145 and bullet_x <= 175  and bullet_y >= 0 and bullet_y <= 30){
     block_4 = HIGH;
     tone(BUZZER_PIN, NOTE_G3, 250);
     enemies_hit +=1;
    } 

  if (bullet_x >= 190 and bullet_x <= 220  and bullet_y >= 0 and bullet_y <= 30){
     block_5 = HIGH;
     tone(BUZZER_PIN, NOTE_G3, 250);
     enemies_hit +=1;
    } 

  if (bullet_x >= 240 and bullet_x <= 263 and bullet_y >= 0 and bullet_y <= 30){
     block_6 = HIGH; 
     tone(BUZZER_PIN, NOTE_G3, 250);
     enemies_hit +=1;
    }    

  if (bullet_x >= 285 and bullet_x <= 305 and bullet_y >= 0 and bullet_y <= 30){
     block_7 = HIGH;
     tone(BUZZER_PIN, NOTE_G3, 250);
     enemies_hit +=1;
    }  

  if (bullet_x >= enemy_x_2 and bullet_x <= enemy_x_2 + 50 and bullet_y >= 0 and bullet_y <= enemy_y_2 + 50){
    block_enemy_2 = HIGH;
    tone(BUZZER_PIN, NOTE_G3, 250);
    enemies_hit +=1;
    }

  spr.pushSprite(0,0);
 
  
} 

//////////////////////// SHOOTING BULLETS /////////////////////////
void shooting() {

    tone(BUZZER_PIN, NOTE_C2, 250);
    delay(50);

    while (bullet_y >= 0){
      
      spr.fillRect(bullet_x, bullet_y, 5, 5, bullet_color);
      bullet_y = bullet_y - 5;

      spr.pushSprite(0,0);

      spr.fillRect(bullet_x, bullet_y, 5, 10, TFT_BLACK);
      bullet_y = bullet_y - 5;
      spr.pushSprite(0,0);
      delay(1);

      collision();
      }

   
  // digitalWrite(BUZZER_PIN, LOW);   
      
      
   keyC = HIGH;

  }

void enemies() {

// enemy 1
  if (block_1 == LOW){
    
    drawBitmap(alienImg, alienImgW, alienImgH, enemy_x, enemy_y, 2);
    }
  else{
    drawBitmap(alien2Img, alien2ImgW, alien2ImgH, enemy_x, enemy_y, 2);
    }  

// enemy 2    

  if (block_2 == LOW){
    
    drawBitmap(alienImg, alienImgW, alienImgH, enemy_x+45, enemy_y, 2);
    }
  else{
    drawBitmap(alien2Img, alien2ImgW, alien2ImgH, enemy_x+45, enemy_y, 2);
    }    

// enemy 3

  if (block_3 == LOW){
    
    drawBitmap(alienImg, alienImgW, alienImgH, enemy_x+90, enemy_y, 2);
    }
  else{
    drawBitmap(alien2Img, alien2ImgW, alien2ImgH, enemy_x+90, enemy_y, 2);
    }  

// enemy 4

  if (block_4 == LOW){
    
    drawBitmap(alienImg, alienImgW, alienImgH, enemy_x+135, enemy_y, 2);
    }
  else{
    drawBitmap(alien2Img, alien2ImgW, alien2ImgH, enemy_x+135, enemy_y, 2);
    }      

// enemy 5

  if (block_5 == LOW){
    
    drawBitmap(alienImg, alienImgW, alienImgH, enemy_x+180, enemy_y, 2);
    }
  else{
    drawBitmap(alien2Img, alien2ImgW, alien2ImgH, enemy_x+180, enemy_y, 2);
    } 

// enemy 6

  if (block_6 == LOW){
    
    drawBitmap(alienImg, alienImgW, alienImgH, enemy_x+225, enemy_y, 2);
    }
  else{
    drawBitmap(alien2Img, alien2ImgW, alien2ImgH, enemy_x+225, enemy_y, 2);
    }   

// enemy 7

  if (block_7 == LOW){
    
    drawBitmap(alienImg, alienImgW, alienImgH, enemy_x+270, enemy_y, 2);
    }
  else{
    drawBitmap(alien2Img, alien2ImgW, alien2ImgH, enemy_x+270, enemy_y, 2);
    }              


  spr.pushSprite(0,0);
  delay(50);

  enemy_y += 5;

  if (enemy_2_start == LOW) {
    
    drawBitmap(ufoImg, ufoImgW, ufoImgH, enemy_x_2, enemy_y_2, 2);
  
    enemy_y_2 += 1;

   spr.pushSprite(0,0);
   delay(50);

    if (enemy_x_2 >= 0){
      enemy_x_2 += 10; 

     }
    if (enemy_x_2 >= 320){
      enemy_x_2 = 0;
     } 
      
  }

  }

void enemies_level_2(){

// enemy 1
    drawBitmap(alienRedImg, alienRedImgW, alienRedImgH, enemy_x, enemy_y, 2);
    
// enemy 2   
    drawBitmap(alienRedImg, alienRedImgW, alienRedImgH, enemy_x+45, enemy_y, 2);
 
// enemy 3
    drawBitmap(alienRedImg, alienRedImgW, alienRedImgH, enemy_x+90, enemy_y, 2);

// enemy 4    
    drawBitmap(alienRedImg, alienRedImgW, alienRedImgH, enemy_x+135, enemy_y, 2);

// enemy 5    
    drawBitmap(alienRedImg, alienRedImgW, alienRedImgH, enemy_x+180, enemy_y, 2);

// enemy 6    
    drawBitmap(alienRedImg, alienRedImgW, alienRedImgH, enemy_x+225, enemy_y, 2);

// enemy 7
    drawBitmap(alienRedImg, alienRedImgW, alienRedImgH, enemy_x+270, enemy_y, 2);

  spr.pushSprite(0,0);
  delay(50);

  enemy_y += 5;

 }
   
  
void gameOver() {

  Serial.println(enemies_hit);

  if (enemies_hit >= 80){

    level_2 = HIGH;

    spr.fillSprite(TFT_BLACK);
    
    spr.setTextSize(2);
    spr.setTextColor(TFT_WHITE);
    spr.setFreeFont(&FreeSansOblique12pt7b);  
    spr.drawString("LEVEL 2!",68,85);
   

    spr.pushSprite(0,0);
    delay(50);

    winningTone();

    delay(5000);

    enemies_hit = 0;
    enemy_x = 15; 
    enemy_y = 0;
    
    }

  hit();
  lost();
}  
  

void winningTone() {
  
 
  tone(BUZZER_PIN, NOTE_G3);  // triplets 
  delay(125);              // delay times based on whether or not note is triplet, eigth, quarter, etc.
  tone(BUZZER_PIN, NOTE_C4);
  delay(125);
  tone(BUZZER_PIN, NOTE_E4);
  delay(125);

  tone(BUZZER_PIN, NOTE_G4);
  delay(125);
  tone(BUZZER_PIN, NOTE_C5);
  delay(125);
  tone(BUZZER_PIN, NOTE_E5);
  delay(125);

  tone(BUZZER_PIN, NOTE_G6); // quarter note
  delay(375);
  tone(BUZZER_PIN, NOTE_E5);  // eighth note
  delay(188);

  noTone(BUZZER_PIN);
  delay(188);   // eighth note rest

  tone(BUZZER_PIN, NOTE_GS3);  // triplets
  delay(125);
  tone(BUZZER_PIN, NOTE_C4);
  delay(125);
  tone(BUZZER_PIN, NOTE_DS4);
  delay(125);

  tone(BUZZER_PIN, NOTE_GS4);
  delay(125);
  tone(BUZZER_PIN, NOTE_C5);
  delay(125);
  tone(BUZZER_PIN, NOTE_DS5);
  delay(125);

  tone(BUZZER_PIN, NOTE_GS6);  // quarter note
  delay(375);
  tone(BUZZER_PIN, NOTE_E5);  // eighth note
  delay(188);

  noTone(BUZZER_PIN);
  delay(188);   // eighth note rest

  tone(BUZZER_PIN, NOTE_AS3);  // triplets
  delay(125);
  tone(BUZZER_PIN, NOTE_D4);
  delay(125);
  tone(BUZZER_PIN, NOTE_F4);
  delay(125);

  tone(BUZZER_PIN, NOTE_AS4);
  delay(125);
  tone(BUZZER_PIN, NOTE_D5);
  delay(125);
  tone(BUZZER_PIN, NOTE_F5);
  delay(125);

  tone(BUZZER_PIN, NOTE_AS6);  // quarter note
  delay(375);

  tone(BUZZER_PIN, NOTE_AS6);  // triplets
  delay(125);
  noTone(BUZZER_PIN);
  delay(25);
  tone(BUZZER_PIN, NOTE_AS6);
  delay(125);
  noTone(BUZZER_PIN);
  delay(25);
  tone(BUZZER_PIN, NOTE_AS6);
  delay(125);
  noTone(BUZZER_PIN);
  delay(25);

  tone(BUZZER_PIN, NOTE_C7); // whole note
  delay(1400);
  noTone(BUZZER_PIN);

}

void hit() {

  if (rect_y == enemy_y){
     tone(BUZZER_PIN, NOTE_G3, 250);
     hit_enemy += 1;
    }

  spr.pushSprite(0,0);
} 
  
  
void lost() {
  if (hit_enemy >= 1){
    
    //spr.fillSprite(TFT_BLACK);
    
    spr.setTextSize(2);
    spr.setTextColor(TFT_RED);
    spr.setFreeFont(&FreeSansOblique12pt7b);  
    spr.drawString("YOU LOST!",43,90);
    delay(1000);
    
    }
  }
  

  


    
