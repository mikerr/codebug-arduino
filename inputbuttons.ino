#include <Wire.h> //i2c
#include "font4x5.h"

int STATUS_OKAY = 0;
int STATUS_BUSY = 1;

int ROUTINE_QUERY =  0;
int ROUTINE_GET =  1;
int ROUTINE_GET_BULK =  2;
int ROUTINE_SET =  3;
int ROUTINE_SET_BULK =  4;

int NUM_CHANNELS = 8;
int OUTPUT_CHANNEL_INDEX = 5;
int INPUT_CHANNEL_INDEX = 6;
int IO_DIRECTION_CHANNEL = 7;

int CODEBUG_ADDRESS = 24;

void setup()
{
  Wire.begin();  //start i2c
   Serial.begin(115200);   
}

void codebug_set_row ( int row, int value ) {
  int error; 
        Wire.beginTransmission(CODEBUG_ADDRESS);      
        Wire.write(ROUTINE_SET);
        Wire.write(row);
        Wire.write(value);
        error = Wire.endTransmission();
}
int codebug_get_row ( int row ) {
  int error; 
  int data;
  
        Wire.beginTransmission(CODEBUG_ADDRESS);      
        Wire.write(ROUTINE_GET);
        Wire.write(row);
        error = Wire.endTransmission();   
        
        Wire.requestFrom(CODEBUG_ADDRESS, 1);
        while (Wire.available()) { 
             data = Wire.read(); 
            }    
            
        return (data);
}
int codebug_get_input ( int input ) {
  int error; 
  int data;
 // inputs,outputs accessed same as a row of pixels, 
 // inputs at row "6", outputs at row "5" - which are "offscreen" 

 // croc clip inputa are 0-3
 // switches A and B are inputs 4 and 5
 
        Wire.beginTransmission(CODEBUG_ADDRESS);      
        Wire.write(ROUTINE_GET);
        Wire.write(INPUT_CHANNEL_INDEX);
        error = Wire.endTransmission();   
        
        Wire.requestFrom(CODEBUG_ADDRESS, 1);
        while (Wire.available()) { 
             data = Wire.read(); 
            }           
            data =  (data >> input) & 0x1   ;    
        return (data);
}
void codebug_clear (void) {
         for (int y=0;y<5;y++) {
             codebug_set_row(y,0);
         }

}

void codebug_display_char (int letter) {
        for (int y=0;y<5;y++) {
          codebug_set_row(y,font[letter].line[4-y]);
        }
}
void loop()
{
        codebug_clear();
       
            if ( codebug_get_input(4)==1) {
                codebug_display_char(65);
                  delay(1000);
            }
              if ( codebug_get_input(5)==1) {
                codebug_display_char(66);
                  delay(1000);
            }
             
          
                
}
