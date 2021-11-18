#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include "font.h"
#include "kalku.h"

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

#define TFT_GREY 0x1082// New colour
#define color 0x2786
#define color2 0x0C16

const int pwmFreq = 5000;
const int pwmResolution = 8;
const int pwmLedChannelTFT = 0;
String s="";
int buttons[16]={36,33,25,26,37,38,27,21,22,17,13,12,15,2,32,39};
String letters[16]={"0","1","2","3","4","5","6","7","8","9","+","-","*","/","=","."};
int pres=0;
String whole="";
String number;
float n,n2,r=0;
int operation=0;

void setup(void) {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);
 tft.pushImage(0,0,240,135,kalku);
 tft.fillRect(0,34,240,44,TFT_GREY);
  pinMode(0,INPUT_PULLUP);

  for(int i=0;i<16;i++){
     if(buttons[i]<3633)
     
     pinMode(buttons[i],INPUT_PULLUP);
  }

  ledcSetup(pwmLedChannelTFT, pwmFreq, pwmResolution);
  ledcAttachPin(TFT_BL, pwmLedChannelTFT);
  ledcWrite(pwmLedChannelTFT, 100);
  
  tft.setTextColor(TFT_GREEN);
  tft.setFreeFont(&DSEG7_Classic_Bold_32);


}

int res=1;
void loop() {

runCalc();

}

void runCalc()
{
  if(digitalRead(0)==0)
  reset();

for(int i=0;i<16;i++){
res=1;
   if(buttons[i]>33)
      { 
      if(analogRead(buttons[i])<3000)
      res=0;  
      }else{if(digitalRead(buttons[i])==0) res=0;}

if(res==0){
  if(pres==0)
  {
  pres=1;  
  if(i<10){
  number=number+String(i);
  }
  if(i==15)
  number=number+".";
//if +
  if(buttons[i]==13){
  n=number.toFloat();
  operation=1;
  
  number="";
  }
// if -
    if(buttons[i]==12){
  n=number.toFloat();
  operation=2;
  
  number="";
  }

  // if -*
    if(buttons[i]==15){
  n=number.toFloat();
  operation=3;
  
  number="";
  }
//if  /
      if(buttons[i]==2){
  n=number.toFloat();
  operation=4;
  
  number="";
  }
//if =
    if(buttons[i]==32){
      if(operation==1)
      n=n+number.toFloat();
      if(operation==2)
      n=n-number.toFloat();
      if(operation==3)
      n=n*number.toFloat();
      if(operation==4)
      n=n/number.toFloat();
  
 

               int p=n*10.00;
               if(p%10==0)
               number=String(p/10);
               else
               number=String(n);
               tft.setTextColor(color2,TFT_BLACK);
               tft.drawString(number,12,110,4);
               tft.setTextColor(color,TFT_BLACK);
                
  }
   whole=whole+letters[i];
   tft.fillRect(0,34,240,44,TFT_GREY);
   
   tft.setTextColor(color2,TFT_BLACK);
   tft.drawString(whole,12,82,4);
   tft.setTextColor(color,TFT_GREY);
   tft.drawString(number,6,40);

  delay(300);
  }
}else{ pres=0;}
}
 }

 void reset()
 {
  tft.pushImage(0,0,240,135,kalku);
  tft.fillRect(0,34,240,44,TFT_GREY);
  number="";
  whole="";
  }
