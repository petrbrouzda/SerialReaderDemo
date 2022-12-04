#ifndef P_SERIAL_READER_H
#define P_SERIAL_READER_H

/**
 * Nastroj pro cteni serioveho portu.
 * Je urcen k volani z callbacku Serial.OnReceive().
 * Uklada prijata data. Kdyz dostane celou radku, da ji do samostatneho bufferu, ktery vrati pres readLine().
 * Pokud prijdou dalsi data a cela dalsi radka, predeslou prepise.
 * Tj. pokud neodebira konzument dost rychle, dostava stale konzistentni cele radky, ale ne vsechny po sobe, ale vzdy tu posledni, ktera prisla.
 */

#include <stdio.h>
#include <stdlib.h>
#include <arduino.h>
#include <HardwareSerial.h>

#define SERIAL_READER_MAX_LINE_SIZE 100

class SerialReader
{
    public:
        void callback( HardwareSerial * hws );
        int available();
        char * readLine( char * target );

    private:
        char outBuffer[SERIAL_READER_MAX_LINE_SIZE+1];
        char buffer[SERIAL_READER_MAX_LINE_SIZE+1];
        int bufferSize = SERIAL_READER_MAX_LINE_SIZE;
        int pos = 0;

        /**
         * stav output bufferu 
         */
        volatile int lineReady = 0;
      
        /** 0 = zacali jsme nahodne odprostred
         *  1 = rozdelana korektni radka
         */
        int lineState = 0;
};

#endif
