#include <18f252.h>
#include <stdlib.h>
#include "../get_gps.c"

// xbee set up
#use rs232(Baud = 9600, XMIT = PIN_B2, RCV = PIN_B3, stream = xbee)
#use i2c(MASTER, SDA=PIN_B0, SCL=PIN_B1, SLOW)
#byte UCFG = 0xF6F
#bit UTRDI5 = UCFG.3

void main(void) {
    // for gps data 
    double latitude;
    double longitude;
    double altitude;
    double angle;

    // B3 is input mode
    // other B ports aer output mode
    set_tris_b(0x04);

    // C7 is input mode
    // other C ports are output mode
    set_tris_c(0x80);

    fprintf(xbee, "Power ON\r\n");
    fprintf(xbee, "wait GPS...\r\n");

    for(int i = 0; i < 5; i++){
        buffer = get_GPS_Data();
        latitude = get_latitude(buffer);
        longitude = get_longitude(buffer);
        altitude = get_altitude(buffer);
        angle = get_angle(buffer);

        fprintf(xbee, "Latitude : %lf, Longitude : %lf, Altitude : %lf, Angle : %lf\r\n", latitude, longitude, altitude, angle);
    }
}
