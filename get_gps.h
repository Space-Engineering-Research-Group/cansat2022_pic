#ifndef GETGPS_H
#define GETGPS_H

// Subroutine for get data receive
#include <string.h>
#include <extract_value.h>

// device set up
#device PIC18F2520

// global value
extern char buffer[100];

// prototyping

/// @brief GPSデータを取得する関数
/// @param buffer データを入力させたい変数
/// @return GPSデータを取得できなければNULL(要求がタイムアウトすればNULLが返ります),取得できればGPSデータの先頭アドレスが返ってきます
char get_GPS_Data(void);

/// @brief 緯度を取得する関数
/// @param GPSデータ（NMEAフォーマット）
/// @return 緯度[°]
double get_latitude(unsigned char*);

/// @brief 経度を取得する関数
/// @param GPSデータ（NMEAフォーマット）
/// @return 経度[°]
double get_longitude(unsigned char*);

/// @brief 標高を取得する関数
/// @param GPSデータ（NMEAフォーマット）
/// @return 標高[m]
double get_altitude(unsigned char*);

/// @brief obtain angle of advance
/// @param GPS_data NMEA format 
/// @return angle[°]
double get_angle(unsigned char*);

#endif