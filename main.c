#include <LiquidCrystal_I2C.h>

#include "tone.h"
#include "delay.h"

LiquidCrystal_I2C lcd(0x3F, 16,2);

const int BUZ=10;
const int melody [] = { 
NOTE_AS4, NOTE_AS4, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_AS3, NOTE_C4, NOTE_D4, NOTE_AS3, NOTE_F4, NOTE_none,
NOTE_G4, NOTE_F4, NOTE_DS4, NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_AS4, NOTE_C5, NOTE_F4,
NOTE_D5, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_C5, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_C4,
NOTE_AS3,NOTE_none, NOTE_AS4, NOTE_AS4, NOTE_A4, NOTE_G4,NOTE_none, NOTE_G4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_AS4,NOTE_none,
NOTE_D4, NOTE_DS4, NOTE_F4, NOTE_none, NOTE_F4, NOTE_DS4, NOTE_F4, NOTE_G4,NOTE_none, NOTE_G4, NOTE_F4, NOTE_AS4, NOTE_AS4, NOTE_C5, NOTE_D5, NOTE_D5,
NOTE_D5, NOTE_D5, NOTE_D5, NOTE_C5, NOTE_D5, NOTE_DS5, NOTE_DS5, NOTE_DS5, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_C5, NOTE_AS4,NOTE_none
};
const int delayTime [] = {
  d_2,d_4,d_4,d_4,d_8_h,d_16,d_2,d_4_h,d_8,d_4,d_4,d_2_h,d_4,
  d_4_h,d_8,d_2,d_4,d_8_h,d_16,d_2,d_4_h,d_8,d_4,d_4,d_2_h,d_4,
  d_2,d_4,d_4,d_4,d_4,d_2,d_2,d_4,d_4,d_4,d_4,d_4,d_8_h,d_16,
  d_2,d_8,d_8,d_8,d_8,d_2,d_4,d_4,d_2,d_4,d_4,d_2_h,d_4,
  d_8_h,d_16,d_8,d_8,d_2,d_8_h,d_16,d_8,d_8,d_2,d_4_h,d_8,d_4,d_4,d_2_h,d_4,
  d_2,d_8,d_8,d_8,d_8,d_2_h,d_8_h,d_16,d_4_h,d_8,d_4,d_4,d_2_h,d_4
};
const int BzPIN = 10;
const int BtPIN = 2;

const int pin[8] = {3,4,5,6,7,8,9,11};

int lights[7][8] = {0,};
bool music_play = true;

void buttonPressed(){
  music_play = music_play ? false:true;
}

void setup(){
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lights[0][0] = 0;
  lights[0][1] = 0;
  lights[0][2] = 1;
  lights[0][3] = 1;
  lights[0][4] = 1;
  lights[0][5] = 1;
  lights[0][6] = 1;
  lights[0][7] = 1;
  // 시 플랫
  lights[1][0] = 0;
  lights[1][1] = 0;
  lights[1][2] = 0;
  lights[1][3] = 1;
  lights[1][4] = 1;
  lights[1][5] = 0;
  lights[1][6] = 1;
  lights[1][7] = 0;
  // 도
  lights[2][0] = 1;
  lights[2][1] = 1;
  lights[2][2] = 1;
  lights[2][3] = 0;
  lights[2][4] = 1;
  lights[2][5] = 1;
  lights[2][6] = 1;
  lights[2][7] = 0;
  // 라
  lights[2][0] = 1;
  lights[2][1] = 1;
  lights[2][2] = 1;
  lights[2][3] = 0;
  lights[2][4] = 1;
  lights[2][5] = 1;
  lights[2][6] = 1;
  lights[2][7] = 0;
  // 라
  lights[3][0] = 1;
  lights[3][1] = 0;
  lights[3][2] = 1;
  lights[3][3] = 1;
  lights[3][4] = 1;
  lights[3][5] = 1;
  lights[3][6] = 1;
  lights[3][7] = 0;
  // 솔
  lights[4][0] = 1;
  lights[4][1] = 0;
  lights[4][2] = 0;
  lights[4][3] = 0;
  lights[4][4] = 1;
  lights[4][5] = 1;
  lights[4][6] = 1;
  lights[4][7] = 0;
  // 파
  lights[5][0] = 0;
  lights[5][1] = 1;
  lights[5][2] = 1;
  lights[5][3] = 1;
  lights[5][4] = 1;
  lights[5][5] = 0;
  lights[5][6] = 1;
  lights[5][7] = 0;
  // 레
  lights[6][0] = 1;
  lights[6][1] = 0;
  lights[6][2] = 0;
  lights[6][3] = 1;
  lights[6][4] = 1;
  lights[6][5] = 1;
  lights[6][6] = 1;
  lights[6][7] = 1;
  // 미 플랫
    
  pinMode(BzPIN,OUTPUT);
  pinMode(BtPIN,INPUT);
  attachInterrupt(digitalPinToInterrupt(BtPIN),buttonPressed,RISING);
  for(int i = 0;i<8;i++){
    pinMode(pin[i],OUTPUT);
  }
}

void loop(){
  int i = 0;
  while(1){
    if(music_play){
      melody[i] != 0 ? tone(BUZ,melody[i]) : noTone(BUZ);
      int now = 0;
      switch (melody[i]){
        case NOTE_AS4:
        case NOTE_AS3:
          now = 0;
          break;
        case NOTE_C5:
        case NOTE_C4:
          now = 1;
          break;
        case NOTE_A4:
          now=2;
          break;
        case NOTE_G4:
          now=3;
          break;
        case NOTE_F4:
          now=4;
          break;
        case NOTE_D4:
        case NOTE_D5:
          now=5;
          break;
        case NOTE_DS5:
        case NOTE_DS4:
          now=6;
          break;
        case NOTE_none:
          now=10;
          break;
      }
      for(int j = 0;j<8;j++){
        if(now==10){
          for(int i = 0;i<8;i++){
            digitalWrite(pin[i],LOW);
          }
        }else{
           if(lights[now][j]){
          digitalWrite(pin[j],HIGH);
        }else{
          digitalWrite(pin[j],LOW);
        }
       
        }
       
      }
      lcd.setCursor(0,0);
      lcd.print(melody[i]);
      delay(delayTime[i]);
      lcd.clear();
      i++;
    }else{
      noTone(BUZ);
      for(int j = 0;j<8;j++){
        digitalWrite(pin[j],LOW);
      }
    }
    if(i == sizeof(melody)/sizeof(melody[0])) break;
  }
  

}
