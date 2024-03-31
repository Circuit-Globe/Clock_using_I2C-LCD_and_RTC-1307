#ifndef RTC1307_h
#define RTC1307_h


#define RTC_address_write_mode   0b11010000
#define RTC_address_read_mode    0b11010001
#define RTC_second_address       0x00
#define RTC_minute_address       0x01
#define RTC_hour_address         0x02
#define RTC_day_address          0x03
#define RTC_date_address         0x04
#define RTC_month_address        0x05
#define RTC_year_address         0x06
#define one_byte                 1



volatile uint8_t read_second(){
  volatile uint8_t sec, second_ones, second_tens;
  i2c_start();
  i2c_write(RTC_address_write_mode);
  i2c_write(RTC_second_address);
  i2c_start();                     // repeated start
  i2c_write(RTC_address_read_mode);
  sec = i2c_read(one_byte);
  i2c_stop();

  second_ones = 0x0f & sec;
  second_tens = 0x07 & (sec >> 4);
  sec = (second_tens * 10) + second_ones;   // calculating the actual second value
  return sec;
}



volatile uint8_t read_minute(){
  volatile uint8_t minute, minute_ones, minute_tens;
  i2c_start();
  i2c_write(RTC_address_write_mode);
  i2c_write(RTC_minute_address);
  i2c_start();                     // repeated start
  i2c_write(RTC_address_read_mode);
  minute = i2c_read(one_byte);
  i2c_stop();

  minute_ones = 0x0f & minute;
  minute_tens = minute >> 4;
  minute = (minute_tens * 10) + minute_ones;   // calculating the actual minute value
  return minute;
}



volatile uint8_t read_hour(){
  volatile uint8_t hour, hour_ones, hour_tens;
  i2c_start();
  i2c_write(RTC_address_write_mode);
  i2c_write(RTC_hour_address);
  i2c_start();                     // repeated start
  i2c_write(RTC_address_read_mode);
  hour = i2c_read(one_byte);
  i2c_stop();

  hour_ones = 0x0f & hour;
  hour_tens = 0x03 & (hour >> 4);
  hour = (hour_tens * 10) + hour_ones;   // calculating the actual hour value
  return hour;
}



volatile uint8_t read_day(){
  volatile uint8_t day;
  i2c_start();
  i2c_write(RTC_address_write_mode);
  i2c_write(RTC_day_address);
  i2c_start();                     // repeated start

i2c_write(RTC_address_read_mode);
  day = i2c_read(one_byte);
  i2c_stop();

  day &= 0x07;                            // calculating the actual day value
  return day;
}



volatile uint8_t read_date(){
  volatile uint8_t date, date_ones, date_tens;
  i2c_start();
  i2c_write(RTC_address_write_mode);
  i2c_write(RTC_date_address);
  i2c_start();                     // repeated start
  i2c_write(RTC_address_read_mode);
  date = i2c_read(one_byte);
  i2c_stop();

  date_ones = 0x0f & date;
  date_tens = 0x03 & (date >> 4);
  date = (date_tens * 10) + date_ones;   // calculating the actual date value
  return date;
}



volatile uint8_t read_month(){
  volatile uint8_t month, month_ones, month_tens;
  i2c_start();
  i2c_write(RTC_address_write_mode);
  i2c_write(RTC_month_address);
  i2c_start();                     // repeated start
  i2c_write(RTC_address_read_mode);
  month = i2c_read(one_byte);
  i2c_stop();

  month_ones = 0x0f & month;
  month_tens = 0x01 & (month >> 4);
  month = (month_tens * 10) + month_ones;   // calculating the actual month value
  return month;
}



volatile uint8_t read_year(){
  volatile uint8_t year, year_ones, year_tens;
  i2c_start();
  i2c_write(RTC_address_write_mode);
  i2c_write(RTC_year_address);
  i2c_start();                     // repeated start
  i2c_write(RTC_address_read_mode);
  year = i2c_read(one_byte);
  i2c_stop();

  year_ones = 0x0f & year;
  year_tens = year >> 4;
  year = (year_tens * 10) + year_ones;   // calculating the actual year value
  return year;
}



#endif
