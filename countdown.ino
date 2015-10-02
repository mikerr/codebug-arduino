#include <Wire.h> //i2c

int STATUS_OKAY = 0;
int STATUS_BUSY = 1;

int ROUTINE_QUERY =  0;
int ROUTINE_GET =  1;
int ROUTINE_GET_BULK =  2;
int ROUTINE_SET =  3;
int ROUTINE_SET_BULK =  4;

int CODEBUG_ADDRESS = 24;

//thin 3x5 font
struct charmatrix { char c;  int d[5]; };
static charmatrix font[] =
{
'0', { 0x2, 0x5, 0x5, 0x5, 0x2 },
'1', { 0x2, 0x6, 0x2, 0x2, 0x7 },
'2', { 0x6, 0x1, 0x2, 0x4, 0x7 },
'3', { 0x6, 0x1, 0x2, 0x1, 0x6 },
'4', { 0x1, 0x5, 0x7, 0x1, 0x1 },
'5', { 0x7, 0x4, 0x6, 0x1, 0x6 },
'6', { 0x3, 0x4, 0x6, 0x5, 0x2 },
'7', { 0x7, 0x1, 0x2, 0x2, 0x2 },
'8', { 0x2, 0x5, 0x2, 0x5, 0x2 },
'9', { 0x2, 0x5, 0x3, 0x1, 0x6 },
};


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
  
        codebug_set_row(0,font[letter].d[0]);
        codebug_set_row(1,font[letter].d[1]);
        codebug_set_row(2,font[letter].d[2]);
        codebug_set_row(3,font[letter].d[3]);
        codebug_set_row(4,font[letter].d[4]);
}
void loop()
{
        for (int number=10;number>0;number--) {
          codebug_display_char(number);
          delay(1000);
        }
        
}
