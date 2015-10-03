#include <Wire.h> //i2c
#include "font4x5.h"


// blink a led connected to leg 1

// **curently not working** 

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



void codebug_set_row ( int row, int value ) {
  int error; 
        Wire.beginTransmission(CODEBUG_ADDRESS);      
        Wire.write(ROUTINE_SET);
        Wire.write(row);
        Wire.write(value);
        error = Wire.endTransmission();
}


void codebug_set_output (int output_index,int state) {
          
int error; 
int output_state;
           
        Wire.beginTransmission(CODEBUG_ADDRESS);      
        Wire.write(ROUTINE_GET);
        Wire.write(OUTPUT_CHANNEL_INDEX);
        error = Wire.endTransmission();   
        
        Wire.requestFrom(CODEBUG_ADDRESS, 1);
        while (Wire.available()) { 
             output_state = Wire.read(); 
            }           

        if (state != 0) {
            output_state |= 1 << output_index;
        }
        else {
            output_state &= 0xff ^ (1 << output_index);
        }
        Wire.beginTransmission(CODEBUG_ADDRESS);      
        Wire.write(ROUTINE_SET);
        Wire.write(OUTPUT_CHANNEL_INDEX);
        Wire.write(output_state);
        error = Wire.endTransmission();


}

void codebug_set_io (int leg,int direction) {
  //Sets the I/O direction of the leg at index. 1 is Input, 0 is Output.
        
  // io_config_state = leg_index in upper nibble and state in lower nibble
  
        int io_config_state = ((leg << 4) & 0xf0) | (direction & 0x0f);
        int error; 
        Wire.beginTransmission(CODEBUG_ADDRESS);      
        Wire.write(ROUTINE_SET);
        Wire.write(IO_DIRECTION_CHANNEL);
        Wire.write(io_config_state);
        error = Wire.endTransmission();
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

void setup()
{
  Wire.begin();  //start i2c
   Serial.begin(115200);   

   codebug_set_io(1,0);
}
void loop()
{
        codebug_clear();

        codebug_set_row(4,0xb00001);
        codebug_set_output(1,1);

        delay(1000);
        
        codebug_clear();
        codebug_set_output(1,0);
        
        delay(1000);
           
}
