//#define LOAD 10
#include <DS1302.h>
#include <SPI.h>
#include <HCMAX7219.h>
#include <stdio.h>

namespace {

const int kCePin   = 5;  // Chip Enable
const int kIoPin   = 6;  // Input/Output
const int kSclkPin = 7;  // Serial Clock

DS1302 rtc(kCePin, kIoPin, kSclkPin);
HCMAX7219 HCMAX7219(10);

String dayAsString(const Time::Day day) {
  switch (day) {
    case Time::kSunday: return "Sunday";
    case Time::kMonday: return "Monday";
    case Time::kTuesday: return "Tuesday";
    case Time::kWednesday: return "Wednesday";
    case Time::kThursday: return "Thursday";
    case Time::kFriday: return "Friday";
    case Time::kSaturday: return "Saturday";
  }
  return "(unknown day)";
}

void printTime() {
  // Get the current time and date from the chip.
  Time t = rtc.time();

  // Name the day of the week.
  const String day = dayAsString(t.day);

  // Format the time and date and insert into the temporary buffer.
  char buf[50];
  snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d",
           day.c_str(),
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);

  // Print the formatted string to serial so we can see the time.
  Serial.println(buf);

String str = dayAsString(t.day)+" "+t.yr+" "+t.mon+" "+t.date+" "+t.hr+" "+t.min+" "+t.sec+"          ";
char tab2[33];
strcpy(tab2, str.c_str());

  byte Loopcounter;
  byte Position;
  
  for (Loopcounter = 0; Loopcounter <= 5; Loopcounter++)
  {
    for (Position = 1; Position <= 33; Position++)
    {
      HCMAX7219.Clear();
      HCMAX7219.print7Seg(tab2,Position);
      HCMAX7219.Refresh();  
      delay(200);
    }
  }
}

}  // namespace

void setup() {
  rtc.writeProtect(false);
  rtc.halt(false);

  Time t(2016, 12, 04, 23, 30, 00, Time::kSunday);

  // Set the time and date on the chip.
  rtc.time(t);
}

// Loop and print the time every second.
void loop() {
  printTime();
  delay(2000);
}
