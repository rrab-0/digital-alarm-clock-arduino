// dot matrix
#include <MD_Parola.h>   // https://github.com/MajicDesigns/MD_Parola
#include <MD_MAX72xx.h>  // https://github.com/MajicDesigns/MD_MAX72XX)
#include <SPI.h>
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN 13
#define DATA_PIN 11
#define CS_PIN 10
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// real time clock
#include <Streaming.h>  // https://github.com/janelia-arduino/Streaming
#include <TimeLib.h>    // https://github.com/PaulStoffregen/Time
#include <DS3232RTC.h>  // https://github.com/JChristensen/DS3232RTC
DS3232RTC myRTC;
// temp sensor
#include <LM35.h>  // https://github.com/wilmouths/LM35
LM35 lm35(A0);
// light sensor
#define LIGHT_SENSOR A1
// buzzer
#define BUZZER 8
// keyboard
#define CLOCK 6
#define DATA 7

// for snprintf
char buffer[60];

// font
MD_MAX72XX::fontType_t newFont[] PROGMEM = {
  0,                            // 0
  0,                            // 1
  0,                            // 2
  0,                            // 3
  0,                            // 4
  0,                            // 5
  0,                            // 6
  0,                            // 7
  0,                            // 8
  0,                            // 9
  0,                            // 10
  0,                            // 11
  0,                            // 12
  0,                            // 13
  0,                            // 14
  0,                            // 15
  0,                            // 16
  0,                            // 17
  0,                            // 18
  0,                            // 19
  0,                            // 20
  0,                            // 21
  0,                            // 22
  0,                            // 23
  0,                            // 24
  0,                            // 25
  0,                            // 26
  0,                            // 27
  0,                            // 28
  0,                            // 29
  0,                            // 30
  0,                            // 31
  1, 0,                         // 32       - space
  0,                            // 33
  0,                            // 34
  0,                            // 35
  0,                            // 36
  0,                            // 37
  0,                            // 38
  0,                            // 39
  0,                            // 40
  0,                            // 41
  0,                            // 42
  0,                            // 43
  2, 64, 32,                    // 44
  0,                            // 45
  1, 32,                        // 46
  0,                            // 47
  4, 56, 68, 68, 56,            // 48       - 0
  2, 8, 124,                    // 49        - 1
  4, 72, 100, 84, 72,           // 50        - 2
  3, 84, 84, 124,               // 51       - 3
  3, 16, 24, 124,               // 52        - 4
  3, 92, 84, 116,               // 53       - 5
  3, 124, 84, 116,              // 54       - 6
  3, 4, 4, 124,                 // 55        - 7
  3, 124, 84, 124,              // 56       - 8
  3, 92, 84, 124,               // 57       - 9
  1, 36,                        // 58        - :
  2, 64, 36,                    // 59
  0,                            // 60
  0,                            // 61
  0,                            // 62
  0,                            // 63
  0,                            // 64
  3, 120, 20, 120,              // 65
  3, 124, 84, 40,               // 66
  3, 56, 68, 68,                // 67
  3, 124, 68, 56,               // 68
  3, 124, 84, 84,               // 69
  3, 124, 20, 20,               // 70
  4, 56, 68, 84, 116,           // 71
  4, 124, 16, 16, 124,          // 72
  1, 124,                       // 73
  3, 64, 64, 124,               // 74
  3, 124, 40, 68,               // 75
  3, 124, 64, 64,               // 76
  5, 124, 8, 16, 8, 124,        // 77
  5, 124, 8, 16, 32, 124,       // 78
  5, 56, 68, 68, 68, 56,        // 79
  4, 126, 18, 18, 12,           // 80
  5, 56, 68, 100, 68, 184,      // 81
  4, 124, 20, 52, 88,           // 82
  4, 76, 146, 146, 100,         // 83
  5, 4, 4, 124, 4, 4,           // 84
  5, 60, 64, 64, 64, 60,        // 85
  5, 28, 32, 64, 32, 28,        // 86
  5, 60, 64, 112, 64, 60,       // 87
  6, 132, 72, 48, 48, 72, 132,  // 88
  5, 4, 8, 240, 8, 4,           // 89
  5, 68, 100, 84, 76, 68,       // 90
  0,                            // 91
  0,                            // 92
  0,                            // 93
  0,                            // 94
  0,                            // 95
  0,                            // 96
  3, 96, 80, 112,               // 97
  0,                            // 98
  0,                            // 99
  0,                            // 100
  0,                            // 101
  0,                            // 102
  0,                            // 103
  0,                            // 104
  0,                            // 105
  0,                            // 106
  0,                            // 107
  0,                            // 108
  0,                            // 109
  0,                            // 110
  0,                            // 111
  0,                            // 112
  0,                            // 113
  0,                            // 114
  0,                            // 115
  0,                            // 116
  0,                            // 117
  0,                            // 118
  0,                            // 119
  0,                            // 120
  3, 16, 96, 16,                // 121
  0,                            // 122
  0,                            // 123
  0,                            // 124
  0,                            // 125
  0,                            // 126
  0,                            // 127
  0,                            // 128
  0,                            // 129
  0,                            // 130
  0,                            // 131
  0,                            // 132
  0,                            // 133
  0,                            // 134
  0,                            // 135
  0,                            // 136
  0,                            // 137
  0,                            // 138
  0,                            // 139
  0,                            // 140
  0,                            // 141
  0,                            // 142
  0,                            // 143
  0,                            // 144
  0,                            // 145
  0,                            // 146
  0,                            // 147
  0,                            // 148
  0,                            // 149
  0,                            // 150
  0,                            // 151
  0,                            // 152
  0,                            // 153
  0,                            // 154
  0,                            // 155
  0,                            // 156
  0,                            // 157
  0,                            // 158
  0,                            // 159
  0,                            // 160
  0,                            // 161
  0,                            // 162
  0,                            // 163
  0,                            // 164
  0,                            // 165
  0,                            // 166
  0,                            // 167
  0,                            // 168
  0,                            // 169
  0,                            // 170
  0,                            // 171
  0,                            // 172
  0,                            // 173
  0,                            // 174
  0,                            // 175
  2, 0, 4,                      // 176
  0,                            // 177
  0,                            // 178
  0,                            // 179
  0,                            // 180
  0,                            // 181
  0,                            // 182
  0,                            // 183
  0,                            // 184
  0,                            // 185
  2, 0, 0,                      // 186
  0,                            // 187
  0,                            // 188
  0,                            // 189
  0,                            // 190
  0,                            // 191
  0,                            // 192
  0,                            // 193
  0,                            // 194
  0,                            // 195
  0,                            // 196
  0,                            // 197
  0,                            // 198
  0,                            // 199
  0,                            // 200
  0,                            // 201
  0,                            // 202
  0,                            // 203
  0,                            // 204
  0,                            // 205
  0,                            // 206
  0,                            // 207
  0,                            // 208
  0,                            // 209
  0,                            // 210
  0,                            // 211
  0,                            // 212
  0,                            // 213
  0,                            // 214
  0,                            // 215
  0,                            // 216
  0,                            // 217
  0,                            // 218
  0,                            // 219
  0,                            // 220
  0,                            // 221
  0,                            // 222
  0,                            // 223
  0,                            // 224
  0,                            // 225
  0,                            // 226
  0,                            // 227
  0,                            // 228
  0,                            // 229
  0,                            // 230
  0,                            // 231
  0,                            // 232
  0,                            // 233
  0,                            // 234
  0,                            // 235
  0,                            // 236
  0,                            // 237
  0,                            // 238
  0,                            // 239
  0,                            // 240
  0,                            // 241
  0,                            // 242
  0,                            // 243
  0,                            // 244
  0,                            // 245
  0,                            // 246
  0,                            // 247
  0,                            // 248
  0,                            // 249
  0,                            // 250
  0,                            // 251
  0,                            // 252
  0,                            // 253
  0,                            // 254
  0,                            // 255
};

void alarmCheck(char alarmNumber, char c) {
  if (alarmNumber == "1") {
    return snprintf(buffer, sizeof(buffer), "5024201073");
  } else if (alarmNumber == "2") {
    return snprintf(buffer, sizeof(buffer), "5024201073 Iqbal Muchlis");
  } else if (alarmNumber == "3") {
    return snprintf(buffer, sizeof(buffer), "%d", c);
  } else {
    return snprintf(buffer, sizeof(buffer), "invalid alarm format!");
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(CLOCK, INPUT);
  pinMode(DATA, INPUT);
  pinMode(BUZZER, OUTPUT);
  myRTC.begin();
  P.begin();
  P.setFont(newFont);

  // setSyncProvider() causes the Time library to synchronize with the
  // external RTC by calling RTC.get() every five minutes by default.
  setSyncProvider(myRTC.get);
  Serial << F("RTC Sync");
  if (timeStatus() != timeSet)
    Serial << F(" FAIL!");
  Serial << endl;

  P.displayClear();
}

void loop() {
  // change time_t (uint32_t) to uint16_t if need to free more memory
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

      Serial << endl;
      // dump any extraneous input
      while (Serial.available() > 0)
        Serial.read();
    }
  }

  t = now();

  if (t != tLast) {
    tLast = t;

    P.setIntensity(0);
    // changes brightness according to light sensor
    // if (analogRead(LIGHT_SENSOR) < 100) {
    //   // terang banget
    //   P.setIntensity(15);
    // } else if (analogRead(LIGHT_SENSOR) < 200) {
    //   // terang
    //   P.setIntensity(10);
    // } else if (analogRead(LIGHT_SENSOR) < 500) {
    //   // normal
    //   P.setIntensity(5);
    // } else if (analogRead(LIGHT_SENSOR) < 800) {
    //   // gelap
    //   P.setIntensity(3);
    // } else {
    //   // gelap banget
    //   P.setIntensity(0);
    // }

    // prints calendar and clock
    printDateTime(t);
    // prints LM35, RTC Temp, and LDR, current display on dot matrix
    Serial << "LM35: " << lm35.getTemp(CELCIUS) << " "
           << "RTC: " << myRTC.temperature() / 4.0 << " LDR:" << analogRead(LIGHT_SENSOR) << " " << buffer;
    int celciusTemp = lm35.getTemp(CELCIUS);

    // // alarm
    // bool inputMode = false;
    // bool checkFirstAlarm = false;
    // char keyboardInput;
    // char fromKeyboard;

    // if (keyboardInput == "+") {
    //   inputMode = true;
    // } else if (keyboardInput == "-") {
    //   inputMode = false;
    // }

    // while (inputMode == true) {
    //   snprintf(buffer, sizeof(buffer), "");

    //   if (keyboardInput == "1") {
    //     if (second(t) >= firstKeyboardInputDuration1 && second(t) <= firstKeyboardInputDuration2) {
    //       digitalWrite(BUZZER, HIGH);
    //       checkAlarm("1");
    //     }
    //   } else if (keyboardInput == "2") {
    //     if (second(t) >= secondKeyboardInputDuration1 && second(t) <= secondKeyboardInputDuration2) {
    //       digitalWrite(BUZZER, HIGH);
    //       checkAlarm("2");
    //     }
    //   } else if (keyboardInput == "3") {
    //     if (second(t) >= thirdKeyboardInputDuration1 && second(t) <= thirdKeyboardInputDuration2) {
    //       digitalWrite(BUZZER, HIGH);
    //       checkAlarm("%d", c)
    //     }
    //   }
    // }

    // check
    bool checkFirstAlarm = false;
    if (second(t) >= 3 && second(t) <= 5) {
      checkFirstAlarm = true;
    } else {
      checkFirstAlarm = false;
    }
    // test
    if (checkFirstAlarm == true) {
      snprintf(buffer, sizeof(buffer), "5024201073");
    } else if (second(t) == 9 || second(t) == 39 || second(t) == 14 || second(t) == 44) {
      snprintf(buffer, sizeof(buffer), " ");
    } else if ((second(t) >= 10 && second(t) <= 13) || (second(t) >= 40 && second(t) <= 43)) {
      // displays calendar for 3 seconds
      digitalWrite(BUZZER, LOW);
      snprintf(buffer, sizeof(buffer), "%d.%s.%d", day(t), monthShortStr(month(t)), _DEC(year(t)));
      Serial << " CALENDAR";
    } else if ((second(t) >= 14 && second(t) <= 17) || (second(t) >= 44 && second(t) <= 46)) {
      // displays temperature for 3 seconds
      digitalWrite(BUZZER, LOW);
      snprintf(buffer, sizeof(buffer), "%d °C", celciusTemp);
      Serial << " TEMP";
    } else {
      // displays clock as a default
      digitalWrite(BUZZER, LOW);
      snprintf(buffer, sizeof(buffer), "%d.%d.%d", hour(t), minute(t), second(t));
    }

    // for blinking dots
    // else if (second(t) % 2 == 0) {
    //   // if (minute(t) < 10) {
    //   //   strcat("0", minute(t));
    //   // }
    //   // if (second(t) < 10) {
    //   //   strcat("0", second(t));
    //   // }
    //   // if (hour(t) < 10) {
    //   //   strcat("0", hour(t));
    //   // }
    //   // snprintf(buffer, sizeof(buffer), "%d %s %d", day(t), monthShortStr(month(t)), _DEC(year(t)));
    //   // snprintf(buffer, sizeof(buffer), "%d °C", celciusTemp);
    //   digitalWrite(BUZZER, LOW);
    //   snprintf(buffer, sizeof(buffer), "%d %d %d", hour(t), minute(t), second(t));
    // } else {
    //   digitalWrite(BUZZER, LOW);
    //   snprintf(buffer, sizeof(buffer), "%d.%d.%d", hour(t), minute(t), second(t));
    // }

    Serial << endl;
  }

  if (P.displayAnimate()) {
    if (second(t) == 9 || second(t) == 39 || second(t) == 14 || second(t) == 44) {
      P.displayText(buffer, PA_CENTER, 60, 60, PA_OPENING, PA_OPENING);
    } else if (((second(t) >= 10 && second(t) <= 13) || (second(t) >= 40 && second(t) <= 43)) || ((second(t) >= 14 && second(t) <= 16) || (second(t) >= 44 && second(t) <= 45))) {

      P.displayText(buffer, PA_RIGHT, 60, 60, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
    } else {
      P.displayText(buffer, PA_CENTER, 60, 60, PA_NO_EFFECT, PA_NO_EFFECT);
    }
    P.displayReset();
  }
}

// print date and time to Serial
void printDateTime(time_t t) {
  printDate(t);
  Serial << ' ';
  printTime(t);
  // yy,mm,dd,hh,mm,ss
  // 23,05,09,16,53,10
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

// Print to serial an integer in "00" format (with leading zero),
// followed by a delimiter character.
// Input value assumed to be between 0 and 99.
void printI00(int val, char delim) {
  if (val < 10)
    Serial << '0';
  Serial << _DEC(val);
  if (delim > 0)
    Serial << delim;
  return;
}
