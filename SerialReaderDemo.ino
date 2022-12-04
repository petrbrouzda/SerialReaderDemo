/**
 * Quick-n-dirty demo pro cteni serioveho portu z callbacku.
 * Objekt SerialReader nacita data ze serioveho portu pres systemovy callback
 * a nabizi aplikaci vzdy posledni kompletne nactenou radku (zatimco uz nabira 
 * dalsi data).
 */

#define SERIAL1_TX_PIN 0
#define SERIAL1_RX_PIN 1

#define CTRL_PIN 12

#include "SerialReader.h"

HardwareSerial hwSerial_1(1);
SerialReader sr;

/**
 * Premosteni C callbacku na C++
 */
void serial_callback()
{
  sr.callback( &hwSerial_1 );
}


void setup() {
    Serial.begin(115200);

    // sr = new SerialReader();
     
    delay(1000);
    Serial.println( "Start." );

    //  HW Serial port na daných pinech RX a TX
    hwSerial_1.begin(9600, SERIAL_8N1, SERIAL1_RX_PIN, SERIAL1_TX_PIN);
    hwSerial_1.onReceive(serial_callback);

    // tohle ignorujte - pripojene zarizeni je potreba aktivovat
    pinMode( CTRL_PIN, OUTPUT );
    digitalWrite( CTRL_PIN, HIGH );
}


void loop() {

   char txt[101];

    // cca 10 sekund bez delay
   for( int i=0; i<100; i++ ) {
    
      // available je nastaveno tehdy, pokud je k dispozici cely ukonceny radek (to je rozdil proti raw serialportu) 
      // a readLine v tom pripade vrati cely tento radek bez cekani 
     if( sr.available() ) {
        sr.readLine(txt);
        Serial.println( txt );
     } 

     // pauza 100 msec bez volani delay()
     long t = millis();
     while( millis()-t < 100 ) {
        ;
     }
   }

   Serial.println( "." );
  
}
