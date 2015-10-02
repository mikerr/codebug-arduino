#include <Wire.h> //i2c
#include "font4x3.h"

int STATUS_OKAY = 0;
int STATUS_BUSY = 1;

int ROUTINE_QUERY =  0;
int ROUTINE_GET =  1;
int ROUTINE_GET_BULK =  2;
int ROUTINE_SET =  3;
int ROUTINE_SET_BULK =  4;

int CODEBUG_ADDRESS = 24;

void setup()
{
  Wire.begin();  //start i2c

}

void codebug_set_row ( int row, int value ) {
  int error; 
        Wire.beginTransmission(CODEBUG_ADDRESS);      
        Wire.write(ROUTINE_SET);
        Wire.write(row);
        Wire.write(value);
        error = Wire.endTransmission();
}
void codebug_display_char (int letter) {
        for (int x=0;x<5;x++) {
          codebug_set_row(x,font[letter].line[4-x]
          )
}
void loop()
{
        for (int number=0;number<100;number++) {
          codebug_display_char(number);
          delay(1000);
        }
        
}
