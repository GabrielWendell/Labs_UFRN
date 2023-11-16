/*
 *
 * 
 *
*/

#include "U8glib.h"
#include <SPI.h>
#include <Wire.h>
#include <DS3231.h>

#define LOG_PERIOD 15000  //Logging period in milliseconds, recommended value 15000-60000.
#define MAX_PERIOD 60000  //Maximum logging period without modifying this sketch
#define led 9  //


U8GLIB_NHD_C12864 u8g(8, 7, 6, 5, 4);  // SPI Com: SCK = 8, MOSI = 7, CS = 6, RS = 5, RST = 4
DS3231  rtc(SDA, SCL);

unsigned long counts;     //variable for GM Tube events
unsigned long cpm;        //variable for CPM
float dose;               //variable for effective dose
float percent;             //variable for percent 
unsigned int multiplier;  //variable for calculation CPM in this sketch
unsigned long previousMillis;  //variable for time measurement

String(dose_out) = String();
String(percent_out) = String();
String(CPM_out) = String();
String(TIME) = String();
String(TEMP) = String();
String(condition) = String();


String(LED) = String("OFF");                   //背光控制

void tube_impulse(){       //subprocedure for capturing events from Geiger Kit
  counts++;
}

void setup(){             //setup subprocedure
  counts = 0;
  cpm = 0;
  dose = 0;
  multiplier = MAX_PERIOD / LOG_PERIOD;      //calculating multiplier, depend on your log period
  attachInterrupt(0, tube_impulse, FALLING); //define external interrupts 
  
  u8g.setRot180();
  u8g.setColorIndex(255);
  pinMode(led, OUTPUT);

  rtc.begin();
  // 第一次設定寫入 DS1302 RTC時鐘，之後可以加上註解
  //  rtc.setDOW(SUNDAY);         // 設定每週星期幾？
  //  rtc.setTime(20, 16, 30);     // 設定24小時時間 20:16:30 
  //  rtc.setDate(19, 3, 2017);   // 設定日期(日, 月, 年)
}

void loop(){                                 //main cycle
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > LOG_PERIOD){
    previousMillis = currentMillis;
    cpm = counts * multiplier;
    dose = cpm / 151.0;
    percent = (dose / 0.274) * 100;

    if(dose<=0.34){
      condition = String("Safety!");
    }

    else if(0.34<dose<=1.0){
      condition = String("Warning!");
    }
    
    else if(dose>1.0){
      condition = String("Dangerous!");
    }
    
    CPM_out = String("CPM: ") + cpm + String("        ") + condition;
    dose_out = String("dose: ") + dose + String(" uSv/h");
    percent_out = percent + String("% of World Average!");
    TIME = rtc.getDOWStr() + String(" ") + rtc.getDateStr() + String(" ") + rtc.getTimeStr();
    TEMP = String("Temperature: ") + rtc.getTemp() + String(" C");

    
    counts = 0;
    if(LED == String("ON")){
      digitalWrite(led, 1); 
    }

    else if(LED == String("OFF")){
      digitalWrite(led, 0); 
    }
    
      u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_7x14B);
    u8g.setPrintPos(0, 12);
    u8g.print(String("Geiger counter"));
    u8g.setFont(u8g_font_04b_03);
    u8g.setPrintPos(0, 19);
    u8g.print(TIME);  
    u8g.setFont(u8g_font_5x7);
    u8g.setPrintPos(0, 26);
    u8g.print(TEMP); 
    u8g.setFont(u8g_font_7x14B);
    u8g.setPrintPos(0, 33);
    u8g.print(String("--------------------"));
    u8g.setFont(u8g_font_helvR08);
    u8g.setPrintPos(0, 40);
    u8g.print(CPM_out);    
    u8g.setPrintPos(0, 50);
    u8g.print(dose_out);
    u8g.setPrintPos(0, 60);
    u8g.print(percent_out);
    


    
  } while( u8g.nextPage() );
  delay(1000);

    counts = 0;
  }
  
}