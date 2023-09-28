// Load pic header file
#include <18f2550.h>

// Built-in hardware Configure how to use the
#fuses HS,NOWDT,NOPROTECT,PUT,BROWNOUT,NOLVP

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <i2c_LCD_lib.c>


#include "spin.c"
#include "gps_data.c"
#include "gps_cal.c"

#use fast_io(A)
#use fast_io(B)
#use fast_io(C)

// RS232C setup
#use delay(CLOCK=20000000)
#use rs232(Baud = 9600, XMIT = PIN_C6, RCV = PIN_C7, stream = gps, ERRORS)
#use rs232(Baud = 9600, XMIT = PIN_B2, RCV = PIN_B3, stream = xbee)
#use i2c(MASTER, SDA=PIN_B0, SCL=PIN_B1, SLOW)
#byte UCFG = 0xF6F
#bit UTRDIS = UCFG.3


// WARNNING: Please specify properly
float64 goal_latitude = ;
float64 goal_longitude = ;

float64 current_latitude = 0.0;
float64 current_longitude = 0.0;

unsigned char lcd_buffer[50];

unsigned char buffer[100];

// config
int wait_time = 5;
int gps_receive_count = 0;
int is_dark = 1;


void setup_pic() {
  // USB disable
  UTRDIS = 1;

  // Input/output pin settings
  set_tris_A(0x00); //All of A ports are output mode
  set_tris_B(0x18); //B3 and B4 pin are inputs, other B ports are output mode
  set_tris_C(0x80); //C7 pin is input mode. C4 and C5 are "always input mode" when USB is disabled. Other C ports are output mode.
  
  // motor stop
  stop();

  // I2C(LCD) setup
  lcd_init();
  lcd_clear();

  lcd_str("Power ON");
  delay_ms(1000);
  lcd_clear():
  
  // Display the latitude and longitude of the goal in lcd
  sprintf(lcd_buffer, "Goal Latitude is %f", goal_latitude):
  lcd_str(lcd_buffer);
  sprintf(lcd_buffer, "Goal Longitude is %f", goal_longitude):
  lcd_str(lcd_buffer);

  // Send Power ON to Xbee
  // \r\n is the Windows line feed code
  fprintf(xbee, "Power ON\r\n");

  // output for servo
  output_low();

  fprintf(xbee, "Experiment Ready\r\n");

  // Throw away the first one because of the possibility of mixing strange data
  gets(buffer);

  // TODO: Think about the raison d'etre of this place
  do {
    gets(buffer);
    current_latitude = gps_lat(buffer);
    current_longitude = gps_lon(buffer);
    fprintf(xbee, "GPS setting\r\n");
  } while (buffer[22] == ',');
  
  do {
    fprintf(xbee, is_dark ? "Waiting to drop" : "Drop Complete");
    gets(buffer);
    gps_receve_count++;
    is_dark = input(PIN_B4)
  } while (gps_receve_count < 20 && is_dark == 0)
}


void main() {
  setup_pic();

  // TODO: Continue refactoring based on main2.c
}

