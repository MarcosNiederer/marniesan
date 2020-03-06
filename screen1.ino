#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_HX8357.h>
#include <Adafruit_STMPE610.h>
#include <Fonts/FreeSerifBold18pt7b.h>
#include <Fonts/FreeSerifBold12pt7b.h>
#include <Fonts/FreeSansBoldOblique24pt7b.h>
#include <Fonts/FreeSerifBold9pt7b.h>

#define TS_MINX 3800
#define TS_MINY 100
#define TS_MAXX 100
#define TS_MAXY 3750

#define STMPE_CS 32
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);
#define TFT_CS 15
#define TFT_DC 33
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC);

#include "config.h"
#define FEED_OWNER "axelmagnus"
AdafruitIO_Feed *rainfall      = io.feed("ab-weather.rainfall", FEED_OWNER);
AdafruitIO_Feed *temperature   = io.feed("ab-weather.temperature", FEED_OWNER);
AdafruitIO_Feed *windspeed     = io.feed("ab-weather.windspeed", FEED_OWNER);
AdafruitIO_Feed *winddirection = io.feed("ab-weather.winddirection", FEED_OWNER);



int currentpage;



void drawHome()  //draws home menu
{
  tft.fillRoundRect(90, 50, 300, 50, 8, HX8357_BLACK);    //weatherstation menu button
  tft.drawRoundRect(90, 50, 300, 50, 8, HX8357_WHITE);
  tft.setCursor(120, 80);
  tft.setFont(&FreeSerifBold18pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("Weatherstation");

  tft.fillRoundRect(90, 200, 300, 50, 8, HX8357_BLACK);   //awning control menu button
  tft.drawRoundRect(90, 200, 300, 50, 8, HX8357_WHITE);
  tft.setCursor(120, 235);
  tft.setFont(&FreeSerifBold18pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("Awning control");
}

void wst()  //draws weatherstation menu
{
  tft.fillScreen(HX8357_BLUE);        //temperature
  tft.fillRoundRect(30, 100, 200, 80, 8, HX8357_BLACK);
  tft.drawRoundRect(30, 100, 200, 80, 8, HX8357_WHITE);
  tft.setCursor(60, 150);
  tft.setFont(&FreeSerifBold12pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("Temperature");

  tft.fillRoundRect(30, 200, 200, 80, 8, HX8357_BLACK);   //rainfall button
  tft.drawRoundRect(30, 200, 200, 80, 8, HX8357_WHITE);
  tft.setCursor(85, 250);
  tft.setFont(&FreeSerifBold12pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("Rainfall");

  tft.fillRoundRect(260, 200, 200, 80, 8, HX8357_BLACK); // wind direction button
  tft.drawRoundRect(260, 200, 200, 80, 8, HX8357_WHITE);
  tft.setCursor(280, 250);
  tft.setFont(&FreeSerifBold12pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("Wind Direction");

  tft.fillRoundRect(260, 100, 200, 80, 8, HX8357_BLACK);   //wind speed button
  tft.drawRoundRect(260, 100, 200, 80, 8, HX8357_WHITE);
  tft.setCursor(290, 150);
  tft.setFont(&FreeSerifBold12pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("Wind Speed");

  tft.fillRoundRect(0, 0, 80, 80, 8, HX8357_BLACK);  //back button
  tft.drawRoundRect(0, 0, 80, 80, 8, HX8357_WHITE);
  tft.setCursor(5, 45);
  tft.setFont(&FreeSerifBold12pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("BACK");
}

void temperaturescreen()  //draws temperature menu
{
  tft.fillRoundRect(400, 0, 80, 80, 8, HX8357_BLACK);   //back button
  tft.drawRoundRect(400, 0, 80, 80, 8, HX8357_WHITE);
  tft.setCursor(405, 45);
  tft.setFont(&FreeSerifBold12pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("BACK");

  tft.fillRoundRect(80, 100, 150, 80, 8, HX8357_BLACK);   //live temp template
  tft.drawRoundRect(80, 100, 150, 80, 8, HX8357_WHITE);
  tft.setCursor(100, 125);
  tft.setFont(&FreeSerifBold12pt7b);
  tft.setTextColor(HX8357_WHITE);



}

void rainfallscreen()  //draws rainfall menu
{
  tft.fillRoundRect(400, 0, 80, 80, 8, HX8357_BLACK);   //back button
  tft.drawRoundRect(400, 0, 80, 80, 8, HX8357_WHITE);
  tft.setCursor(405, 45);
  tft.setFont(&FreeSerifBold12pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("BACK");
}
void windspeedscreen()  //draws windspeed menu
{
  tft.fillRoundRect(400, 0, 80, 80, 8, HX8357_BLACK);   //back button
  tft.drawRoundRect(400, 0, 80, 80, 8, HX8357_WHITE);
  tft.setCursor(405, 45);
  tft.setFont(&FreeSerifBold12pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("BACK");
}
void winddirectionscreen()  //draws windspeed menu
{
  tft.fillRoundRect(400, 0, 80, 80, 8, HX8357_BLACK);   //back button
  tft.drawRoundRect(400, 0, 80, 80, 8, HX8357_WHITE);
  tft.setCursor(405, 45);
  tft.setFont(&FreeSerifBold12pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("BACK");
}
void awnbtn() //draws awning control menu
{
  tft.fillScreen(HX8357_BLUE);
  tft.fillRoundRect(80, 125, 90, 90, 8, HX8357_BLACK);   // up button
  tft.drawRoundRect(80, 125, 90, 90, 8, HX8357_WHITE);
  tft.setCursor(110, 175);
  tft.setFont(&FreeSerifBold12pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("UP");

  tft.fillRoundRect(195, 125, 90, 90, 8, HX8357_BLACK);   //pause button
  tft.drawRoundRect(195, 125, 90, 90, 8, HX8357_WHITE);
  tft.setCursor(200, 175);
  tft.setFont(&FreeSerifBold12pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("PAUSE");

  tft.fillRoundRect(310, 125, 90, 90, 8, HX8357_BLACK);   // down button
  tft.drawRoundRect(310, 125, 90, 90, 8, HX8357_WHITE);
  tft.setCursor(315, 175);
  tft.setFont(&FreeSerifBold12pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("DOWN");

  tft.fillRoundRect(0, 0, 80, 80, 8, HX8357_BLACK);   //back button
  tft.drawRoundRect(0, 0, 80, 80, 8, HX8357_WHITE);
  tft.setCursor(5, 45);
  tft.setFont(&FreeSerifBold12pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("BACK");
}

int temp = 0; // tdest
void handleMessageTemp(AdafruitIO_Data *data) { // tdest
  Serial.print("received temp <-  ");
  Serial.println(data->toInt());
  temp = data->toInt();
}

int rain = 0; // tdest
void handleMessageRain(AdafruitIO_Data *data) { // tdest
  Serial.print("received rain <-  ");
  Serial.println(data->toInt());
  rain = data->toInt();
}

int wndspd = 0; // tdest
void handleMessageWindspeed(AdafruitIO_Data *data) { // tdest
  Serial.print("received windspeed <-  ");
  Serial.println(data->toInt());
  wndspd = data->toInt();
}

int wnddir = 0; // tdest
void handleMessageWindDirection(AdafruitIO_Data *data) { // tdest
  Serial.print("received winddirection <-  ");
  Serial.println(data->toInt());
  wnddir = data->toInt();
}

void setup(void) {
  Serial.begin(115200);
  while (! Serial);
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  /* rainfall->onMessage(handleMessage);*/  rainfall->onMessage(handleMessageRain);
  /*temperature->onMessage(handleMessage);*/ temperature->onMessage(handleMessageTemp);
  /* windspeed->onMessage(handleMessage);*/    windspeed->onMessage(handleMessageWindspeed);
  /* winddirection->onMessage(handleMessage);*/ winddirection->onMessage(handleMessageWindDirection);
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText());
  rainfall->get();
  temperature->get();
  windspeed->get();
  winddirection->get();
  //Serial.println(temperature->get());
  tft.begin();
  if (!ts.begin()) {
    Serial.println("Unable to start touchscreen.");
  }
  else {
    Serial.println("Touchscreen started.");
  }
  tft.fillScreen(HX8357_BLUE);
  tft.setRotation(1);
  currentpage = 0;
  drawHome();
}

void loop() {
  io.run();

  if (!ts.bufferEmpty())
  {

    TS_Point p = ts.getPoint();     // Read touchscreen

    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.height());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.width());
    int y = p.x;
    int x = p.y;
    Serial.print("x value");
    Serial.print(x);
    Serial.print("\t y value");
    Serial.println(y);

    if (currentpage == 0)
    {

      if ((x >= 90) && (x <= 390)) {
        if ((y >= 50) && (y <= 100)) {    //transitions between first menu and weatherstation menu
          Serial.println("btn hit");
          currentpage = 1;
          wst();
        }
      }
      if ((x >= 90) && (x <= 390)) {
        if ((y >= 200) && (y <= 250)) {  //transitions between first menu and awning control menu
          Serial.println("btn 2 hit");
          currentpage = 2;
          awnbtn();
        }
      }

    }


    if (currentpage == 2) //page 2 is awning control menu
    {
      if ((x >= 0) && (x <= 80)) {
        if ((y >= 0) && (y <= 80)) {
          Serial.println("btn hit");   //// transitions of "back" button in awning control page to home2
          currentpage = 0;
          tft.fillScreen(HX8357_BLUE);
          drawHome();
        }
      }

    }

    if (currentpage == 1)  // page 1 is weatherstation menu
    {

      if ((x >= 0) && (x <= 80)) {  // transitions of "back" button in weatherstation page to home
        if ((y >= 0) && (y <= 80)) {
          Serial.println("btn hit");
          currentpage = 0;
          tft.fillScreen(HX8357_BLUE);
          drawHome();
        }
      }
      if ((x >= 30 ) && (x <= 230)) { //transitions between wst menu to temp menu
        if ((y >= 100) && (y <= 180)) {
          Serial.println("btn hit");
          currentpage = 3;
          tft.fillScreen(HX8357_BLUE);
          temperaturescreen();
        }
      }
      if ((x >= 30 ) && (x <= 230)) { //transitions between wst menu to rainfall menu
        if ((y >= 200) && (y <= 280)) {
          Serial.println("btn hit");
          currentpage = 4;
          tft.fillScreen(HX8357_BLUE);
          rainfallscreen();
        }
      }
      if ((x >= 260) && (x <= 360)) { //transitions between wst menu to windspeed menu
        if ((y >= 100) && (y <= 180)) {
          Serial.println("btn hit");
          currentpage = 5;
          tft.fillScreen(HX8357_BLUE);
          windspeedscreen();
        }
      }
      if ((x >= 260) && (x <= 360)) { //transitions between wst menu to windspeed menu
        if ((y >= 200) && (y <= 280)) {
          Serial.println("btn hit");
          currentpage = 6;
          tft.fillScreen(HX8357_BLUE);
          winddirectionscreen();
        }
      }
    }



    if (currentpage == 3) //temperature menu
    {
      if ((x >= 400) && (x <= 480)) {  // transitions of "back" button in temperature menu to wst menu
        if ((y >= 0) && (y <= 80)) {
          Serial.println("btn hit");
          currentpage = 1;
          tft.fillScreen(HX8357_BLUE);
          wst();

        }
      }
      
        
    
      tft.print(temp);
    }
    if (currentpage == 4) //rainfall menu
    {
      if ((x >= 400) && (x <= 480)) {  // transitions of "back" button in rainfall menu to wst menu
        if ((y >= 0) && (y <= 80)) {
          Serial.println("btn hit");
          currentpage = 1;
          tft.fillScreen(HX8357_BLUE);
          wst();
        }
      }
      tft.print(rain);
    }
    if (currentpage == 5) //windspeed menu
    {
      if ((x >= 400) && (x <= 480)) {  // transitions of "back" button in windspeed menu to wst menu
        if ((y >= 0) && (y <= 80)) {
          Serial.println("btn hit");
          currentpage = 1;
          tft.fillScreen(HX8357_BLUE);
          wst();
        }
      }
      tft.print(wndspd);
    }
    if (currentpage == 6) //windspeed menu
    {
      if ((x >= 400) && (x <= 480)) {  // transitions of "back" button in winddirection menu to wst menu
        if ((y >= 0) && (y <= 80)) {
          Serial.println("btn hit");
          currentpage = 1;
          tft.fillScreen(HX8357_BLUE);
          wst();
        }
      }
      if (wnddir){
        
      tft.print(wndrie);
      }
      
      if (winddirection receive){
        tft.print (wnddir)
        }
      
    }
  }
}
