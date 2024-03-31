#ifndef I2C_h
#define I2C_h



volatile char *I2C_TWSR = 0xB9;
volatile char *I2C_TWBR = 0xB8;
volatile char *I2C_TWCR = 0xBC;
volatile char *I2C_TWDR = 0xBB;

#define      TWCR_TWINT     7
#define      TWCR_TWEA      6
#define      TWCR_TWSTA     5
#define      TWCR_TWSTO     4
#define      TWCR_TWEN      2



void i2c_init (void){
*I2C_TWSR = 0X00;        // set prescaler bits to zero
*I2C_TWBR = 0x47;        // SCL frequency is 50K for XTAL = 8Mhz
*I2C_TWCR = 0x04;        // enable TWI module
}


void i2c_start(void){
 *I2C_TWCR = ( 1 << TWCR_TWINT ) | ( 1 << TWCR_TWSTA ) | ( 1 << TWCR_TWEN );
 while ((*I2C_TWCR & ( 1 << TWCR_TWINT )) == 0);     // wait for the start successfully
}


void i2c_write(unsigned char data){
 *I2C_TWDR = data ;
 *I2C_TWCR = (1<<TWCR_TWINT) | (1<<TWCR_TWEN);      // enable the transmission
 while ((*I2C_TWCR & ( 1 << TWCR_TWINT )) == 0);   // wait for the complete transmission
}
 

unsigned char i2c_read(unsigned char last){
  /* If want to read more than 1 byte */
 if ( last == 0 )  *I2C_TWCR = (1<<TWCR_TWINT) | (1<<TWCR_TWEN) | (1<<TWCR_TWEA);

 /* else read only one byte */
 else  *I2C_TWCR = (1<<TWCR_TWINT) | (1<<TWCR_TWEN);

 while ((*I2C_TWCR & ( 1 << TWCR_TWINT )) == 0);  // wait for the complete reception
 return *I2C_TWDR ; 
}


void i2c_stop(){
*I2C_TWCR = ( 1 <<TWCR_TWINT )|( 1 << TWCR_TWEN) | ( 1<< TWCR_TWSTO);
}



#endif
