// Load pic header file
#include <18f2550.h>

// Built-in hardware Configure how to use the
#fuses HS,NOWDT,NOPROTECT,PUT,BROWNOUT,NOLVP

#include <math.h>
#include <string.h>
#include <stdlib.h>

#include <motor.c>
#include <get_gps.c>
#include <stack_check.c>
#include <calculate.c>

#use fast_io(A)
#use fast_io(B)
#use fast_io(C)

// RS232C setup
#use delay(CLOCK=20000000)

// GPS setup
#use rs232(Baud = 9600, XMIT = PIN_C6, RCV = PIN_C7, stream = gps, ERRORS)

// xbee setup
#use rs232(Baud = 9600, XMIT = PIN_B2, RCV = PIN_B3, stream = xbee)
#use i2c(MASTER, SDA=PIN_B0, SCL=PIN_B1, SLOW)
#byte UCFG = 0xF6F
#bit UTRDIS = UCFG.3

// config
int wait_time = 5;
int gps_receive_count = 0;
int is_dark = 1;

AllPins motor_pins; 
motor_pins.Left.forward   = PIN_C0;
motor_pins.Left.back      = PIN_C1;
motor_pins.Right.forward  = PIN_A0;
motor_pins.Right.back     = PIN_C2;

unsigned char GPS_Data[100];
float pi = acos(-1.0);

// Run Set Up
void setup_pic(void) {
  // USB disable
  UTRDIS = 1;

  // Input/output pin settings
  set_tris_A(0x00); // All of A ports are output mode
  set_tris_B(0x18); // B3 and B4 pin are inputs, other B ports are output mode
  set_tris_C(0x80); // C7 pin is input mode. C4 and C5 are "always input mode" when USB is disabled. Other C ports are output mode.
  
  // set up values
  int servo_pin = PIN_B5;
  
  // motor stop
  motor_stop(&motor_pins);

  // Send Power ON to Xbee
  // \r\n is the Windows line feed code
  fprintf(xbee, "Power ON\r\n");

  // output for servo
  output_low(servo_pin);

  fprintf(xbee, "Experiment Ready\r\n");

  do {
    fprintf(xbee, is_dark ? "Waiting to drop" : "Drop Complete");
    gets(buffer);
    gps_receive_count++;
    is_dark = input(PIN_B4)
  } while (gps_receive_count < 20 && is_dark == 0)

  // set up GPS
  fprintf(xbee, "Waiting for GPS\r\n");
  buffer = get_GPS_Data();
  fprintf(xbee, "GPS is OK\r\n");
}

void main() {
  setup_pic();

  // set up values
  unsigned char GPS_Data[100];
  Coordinate Start, Goal, Now;

  fprintf(xbee, "Setting Up Goal Parameter\r\n");
  do{
    GPS_Data = get_GPS_Data();
    Now.latitude  = get_latitude(GPS_Data);
    Now.longitude = get_longitude(GPS_Data);
  }while(Now.latitude == NULL);
  
  Now.latitude  = (int)Now.latitude;
  Now.longitude = (int)Now.longitude;

  Goal.latitude   = 4566.0;
  Goal.longitude  = 6058.0;

  Goal.latitude   = Goal.latitude / 1000 + Now.latitude;
  Goal.longitude  = Goal.longitude / 1000 + Now.longitude;

  fprintf(xbee, "Goal is %lf , %lf\r\n", Goal.latitude, Goal.longitude);

  Start.latitude  = get_latitude(GPS_Data);
  Start.longitude = get_longitude(GPS_Data);

  fprintf(xbee, "Setting Up Complete\r\n");

  // Start
  motor_forward(motor_pins);
  delay_ms(10000);

  while (true)
  {
    // Goal Check
    do{
      GPS_Data = get_GPS_Data();
      Now.latitude  = get_latitude(GPS_Data);
      Now.longitude = get_longitude(GPS_Data);
    }while(Now.latitude == NULL);

    double distance_to_goal = fabs(distance(Now.latitude, Now.longitude) - distance(Goal.latitude, Goal.longitude));
    fprintf(xbee, "%4d. Latitude : %0.4lf, Longitude : %0.4lf, Distance : %lf", Now.latitude, Now.longitude, distance_to_goal);

    if(distance_to_goal < 0.0005){
      break;
    }

    back_check(&Now, &Start, motor_pins);
    turn_check(&Now, &Start, &Goal, &motor_pins);

  }

  fprintf(xbee, "Mission Complete\r\n");
  return;

}