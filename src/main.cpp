#include <Arduino.h>
#include <Wire.h>
#include <FastLED.h>
#include "cell.h"
#include <RTClib.h>

#define NUM_LEDS 256
#define DATA_PIN A5 //Was A5

CRGB leds[NUM_LEDS];

RTC_DS3231 rtc;

Cell m1 = {29,30,33,34};
Cell t1 = {26,27,36,37};
Cell w1 = {23,24,39,40};
Cell th1 = {20,21,42,43};
Cell f1 = {17,18,45,46};

Cell m2 = {65,66,93,94};
Cell t2 = {68,69,90,91};
Cell w2 = {71,72,87,88};
Cell th2 = {74,75,84,85};
Cell f2 = {77,78,81,82};

Cell m3 = {125,126,129,130};
Cell t3 = {122,123,132,133};
Cell w3 = {119,120,135,136};
Cell th3 = {116,117,138,139};
Cell f3 = {113,114,141,142};

Cell m4 = {161,162,189,190};
Cell t4 = {164,165,186,187};
Cell w4 = {167,168,183,184};
Cell th4 = {170,171,180,181};
Cell f4 = {173,174,177,178};

Cell m5 = {221,222,225,226};
Cell t5 = {218,219,228,229};
Cell w5 = {215,216,231,232};
Cell th5 = {212,213,234,235};
Cell f5 = {209,210,237,238};

Cell week1[5] = {m1,t1,w1,th1,f1};
Cell week2[5] = {m2,t2,w2,th2,f2};
Cell week3[5] = {m3,t3,w3,th3,f3};
Cell week4[5] = {m4,t4,w4,th4,f4};
Cell week5[5] = {m5,t5,w5,th5,f5}; 

Cell days[25] = {m1,t1,w1,th1,f1,m2,t2,w2,th2,f2,m3,t3,w3,th3,f3,m4,t4,w4,th4,f4,m5,t5,w5,th5,f5}; 

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int firstDayCell = 0;
int lastDayCell = 24;

void setStatus(Cell cell, Status _status) {
  cell.status = _status;
  for (int n : cell.ledNums) {
    leds[n] = cell.statusColor(); FastLED.show();
  }
}

void initialize(DateTime now) {
  int currentDayOfWeek = now.dayOfTheWeek();
  int currentDay = now.day();

  int firstDayOfWeek = (currentDayOfWeek - (currentDay - 1)) % 7;

  if (firstDayOfWeek < 0) {
    firstDayOfWeek += 7;
  }

  if (firstDayOfWeek == 0 || firstDayOfWeek == 6) {
    firstDayCell = 0;
  }
  else {
    firstDayCell = firstDayOfWeek - 1;
  }

  // Add logic for last day

  for (Cell cell : days) {
    setStatus(cell, Status::NotIncluded);
  }
}

void setup () {
  Serial.begin(57600);

#ifndef ESP8266
  Serial.println("ESP8266");
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

void loop () {
  DateTime now = rtc.now();

  if (now.second() == 15) {
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");

    // calculate a date which is 7 days, 12 hours, 30 minutes, 6 seconds into the future
    DateTime future (now + TimeSpan(7,12,30,6));

    Serial.print(" now + 7d + 12h + 30m + 6s: ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();

    Serial.print("Temperature: ");
    Serial.print(rtc.getTemperature());
    Serial.println(" C");

    Serial.println();
  }
  delay(1000);
}