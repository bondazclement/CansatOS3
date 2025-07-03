/*
 * gps.c
 *
 *  Created on: Jul 3, 2025
 *      Author: clementbondaz-sanson
 */
#include "gps.h"
#include <string.h>
#include <stdlib.h>

/**
 * @brief Parse une trame NMEA GPGGA pour en extraire l'altitude.
 * @param nmea_sentence: La trame NMEA à parser.
 * @param gps_data: Pointeur vers la structure où stocker les données.
 * @retval 0 si le parsing a réussi, -1 sinon.
 */
int GPS_Parse(char* nmea_sentence, GPS_Data* gps_data)
{
    if (strncmp(nmea_sentence, "$GPGGA", 6) != 0) {
        return -1;
    }

    char* token;
    int token_count = 0;

    // Fait une copie de la phrase pour ne pas modifier l'originale
    char sentence_copy[128];
    strncpy(sentence_copy, nmea_sentence, sizeof(sentence_copy));

    token = strtok(sentence_copy, ",");
    while (token != NULL) {
        token_count++;
        // Le 7ème token est la qualité du fix GPS (0=invalid, 1=GPS fix, ...)
        if (token_count == 7) {
            gps_data->fix = atoi(token);
        }
        // Le 10ème token est l'altitude
        if (token_count == 10) {
            gps_data->altitude = atof(token);
            return 0; // On a trouvé l'altitude, on peut sortir
        }
        token = strtok(NULL, ",");
    }

    return -1; // Altitude non trouvée
}

