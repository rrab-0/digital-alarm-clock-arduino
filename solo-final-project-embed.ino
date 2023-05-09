// TODO:
// - make alarm
// - implement light sensor to check brightness
// - if can fix too much memory usage
//  - problem is at library itself "MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);"
// //- display clock, calendar properly
// //- make text scroll

// Arduino DS3232RTC Library
// https://github.com/JChristensen/DS3232RTC
// Copyright (C) 2018 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
//
// Example sketch to display the date and time from a DS3231
// or DS3232 RTC every second. Display the temperature once per
// minute. (The DS3231 does a temperature conversion once every
// 64 seconds. This is also the default for the DS3232.)
//
// Set the date and time by entering the following on the Arduino
// serial monitor:
//  year,month,day,hour,minute,second,
//
// Where
//  year can be two or four digits,
//  month is 1-12,
//  day is 1-31,
//  hour is 0-23, and
//  minute and second are 0-59.
//
// Entering the final comma delimiter (after "second") will avoid a
// one-second timeout and will allow the RTC to be set more accurately.
//
// No validity checking is done, invalid values or incomplete syntax
// in the input will result in an incorrect RTC setting.
//
// Jack Christensen 08Aug2013
#include <MD_Parola.h>
// #include <MD_MAX72xx.h>
#include <SPI.h>

#include <DS3232RTC.h>  // https://github.com/JChristensen/DS3232RTC
#include <Streaming.h>  // https://github.com/janelia-arduino/Streaming
#include <TimeLib.h>    // https://github.com/PaulStoffregen/Time

#include <Wire.h>
#include <time.h>

const uint16_t WAIT_TIME = 1000;

#define LM_35 A0
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CLK_PIN 13
#define DATA_PIN 11
#define CS_PIN 10

MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

DS3232RTC myRTC;

char buffer[60];

void setup() {
  Serial.begin(115200);
  // Serial << F("\n" __FILE__ "\n" __DATE__ " " __TIME__ "\n");
  myRTC.begin();

  // setSyncProvider() causes the Time library to synchronize with the
  // external RTC by calling RTC.get() every five minutes by default.
  setSyncProvider(myRTC.get);
  Serial << F("RTC Sync");
  if (timeStatus() != timeSet) Serial << F(" FAIL!");
  Serial << endl;

  P.begin();
  P.setIntensity(0);
  P.displayClear();
}

void loop() {
  static time_t tLast;
  time_t t;
  tmElements_t tm;

  // check for input to set the RTC, minimum length is 12, i.e. yy,m,d,h,m,s
  if (Serial.available() >= 12) {
    // note that the tmElements_t Year member is an offset from 1970,
    // but the RTC wants the last two digits of the calendar year.
    // use the convenience macros from the Time Library to do the conversions.

    int y = Serial.parseInt();
    if (y >= 100 && y < 1000)
      Serial << F("Error: Year must be two digits or four digits!") << endl;
    else {
      if (y >= 1000)
        tm.Year = CalendarYrToTm(y);
      else  // (y < 100)
        tm.Year = y2kYearToTm(y);
      tm.Month = Serial.parseInt();
      tm.Day = Serial.parseInt();
      tm.Hour = Serial.parseInt();
      tm.Minute = Serial.parseInt();
      tm.Second = Serial.parseInt();
      t = makeTime(tm);
      myRTC.set(t);  // use the time_t value to ensure correct weekday is set
      setTime(t);
      Serial << F("RTC set to: ");
      printDateTime(t);

      // sprintf(buffer, "%d %s %d %d:%d:%d", day(t), monthShortStr(month(t)), _DEC(year(t)), hour(t), minute(t), second(t));
      // P.displayText(buffer, PA_CENTER, 25, 25, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
      // P.displayReset();


      Serial << endl;
      // dump any extraneous input
      while (Serial.available() > 0) Serial.read();
    }
  }

  t = now();
  // sprintf(buffer, "%d.%d.%d > %d %s %d", hour(t), minute(t), second(t), day(t), monthShortStr(month(t)), _DEC(year(t)));
  if (t != tLast) {
    tLast = t;
    // prints calendar and clock
    printDateTime(t);

    // // prints celcius
    // uint8_t c = myRTC.temperature() / 4.;
    // Serial << c << F(" C  ");

    // // from LM35 (celcius)
    // int celcius = analogRead(LM_35);
    // int displayCelcius = celcius * (5.0/1023.0) * 100;
    // Serial << displayCelcius << F(" C");
    // // displays to dot matrix
    // snprintf(buffer, sizeof(buffer), "Iqbal Muchlis 5024201073 -> %d.%d.%d >> %d %s %d >> %d C", hour(t), minute(t), second(t), day(t), monthShortStr(month(t)), _DEC(year(t)), displayCelcius);
    // // snprintf(buffer, sizeof(buffer), "%d C", celcius);
    float voltage = analogRead(LM_35) * (5.0 / 1023.0);
    float celcius = (voltage - 0.5) * 100.0;
    Serial << celcius << F(" C");

    snprintf(buffer, sizeof(buffer), "Iqbal Muchlis 5024201073 -> %d.%d.%d >> %d %s %d >> %0.2f C", hour(t), minute(t), second(t), day(t), monthShortStr(month(t)), _DEC(year(t)), celcius);



    // THIS FLOAT BELOW IS EATING TOO MUCH MEMORY DONT DO IT

    // (this was once a frightening float) uint8_t c = myRTC.temperature() / 4.;
    // (this was once a frightening float) uint8_t f = c * 9. / 5. + 32.;
    // Serial << F("  ") << c << F(" C  ") << f << F(" F");


    Serial << endl;
  }
  // sprintf(buffer, "%d %s %d %d:%d:%d", day(t), monthShortStr(month(t)), _DEC(year(t)), hour(t), minute(t), second(t));
  if (P.displayAnimate()) {
    P.displayText(buffer, PA_CENTER, 25, 25, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
    P.displayReset();
  }
}

// print date and time to Serial
void printDateTime(time_t t) {
  printDate(t);
  Serial << ' ';
  printTime(t);

  // sprintf(buffer, "%d %s %d %d:%d:%d", day(t), monthShortStr(month(t)), _DEC(year(t)), hour(t), minute(t), second(t));
  // 23,05,09,16,53,10
  // sprintf(buffer, "%d.%d.%d > %d %s %d", hour(t), minute(t), second(t), day(t), monthShortStr(month(t)), _DEC(year(t)));
  // sprintf(buffer, "%d %s %d", day(t), monthShortStr(month(t)), _DEC(year(t)));
  // if (P.displayAnimate()) {
  //   P.displayText(buffer, PA_CENTER, 0, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  //   P.displayReset();
  // }
}

// print time to Serial
void printTime(time_t t) {
  printI00(hour(t), ':');
  printI00(minute(t), ':');
  printI00(second(t), ' ');
}

// print date to Serial
void printDate(time_t t) {
  printI00(day(t), 0);
  Serial << "-" << monthShortStr(month(t)) << "-" << _DEC(year(t));
}

// Print an integer in "00" format (with leading zero),
// followed by a delimiter character to Serial.
// Input value assumed to be between 0 and 99.
void printI00(int val, char delim) {
  if (val < 10) Serial << '0';
  Serial << _DEC(val);
  if (delim > 0) Serial << delim;
  return;
}
