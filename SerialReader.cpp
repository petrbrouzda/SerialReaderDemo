#include "SerialReader.h"

void SerialReader::callback( HardwareSerial * hws )
{
  while (hws->available()) {
    char c = hws->read();

    // po spusteni pockame na konec radky, abychom nezpusobili chaos rozpulenou radkou
    if( this->lineState == 0 ) {
      if( c==13 || c==10 ) {
        this->lineState = 1;
        this->buffer[0] = 0;
      }
    } else {
      // uz jsme v normalnim stavu
      if( c==13 || c==10 ) {
        // konec radku
        if( this->pos==0 ) {
          // konec radku prisel bez dalsich dat = nic se nedeje
          continue;
        } else {
          // mame nejaka data, zkopirujeme je do vystupniho bufferu
          strcpy( this->outBuffer, this->buffer );
          this->lineReady = 1;
          this->pos=0;
        }
      } else {
        // jiny znak nez konec radku
        if( this->pos<this->bufferSize ) {
          this->buffer[this->pos++] = c;
          this->buffer[this->pos] = 0;
        } else {
          // ztratily se nam nejaka data
          //TODO: nejaky flag na vadnou radku
        }
      } // if( c==13 || c==10 ) {
    } // if( serLineState == 0 ) {
  } // while (hwSerial_1.available()) {
}

char * SerialReader::readLine( char * target )
{
  char * rc = NULL;
  noInterrupts();
  if( this->lineReady != 1 ) {
    target[0] = 0;
    rc=NULL;
  } else {
    strcpy( target, this->outBuffer );
    rc = target;
    this->lineReady = 0;
  }
  interrupts();
  return rc;
}

int SerialReader::available()
{
   return this->lineReady;
}
