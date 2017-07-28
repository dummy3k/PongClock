// http://tronixstuff.com/2014/12/01/tutorial-using-ds1307-and-ds3231-real-time-clock-modules-with-arduino/
#include "Arduino.h"

#include "Wire.h"
#define DS3231_I2C_ADDRESS 0x68
#define DS1307_I2C_ADDRESS 0x68
#define RTC_I2C_ADDRESS DS1307_I2C_ADDRESS

#include "DateTime.h"



// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return( (val/16*10) + (val%16) );
}
void x_setup()
{
  Wire.begin();
  Serial.begin(9600);
  Serial.write("Start\n");

  // set the initial time here:
  // DS3231 seconds, minutes, hours, day, date, month, year
  // setDS3231time(30,42,21,4,26,11,14);
  //setDS3231time(30,22,15,4,26,11,14);
  //setDS3231time(30,22,15,7,11,3,17);

}
void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
dayOfMonth, byte month, byte year)
{
  // sets time and date data to DS3231
  Wire.beginTransmission(RTC_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}
void readDS3231time(byte *second,
byte *minute,
byte *hour,
byte *dayOfWeek,
byte *dayOfMonth,
byte *month,
byte *year)
{
  Wire.beginTransmission(RTC_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(RTC_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}

DateTime getTime() {
  DateTime retVal;
  byte year;
  readDS3231time(&retVal.second, &retVal.minute, &retVal.hour, 
                 &retVal.dayOfWeek, &retVal.day, &retVal.month,  &year);
  retVal.year = year + 2000;
  return retVal;
}

bool startsWith(const char* s1, const char* s2) {
  size_t len = strlen(s1);
  for (int i = 0;  i<len; i++) {
     if (!s2[i]) return true;
     if (s1[i] != s2[i]) return false;
  }
  return true;
}

DateTime::DateTime() {
  this->year = 0;
  this->month = 0;
  this->day = 0;
  this->hour = 0;
  this->minute = 0;
  this->second = 0;
  this->dayOfWeek = -1;
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second) {
  this->year = year;
  this->month = month;
  this->day = day;
  this->hour = hour;
  this->minute = minute;
  this->second = second;
  this->dayOfWeek = -1;
}


DateTime DateTime::fromDateTimeString(const char* sDate, const char* sTime) {
  //Mar 18 2017
  char sMonth[4] = {0};
  int iMonth = 0;
  int day; //max 12bytes
  int year = 0; //max 12bytes
  if (sscanf(sDate, "%s %d %d", sMonth, &day, &year) == 3) {
    /*
    * Jan, Feb, Mar, Mai, Apr, Jun,
    * Jul, Aug, Sep, Oct, Nov, Dev
    */
    static const char S_JAN[] PROGMEM = "Jan";
    static const char S_FEB[] PROGMEM = "Feb";
    static const char S_MAR[] PROGMEM = "Mar";
    static const char S_MAI[] PROGMEM = "Mai";
    static const char S_APR[] PROGMEM = "Apr";
    static const char S_JUN[] PROGMEM = "Jun";
    static const char S_JUL[] PROGMEM = "Jul";
    static const char S_AUG[] PROGMEM = "Aug";
    static const char S_SEP[] PROGMEM = "Sep";
    static const char S_OCT[] PROGMEM = "Oct";
    static const char S_NOV[] PROGMEM = "Nov";
    static const char S_DEZ[] PROGMEM = "Dec";
    static const char* const MONTH_NAMES[] PROGMEM = {S_JAN, S_FEB, S_MAR, S_MAI, S_APR, S_JUN,
                                                      S_JUL, S_AUG, S_SEP, S_OCT, S_NOV, S_DEZ};
    for (int i=0; i<12; i++) {
      if (!strcmp_P(sMonth, MONTH_NAMES[i])) {
        iMonth = i;
      }
    }
    
    /*
    Serial.print("sMonth: ");
    Serial.println(sMonth);
    
    if (startsWith(sMonth, F("Ja"))) iMonth = 1; 
    if (startsWith(sMonth, "F")) iMonth = 2; 
    if (startsWith(sMonth, "Mar")) iMonth = 3; 
    if (startsWith(sMonth, "Mai")) iMonth = 4; 
    if (startsWith(sMonth, "Ap")) iMonth = 5; 
    if (startsWith(sMonth, "Jun")) iMonth = 6; 
    if (startsWith(sMonth, "Jul")) iMonth = 7; 
    if (startsWith(sMonth, "Au")) iMonth = 8; 
    if (startsWith(sMonth, "S")) iMonth = 9; 
    if (startsWith(sMonth, "O")) iMonth = 10; 
    if (startsWith(sMonth, "N")) iMonth = 11; 
    if (startsWith(sMonth, "D")) iMonth = 12; 
    */
  }

  int hour = 0;
  int minute = 0;
  int second = 0;
  if (sscanf(sTime, "%d:%d:%d", &hour, &minute, &second) != 3) {
  }

  DateTime ret = {year, iMonth, day,
                hour, minute, second};
  return ret;
}

char* DateTime::toString() {
  //2017-01-01 12:34:00
  // -> 19 bytes + 0;
  const size_t buffer_size = 20;
  static char buffer[buffer_size];
  memset(buffer, 0, buffer_size);

  snprintf_P(buffer, buffer_size, 
             PSTR("%04d-%02d-%02d %02d:%02d:%02d"), 
             this->year, this->month, this->day,
             this->hour, this->minute, this->second);
  /*
  int r = snprintf_P(buffer, buffer_size, S_TEST_FORMAT, 
          year, 65);
  sprintf_P(buffer, PSTR("%d %d"), 
          this->year, 65);
  */

  return buffer;
}

int DateTime::cmp(DateTime other) {
  if (this->year < other.year) return -1;
  if (this->year > other.year) return 1;
  if (this->month < other.month) return -1;
  if (this->month > other.month) return 1;
  if (this->day < other.day) return -1;
  if (this->day > other.day) return 1;
  if (this->hour < other.hour) return -1;
  if (this->hour > other.hour) return 1;
  if (this->minute < other.minute) return -1;
  if (this->minute > other.minute) return 1;
  if (this->second < other.second) return -1;
  if (this->second > other.second) return 1;

  return 0;
}

void displayTime()
{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
  &year);
  // send it to the serial monitor
  Serial.print(hour, DEC);
  // convert the byte variable to a decimal number when displayed
  Serial.print(F(":"));
  if (minute<10)
  {
    Serial.print(F("0"));
  }
  Serial.print(minute, DEC);
  Serial.print(F(":"));
  if (second<10)
  {
    Serial.print(F("0"));
  }
  Serial.print(second, DEC);
  Serial.print(F(" "));
  Serial.print(dayOfMonth, DEC);
  Serial.print(F("/"));
  Serial.print(month, DEC);
  Serial.print(F("/"));
  Serial.print(year, DEC);
  Serial.print(F(" Day of week: "));
  switch(dayOfWeek){
  case 1:
    Serial.println(F("Sunday"));
    break;
  case 2:
    Serial.println(F("Monday"));
    break;
  case 3:
    Serial.println(F("Tuesday"));
    break;
  case 4:
    Serial.println(F("Wednesday"));
    break;
  case 5:
    Serial.println(F("Thursday"));
    break;
  case 6:
    Serial.println(F("Friday"));
    break;
  case 7:
    Serial.println(F("Saturday"));
    break;
  }
}
void x_loop()
{
  //Serial.write("Loop\n");
  displayTime(); // display the real-time clock data on the Serial Monitor,
  delay(1000); // every second
}

/*
DateTime DateTime::addSeconds(size_t n) {
  byte second = n % 60;
  //byte day, hour, minute, second;
}
*/

