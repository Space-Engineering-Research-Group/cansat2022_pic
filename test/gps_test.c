#include <../get_gps.h>
#include <18f2520.h>

// GPS set up
#use rs232(Baud = 9600, XMIT = PIN_C6, RCV = PIN_C7, stream = gps, ERRORS)

// xbee set up
#use rs232(Baud = 9600, XMIT = PIN_B2, RCV = PIN_B3, stream = xbee)
#byte UCFG = 0xF6F
#bit UTRDI5 = UCFG.3

void main(void) {
    // for gps data 
    char buffer[100];
    double latitude;
    double longitude;
    double altitude;

    // B4 is input mode
    // other B ports aer output mode
    set_tris_b(0x04);

    // C7 is input mode
    // other C ports are output mode
    set_tris_c(0x80);

    fprintf(xbee, "Power ON\r\n");

    fpirntf(xbee, "wait GPS...\r\n");

    buffer = get_GPS_Data(buffer);

    fprintf(xbee, "GPS OK\r\n");

    latitude = get_latitude(buffer);
    longitude = get_longitude(buffer);
    altitude = get_altitude(buffer);

    for(int i = 0; i < 5; i++){
        fprintf(xbee, "Latitude : %lf Longitude : %lf Altitude : %lf\r\n", latitude, longitude, altitude);
    }
}