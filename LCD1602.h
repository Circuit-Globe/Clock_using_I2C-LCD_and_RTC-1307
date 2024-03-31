#ifndef LCD1602_h
#define LCD1602_h


#define command_en_high               4 + 8          // RS=0, R/W=0, EN=1 (4), LED+ = 1 (8)
#define command_en_low                0 + 8          // RS=0, R/W=0, EN=0, LED+ = 1 (8)
#define data_en_high                  1 + 4 + 8      // RS=1 (1), R/W=0, EN=1 (4), LED+ = 1 (8)
#define data_en_low                   1 + 8          // RS=1 (1), R/W=0, EN=0, LED+ = 1 (8)
#define LCD_address_write_mode        0x27 << 1      // slave address of the I2C LCD



void send_command(volatile uint8_t cmd){

	volatile uint8_t high_nibble = cmd & 0xf0;
	volatile uint8_t low_nibble = cmd << 4;

  i2c_start(); // transmit start 
  i2c_write(LCD_address_write_mode); // transmitt Slave address + W0 (SLA+W means to master is writing )
  
  i2c_write(high_nibble + command_en_high);
  i2c_write(high_nibble + command_en_low);
  i2c_write(low_nibble + command_en_high);
	i2c_write(low_nibble + command_en_low);
  i2c_stop(); // transmit stop condition
  delayMicroseconds(50);
}



void send_data(volatile uint8_t data1){

	volatile uint8_t high_nibble = data1 & 0xf0;
	volatile uint8_t low_nibble = data1 << 4;

  i2c_start(); // transmit start 
  i2c_write(LCD_address_write_mode); // transmitt Slave address + W0 (SLA+W means to master is writing )
  i2c_write(high_nibble + data_en_high);
  i2c_write(high_nibble + data_en_low);
  i2c_write(low_nibble + data_en_high);
  i2c_write(low_nibble + data_en_low);
  i2c_stop(); // transmitt stop condition
  delayMicroseconds(50);
}



void lcd_init(){
  send_command (0x02);   // 4bit mode 
	send_command (0x0C);	// Display ON Cursor OFF 
	send_command (0x06);	// Auto Increment cursor 
	send_command (0x01);	// Clear display 
	send_command (0x80);	// Cursor at home position
}



void lcd_string (char *str){ 
	int i;
	for(i=0;str[i]!=0;i++)
	send_data (str[i]);  /* Call LCD data write */
}



void lcd_number(volatile uint16_t number){
  volatile char i=0, num[8]={0};
  
  while(number){
    num[i++] = number%10;
    number/=10;
  }
  i--;
  for(; i>=0; i--)
  send_data(num[i] + 48);
}



void lcd_cursor(volatile uint8_t row, volatile uint8_t column){
  if(row==0) send_command(0x80 + column);
  else if(row==1) send_command(0xc0 + column);
}



void lcd_clear(){
  send_command(0x01);
}



#endif
