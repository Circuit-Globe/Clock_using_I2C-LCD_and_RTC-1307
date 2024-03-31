#include "I2C.h"
#include "LCD1602.h"
#include "RTC1307.h"


int main(){

  volatile uint8_t seconds, minutes, hours, days, dates, months, years;
  char day[][12] = {" Sunday", " Monday", " Tuesday", " Wednessday", " Thursday", " Friday", " Saturday",};

  i2c_init();
  lcd_init();

while(1){

  for(volatile long i=0; i<300; i++){    // printing the Time & Date for a particular time //

  lcd_cursor(0,0);
  lcd_string("TIME-");
  hours = read_hour();  // for reading the hour
  lcd_number(hours);    // for printing the hour
  lcd_string(":");
  minutes = read_minute();  // for reading the minute
  lcd_number(minutes);      // for printing the minute
  lcd_string(":");
  seconds = read_second();  // for reading the second
  lcd_number(seconds);      // for printing the second
  lcd_string("     ");

  lcd_cursor(1,0);
  lcd_string("DATE-");
  dates = read_date();  // for reading the date
  lcd_number(dates);    // for printing the date
  lcd_string("/");
  months = read_month();  // for reading the month
  lcd_number(months);      // for printing the month
  lcd_string("/");
  years = read_year();   // for reading the year
  lcd_number(20);
  lcd_number(years);      // for printing the year
  lcd_string("     ");
  }
  
  lcd_clear();
  lcd_cursor(0,0);
  lcd_string("Today is:-");
  lcd_cursor(1,0);
  days = read_day();        // for reading the day
  lcd_string(day[days - 1]);    // for printing the day
  lcd_string("     ");
  for(volatile long i=0; i<1000000; i++);  // delay //
  }
  return 0;
}
