#include <Wire.h> //i2c

// Shows an arrow bitmap on the display


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
void loop()
{
  
        codebug_set_row(4, 0b11100);
        codebug_set_row(3, 0b11000);
        codebug_set_row(2, 0b10100);
        codebug_set_row(1, 0b00010);
        codebug_set_row(0, 0b00001);

}
