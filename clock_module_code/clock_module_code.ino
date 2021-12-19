#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"
//#include <DS3231.h>
#include <OneButton.h>
#include "LowPower.h"

//buttons pd2(lightA btn) pd3 pd4
//leds pd5(led2) pd6(led1)
#define BUTTON_PIN 1  //PD3
   OneButton btn = OneButton(
        BUTTON_PIN,  // Input pin for the button
        true,        // Button is active LOW
        true         // Enable internal pull-up resistor 
      );
 #define LIGHT_A_BUTTON 32  //PD3
   OneButton btn_A = OneButton(
        LIGHT_A_BUTTON,  // Input pin for the button
        true,        // Button is active LOW
        true         // Enable internal pull-up resistor 
      );
#define LIGHT_B_BUTTON 2  //PD3
   OneButton btn_B = OneButton(
        LIGHT_B_BUTTON,  // Input pin for the button
        true,        // Button is active LOW
        true         // Enable internal pull-up resistor 
      );
////output pins LEDS
//#define led1 10
//#define led2  9

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

/*this code*/

//if to allow serial printing of statement when needed
#define DEBUG 0//keep zero to save space on the atmega chip
#if DEBUG ==1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else 
#define debug(x)
#define debugln(x)
#endif


//instantiate the U8g2lib class
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 


char time_data[11];
char date_data[11];
char day_data[13];
//flags used to set the time
long on_time =30000;//30seconds on time duration for the screen

//flags and variables for time setting
//int incrementor = 0;//will be used to increment whatever variable that is active
int  flag_settime=0;
int  flag_location=0;

 struct mytime{
  int my_seconds;
  int my_minutes;
  int my_hour;
  int my_date;
  int my_month;
  int my_year;
  int my_day;
  };
  //global sturct variable
 struct mytime thistime;

long current_time=0;
void wakeUp()
{
  current_time=millis();
    // Just a handler for the pin interrupt.
}
void toggle_A(){
  digitalWrite(10, !digitalRead(10));
  }
  
void toggle_B(){
  digitalWrite(9, !digitalRead(9));
  }
 
void setup() {
  // put your setup code here, to run once:
   u8g2.begin();
   u8g2.clearBuffer();
   //u8g2.setFont(u8g2_font_logisoso28_tr);
   u8g2.setFont(u8g2_font_freedoomr25_mn);//selecting the appropriate font choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   if (! rtc.begin()) {
    debugln("Couldn't find RTC");
    while (1);
  }
   //this line of code is to be uploaded once and the removed after.
   //once this line is removed, compile and upload the code once again to ensure that the RTC datetime is not reset
   //everytime the MCU wakes up from sleep
   if (rtc.lostPower()) {
    debugln("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    //button use setup
    btn.setDebounceTicks(30);
    btn.setClickTicks(250);
    btn. setPressTicks(800);
 //CLICK HANDLES 
    btn.attachClick(handleClick);
    btn_A.attachClick(toggle_A);
    btn_B.attachClick(toggle_B);
      
      btn.attachDoubleClick([]() {
      debugln("Double Pressed!");
      if (flag_location<7){
          flag_location++;
          }
          else{
            flag_location=0; 
          }
    });
    btn.attachLongPressStart(handleLongpress);
  //other
   // pinMode(BUTTON_PIN, INPUT_PULLUP);
    /*attachInterrupt(digitalPinToInterrupt(Time_Set), buttonPressed, FALLING);
    -*/
   pinMode(10, OUTPUT);//led 1
   pinMode(9, OUTPUT);//led 2
 
    debugln("starting");
}
//int set_flag=0;
void loop() {
  // put your main code here, to run repeatedly:
  //we go to sleep
  attachInterrupt(1, wakeUp, LOW);//attach interrupt pin 1 of the atmeaga
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  detachInterrupt(0);
   btn.tick();
   do{
   if(flag_settime==1)
   {
    time_setter();    //save the current time in the global struct
    //set_flag=1;     //this flag is used to indicate that time will need to be saved to the rtc chip after setting process is done
    
    //the we move on to display and change the different time variables of the rtc and save the in the same struct variable
    do{
      //here we will show all the variables that we will use to set time on the rtc
      show_location(flag_location);
      
      }while(flag_settime!=0);
      
    rtc.adjust(DateTime(thistime.my_year, thistime.my_month, thistime.my_date, thistime.my_hour, thistime.my_minutes, thistime.my_seconds)); 
    //update time on exiting the loop
    }
    
    //function to display the time, day and date /....normal operation area
   gettime();
   u8g2.clearBuffer();
   u8g2.drawStr(31,4,day_data);
   u8g2.drawStr(31,18,time_data);  // write data to the internal memory
   u8g2.drawStr(31,28,date_data);
   u8g2.sendBuffer();         // transfer internal memory to the display
   }while(millis()-current_time<=on_time);
   
}
void gettime(){
  DateTime now = rtc.now();
 // int myhour=now.minute();
  sprintf(time_data, "%d:%d:%d",now.hour(),now.minute(),now.second());
  sprintf(date_data, "%d/%d/%d",now.year(),now.month(),now.day());
  strcpy(day_data, (daysOfTheWeek[now.dayOfTheWeek()]));
}
 void handleClick(){
  if(flag_settime==1){
   increment(flag_location);
  }
  
  }
 void handleLongpress(){
  //long pressing the time button gets you here
  // it enters the time setting mode and if you long press again
  //you leave time setting mode
  flag_settime= (flag_settime==1)?0:1;
  
 }

 void time_setter(){
  //this function is called once the code enters time setting mode
  DateTime now = rtc.now();
  thistime.my_seconds=now.second();
  thistime.my_minutes=now.minute();
  thistime.my_hour=now.hour();
  thistime.my_date=now.day();
  thistime.my_month=now.month();
  thistime.my_year=now.year();
  thistime.my_day=now.dayOfTheWeek();
  }
void increment(int location){       //function to increment only the active variable
    //we already got the current time of the rtc module
    //we manipulate it then here based on the button pressed
    // char *buf;
   if (location==0){
     if(thistime.my_seconds>60){thistime.my_seconds=0;}
     else {thistime.my_seconds=thistime.my_seconds+1;}
   }
   else if (location==1){
     if(  thistime.my_minutes>60){thistime.my_minutes=0;}
     else {thistime.my_minutes=thistime.my_minutes+1;}
    }
     else if (location==2){
     if(  thistime.my_hour>23){thistime.my_hour=0;}
     else {thistime.my_hour=thistime.my_hour+1;}
   }
        else if (location==3){
    if(  thistime.my_date>31){thistime.my_date=0;}
     else {thistime.my_date=thistime.my_date+1;}
    }
        else if (location==4){
     if(  thistime.my_month>31){thistime.my_month=0;}
     else {thistime.my_month=thistime.my_month+1;}
     }
        else if (location==5){
     if(  thistime.my_year>2050){thistime.my_year=0;}
     else {thistime.my_year=thistime.my_year+1;}
     }
         else if (location==6){
     if(  thistime.my_day>31){thistime.my_day=0;}
     else {thistime.my_day=thistime.my_day+1;}
      }
    }
 void show_location(int location){
  //funtion to show the active variable.
  char *buf; //local buffer to store our character arrat and dispaly it on the screen
    if (location==0){
     u8g2.clearBuffer();
     u8g2.drawStr(3,24,"sec");
     u8g2.drawStr(31,24,itoa(thistime.my_seconds, buf,3));  // write data to the internal memory
     u8g2.sendBuffer();         // transfer internal memory to the display
      }
   else if (location==1){
     u8g2.clearBuffer();
     u8g2.drawStr(3,24,"min");
     u8g2.drawStr(31,24,itoa(thistime.my_minutes,buf,3));  // write data to the internal memory
     u8g2.sendBuffer();         // transfer internal memory to the display
      }
     else if (location==2){
     u8g2.clearBuffer();
     u8g2.drawStr(3,24,"hrs");
     u8g2.drawStr(31,24,itoa(thistime.my_hour,buf,3));  // write data to the internal memory
     u8g2.sendBuffer();         // transfer internal memory to the display
      }
        else if (location==3){
     u8g2.clearBuffer();
     u8g2.drawStr(3,24,"date");
     u8g2.drawStr(31,24,itoa(thistime.my_date,buf,3));  // write data to the internal memory
     u8g2.sendBuffer();         // transfer internal memory to the display
      }
        else if (location==4){
     u8g2.clearBuffer();
     u8g2.drawStr(3,24,"month");
     u8g2.drawStr(31,24,itoa(thistime.my_month,buf,3));  // write data to the internal memory
     u8g2.sendBuffer();         // transfer internal memory to the display
      }
        else if (location==5){
     u8g2.clearBuffer();
     u8g2.drawStr(3,24,"year");
     u8g2.drawStr(31,24,itoa(thistime.my_year,buf,5));  // write data to the internal memory
     u8g2.sendBuffer();         // transfer internal memory to the display
      }
         else if (location==6){
     u8g2.clearBuffer();
     u8g2.drawStr(3,24,"day");
     u8g2.drawStr(31,24,daysOfTheWeek[thistime.my_day]);  // write data to the internal memory
     u8g2.sendBuffer();         // transfer internal memory to the display
      }
  }
