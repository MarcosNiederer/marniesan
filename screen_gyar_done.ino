#include <SPI.h> // library for communication between SPI devices
#include <Wire.h> //library for communication for I2C / TWI devices
#include <Adafruit_GFX.h> // core graphics library for display
#include <Adafruit_HX8357.h> //tft screen specific graphics library
#include <TFT_eSPI.h> 
#include <Adafruit_STMPE610.h> // library for resistive touch screen controller breakout
//fonts for text
#include <Fonts/FreeSerifBold18pt7b.h>
#include <Fonts/FreeSerifBold12pt7b.h>
#include <Fonts/FreeSansBoldOblique24pt7b.h>
#include <Fonts/FreeSerifBold9pt7b.h>

//define screen parameters
#define TS_MINX 3800
#define TS_MINY 100
#define TS_MAXX 100
#define TS_MAXY 3750

//define screen pins & other screen details
#define STMPE_CS 32
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);
#define TFT_CS 15
#define TFT_DC 33
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC);

#include "config.h" //includes the config file for WIFI connection, Adafruit IO connection, etc. 

#define FEED_OWNER "axelmagnus" //define owner of feeds (Adafruit IO)
AdafruitIO_Feed *rainfall      = io.feed("ab-weather.rainfall", FEED_OWNER); //feed accessing
AdafruitIO_Feed *windspeed     = io.feed("ab-weather.windspeed", FEED_OWNER);
AdafruitIO_Feed *winddirection = io.feed("ab-weather.winddirection", FEED_OWNER);

int currentpage;


//following void functions are for designing look of different menus

void drawHome()  //draws home menu
{ //menu design
  tft.fillRoundRect(90, 50, 300, 50, 8, HX8357_BLACK);
  tft.drawRoundRect(90, 50, 300, 50, 8, HX8357_WHITE);
  tft.setCursor(120, 80);
  tft.setFont(&FreeSerifBold18pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("Weatherstation");

  tft.fillRoundRect(90, 200, 300, 50, 8, HX8357_BLACK);
  tft.drawRoundRect(90, 200, 300, 50, 8, HX8357_WHITE);
  tft.setCursor(120, 235);
  tft.setFont(&FreeSerifBold18pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("Awning control");
}

void wst()  //draws weatherstation menu
{ //menu design
  tft.fillScreen(HX8357_BLUE);
  tft.fillRoundRect(30, 85, 200, 100, 8, HX8357_BLACK);
  tft.drawRoundRect(30, 85, 200, 100, 8, HX8357_WHITE);
  tft.setCursor(50, 170);
  tft.setFont(&FreeSerifBold9pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("Current Windspeed");

  tft.fillRoundRect(30, 200, 200, 115, 8, HX8357_BLACK);
  tft.drawRoundRect(30, 200, 200, 115, 8, HX8357_WHITE);
  tft.setCursor(35, 300);
  tft.setFont(&FreeSerifBold9pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("Current Wind Direction");

  tft.fillRoundRect(260, 20, 200, 100, 8, HX8357_BLACK);
  tft.drawRoundRect(260, 20, 200, 100, 8, HX8357_WHITE);
  tft.setCursor(300, 110);
  tft.setFont(&FreeSerifBold9pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("Current Rainfall");
  
  tft.fillRoundRect(0, 0, 80, 80, 8, HX8357_BLACK);
  tft.drawRoundRect(0, 0, 80, 80, 8, HX8357_WHITE);
  tft.setCursor(5, 45);
  tft.setFont(&FreeSerifBold12pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("BACK");
}

void awnbtn() //draws awning control menu
{ //menu design
  tft.fillScreen(HX8357_BLUE);
  tft.fillRoundRect(80, 125, 90, 90, 8, HX8357_BLACK);
  tft.drawRoundRect(80, 125, 90, 90, 8, HX8357_WHITE);
  tft.setCursor(110, 175);
  tft.setFont(&FreeSerifBold12pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("UP");

  tft.fillRoundRect(195, 125, 90, 90, 8, HX8357_BLACK);
  tft.drawRoundRect(195, 125, 90, 90, 8, HX8357_WHITE);
  tft.setCursor(200, 175);
  tft.setFont(&FreeSerifBold12pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("PAUSE");

  tft.fillRoundRect(310, 125, 90, 90, 8, HX8357_BLACK);
  tft.drawRoundRect(310, 125, 90, 90, 8, HX8357_WHITE);
  tft.setCursor(315, 175);
  tft.setFont(&FreeSerifBold12pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("DOWN");

  tft.fillRoundRect(0, 0, 80, 80, 8, HX8357_BLACK);
  tft.drawRoundRect(0, 0, 80, 80, 8, HX8357_WHITE);
  tft.setCursor(5, 45);
  tft.setFont(&FreeSerifBold12pt7b);
  tft.setTextColor(HX8357_WHITE);
  tft.print("BACK");
}

//following int functions handle received data

int temp = 0;
void handleMessageTemp(AdafruitIO_Data *data) {
  Serial.print("received temp <-  ");
  Serial.println(data->toInt());
  temp = data->toInt();
}

int rain = 0;
void handleMessageRain(AdafruitIO_Data *data) {
  Serial.print("received rain <-  ");
  Serial.println(data->toInt());
  rain = data->toInt();
}

int wndspd = 0;
void handleMessageWindspeed(AdafruitIO_Data *data) {
  Serial.print("received windspeed <-  ");
  Serial.println(data->toInt());
  wndspd = data->toInt();
}

int wnddir = 0;
void handleMessageWindDirection(AdafruitIO_Data *data) {
  Serial.print("received winddirection <-  ");
  Serial.println(data->toInt());
  wnddir = data->toInt();
}

void setup(void) {

  Serial.begin(115200);
  while (! Serial);
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  //onMessage functions for when data is received
  rainfall->onMessage(handleMessageRain);
  windspeed->onMessage(handleMessageWindspeed);
  winddirection->onMessage(handleMessageWindDirection);

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText());
  //gets data
  rainfall->get();
  windspeed->get();
  winddirection->get();

  //starts screen
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
    { //transitions between main menu and weatherstation menu
      if ((x >= 90) && (x <= 390)) {
        if ((y >= 50) && (y <= 100)) {
          Serial.println("btn hit");
          currentpage = 1;
          wst();
        }
      }//transitions between main menu and awning control menu
      if ((x >= 90) && (x <= 390)) {
        if ((y >= 200) && (y <= 250)) {
          Serial.println("btn 2 hit");
          currentpage = 2;
          awnbtn();
        }
      }
    }
    if (currentpage == 2) //page 2 is awning control menu
    { //transitions of "back" button in awning control page to main menu
      if ((x >= 0) && (x <= 80)) {
        if ((y >= 0) && (y <= 80)) {
          Serial.println("btn hit");
          currentpage = 0;
          tft.fillScreen(HX8357_BLUE);
          drawHome();
        }
      }
    }

    if (currentpage == 1) //page 1 is weatherstation menu
    { //transitions of "back" button in weatherstation page to main menu
      if ((x >= 0) && (x <= 80)) {
        if ((y >= 0) && (y <= 80)) {
          Serial.println("btn hit");
          currentpage = 0;
          tft.fillScreen(HX8357_BLUE);
          drawHome();
        }
      }
    }
  }
  //prints feed values with its unit
  if (currentpage == 1) {
    tft.setCursor(110, 125);
    tft.print (wndspd);
    tft.setCursor(130, 125);
    tft.print ("m/s");
    tft.setCursor(80, 250);
    tft.print (wnddir);
    tft.setCursor(125, 250);
    tft.print ("degrees");
    tft.setCursor(320, 65);
    tft.print(rain);
    tft.setCursor(340, 65);
    tft.print("mm");

    delay(1000);
    //to avoid values stacking, another template is printed over the last printed value
    tft.fillRoundRect(30, 85, 200, 70, 8, HX8357_BLACK);   
    tft.drawRoundRect(30, 85, 200, 70, 8, HX8357_WHITE);
    tft.fillRoundRect(30, 200, 200, 70, 8, HX8357_BLACK);  
    tft.drawRoundRect(30, 200, 200, 70, 8, HX8357_WHITE);
    tft.fillRoundRect(260, 20, 200, 70, 8, HX8357_BLACK);   
    tft.drawRoundRect(260, 20, 200, 70, 8, HX8357_WHITE);
  }
}
