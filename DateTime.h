#ifndef __DATETIME_H__
#define __DATETIME_H__

void displayTime();

struct DateTime {
  int year;
  byte month, day, hour, minute, second, dayOfWeek ;

  DateTime();
  DateTime(int year, int month, int day, int hour, int minute, int second);
  
  int cmp(DateTime other);

  static DateTime fromDateTimeString(const char* sDate, const char* sTime);
  char* toString();

  bool operator>(const DateTime& other)  { return cmp(other) > 0; }
  bool operator>=(const DateTime& other)  { return cmp(other) >= 0; }
  bool operator<=(const DateTime& other)  { return cmp(other) <= 0; }

  DateTime addSeconds(size_t n);
};

DateTime getTime();
void displayTime();
void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year);


#endif
