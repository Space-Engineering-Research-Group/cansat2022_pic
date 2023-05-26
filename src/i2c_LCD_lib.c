//Subroutine for I2C LCD 1602D1
// 
// lcd_init() --- initialize and contrast adjust
// lcd_cmd(cmd) --- 1 byte command transfer
// lcd_data(data) --- 1 byte data transfer
// lcd_str(*ptr) --- string transfer
// lcd_clear() --- LCD clear
// lcd_icon() ---


//prototyping
void lcd_init(void);
void lcd_clear(void);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_str(char* ptr);
void lcd_icon(unsigned char num, unsigned char onoff);

//int contrast=0x18; // default contrast for 5.0V
int CONTRAST=0x1F; // high contrast for 5.0V

//set array for icon display
unsigned char ICON[14][2]={
   {0x00, 0x10},      // Antenna : num=0
   {0x02, 0x10},      // Telephone : num=1
   {0x04, 0x10},      // Electromagnetic wave : num=2
   {0x06, 0x10},      // Connector =3
   {0x07, 0x10},      // Upper arrow =4  
   {0x07, 0x08},      // Lower arrow =5
   {0x07, 0x18},      // Both arrow =6
   {0x09, 0x10},      // Lock =7
   {0x0B, 0x10},      // ?? =8
   {0x0D, 0x02},      // Battery case =9
   {0x0D, 0x12},      // Battery low =10
   {0x0D, 0x1A},      // Battery mid =11
   {0x0D, 0x1E},      // Battery high =12
   {0x0F, 0x10}      //  ?? =13
};


//LCD initialize function
void lcd_init(void)
{
   //delay_ms(100);
   lcd_cmd(0x38);            // 8bit 2line Normal mode
   lcd_cmd(0x39);            // 8bit 2line Extend mode   
   lcd_cmd(0x14);            // internal OSC 183Hz BIAS 1/5
   
   /* contrast adjust */
   lcd_cmd(0x70 + (CONTRAST & 0x0F));
   lcd_cmd(0x5C + (CONTRAST >> 4));
   
   lcd_cmd(0x6A);            // Follower for 5.0V
//   lcd_cmd(0x6B);            // Ffollwer for 3.3V
   //delay_ms(300);
   
   lcd_cmd(0x38);            // Set Normal mode 
   lcd_cmd(0x0C);            // Display On 
   lcd_cmd(0x01);            // Clear Display 
   
}

// 1 byte command transfer
void lcd_cmd(unsigned char cmd)
{
   i2c_start();               //i2c start
   i2c_write(0x7C);           //device address 
   i2c_write(0x00);           //command mode
   i2c_write(cmd);            //command transfer
   i2c_stop();                //i2c stop
   
   /* Clear or Home */
   if((cmd == 0x01)||(cmd == 0x02))
      delay_ms(2);            // 2msec delay
   else
      delay_us(30);           // 30��sec delay   
}

// 1 byte (1 character) data transfer
void lcd_data(unsigned char data)
{
   i2c_start();               //i2c start
   i2c_write(0x7C);           //device address 
   i2c_write(0x40);           //data mode
   i2c_write(data);            //data transfer
   i2c_stop();                //i2c stop
}

/// @brief 調査中
/// @param ptr 
void lcd_str(char* ptr)
{
   while(*ptr != 0)            //
      lcd_data(*ptr++);         //
}

// icon display
// "num" = icon choice, "onoff" = icon ON/OFF
// ex. lcd_icon(3,1);  -> "Connector" icon ON

/// @brief icon display
/// @param num icon choice
/// @param onoff icon ON/OFF
void lcd_icon(unsigned char num, unsigned char onoff)
{
   lcd_cmd(0x39);            // Extend mode
   lcd_cmd(0x40 | ICON[num][0]);   // determine icon address
   if(onoff)
      lcd_data(ICON[num][1]);   // icon ON data transfer
   else
      lcd_data(0x00);         // icon OFF data transfer
   lcd_cmd(0x38);            // Normal Mode
}

/// @brief LCD clear
/// @param  void
void lcd_clear(void)
{
 lcd_cmd(0x01);
}

