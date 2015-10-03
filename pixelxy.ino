#include <Wire.h> //i2c
#include "font4x5.h"

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
void codebug_clear (void) {
         for (int y=0;y<5;y++) {
             codebug_set_row(y,0);
         }

}
void codebug_set_pixel (int x,int y) {
        // todo - needs to merge with display - when get_row implemented
        
          codebug_set_row(y,1 << (4-x));
     
}
void codebug_display_char (int letter) {
        for (int y=0;y<5;y++) {
          codebug_set_row(y,font[letter].line[4-y]);
        }
}
void loop()
{
        for (int x=0;x<5;x++) { 
          for (int y=0;y<5;y++) {
            codebug_clear();
            codebug_set_pixel(x,y);
            delay(100);
          }
        }
}
