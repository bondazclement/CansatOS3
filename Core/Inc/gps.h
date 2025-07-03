#ifndef __GPS_H
#define __GPS_H

#include <stdint.h>

// Structure pour stocker les données GPS
typedef struct {
    float altitude;
    uint8_t fix; // 0 = no fix, 1 = fix
} GPS_Data;

int GPS_Parse(char* nmea_sentence, GPS_Data* gps_data);

#endif /* __GPS_H */
