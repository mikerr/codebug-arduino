#include <Wire.h> //i2c

int STATUS_OKAY = 0;
int STATUS_BUSY = 1;

int ROUTINE_QUERY =  0;
int ROUTINE_GET =  1;
int ROUTINE_GET_BULK =  2;
int ROUTINE_SET =  3;
int ROUTINE_SET_BULK =  4;

int CODEBUG_ADDRESS = 24;

struct charmatrix { char c;  int line[5]; };
static charmatrix font[] =
{

//"4x5 character map.
//https,//github.com/tompreston/4x5-Font
//http,//clubweb.interbaun.com/~rc/Papers/microfont.pdf

    ' ', {0x0, 0x0, 0x0, 0x0, 0x0},
    '!', {0x4, 0x4, 0x4, 0x0, 0x4},
    '#', {0x6, 0xf, 0x6, 0xf, 0x6},
    '\'', {0x0, 0xa, 0x0, 0x0, 0x0},
    '%', {0x7, 0xe, 0x4, 0x7, 0xe},
    '$', {0x7, 0xa, 0x6, 0x5, 0xe},
    '"', {0x1, 0x2, 0x0, 0x0, 0x0},
    '&', {0x2, 0x5, 0x6, 0xa, 0x5},
    ')', {0x4, 0x2, 0x2, 0x2, 0x4},
    '(', {0x4, 0x8, 0x8, 0x8, 0x4},
    '+', {0x0, 0x2, 0x7, 0x2, 0x0},
    '*', {0x0, 0x6, 0xf, 0x6, 0x0},
    '-', {0x0, 0x0, 0x0, 0xf, 0x0},
    ',', {0x0, 0x0, 0x0, 0x2, 0x4},
    '/', {0x1, 0x1, 0x2, 0x4, 0x8},
    '.', {0x0, 0x0, 0x0, 0x0, 0x4},
    '1', {0x2, 0x6, 0x2, 0x2, 0x2},
    '0', {0x6, 0xb, 0xf, 0xd, 0x6},
    '3', {0xe, 0x1, 0x6, 0x1, 0xe},
    '2', {0xe, 0x1, 0x6, 0x8, 0xf},
    '5', {0xf, 0x8, 0xe, 0x1, 0xe},
    '4', {0x2, 0x6, 0xa, 0xf, 0x2},
    '7', {0xf, 0x1, 0x2, 0x4, 0x8},
    '6', {0x6, 0x8, 0xe, 0x9, 0x6},
    '8', {0x6, 0x9, 0x6, 0x9, 0x6},
    '9', {0x6, 0x9, 0xf, 0x1, 0x6},
    ',', {0x0, 0x4, 0x0, 0x4, 0x0},
    ';', {0x0, 0x4, 0x0, 0x4, 0x8},
    '<', {0x2, 0x4, 0x8, 0x4, 0x2},
    '=', {0x0, 0xf, 0x0, 0xf, 0x0},
    '>', {0x4, 0x2, 0x1, 0x2, 0x4},
    '?', {0x6, 0x9, 0x2, 0x0, 0x2},
    '@', {0x6, 0xd, 0xb, 0x8, 0x6},
    'A', {0x4, 0xa, 0xe, 0xa, 0xa},
    'B', {0xe, 0x9, 0xe, 0x9, 0xe},
    'C', {0x6, 0x9, 0x8, 0x9, 0x6},
    'D', {0xe, 0x9, 0x9, 0x9, 0xe},
    'E', {0xf, 0x8, 0xe, 0x8, 0xf},
    'F', {0xf, 0x8, 0xe, 0x8, 0x8},
    'G', {0x6, 0x8, 0xb, 0x9, 0x6},
    'H', {0x9, 0x9, 0xf, 0x9, 0x9},
    'I', {0xe, 0x4, 0x4, 0x4, 0xe},
    'J', {0x1, 0x1, 0x1, 0x9, 0x6},
    'K', {0x9, 0xa, 0xc, 0xa, 0x9},
    'L', {0x8, 0x8, 0x8, 0x8, 0xf},
    'M', {0x9, 0xf, 0xf, 0x9, 0x9},
    'N', {0x9, 0xd, 0xf, 0xb, 0x9},
    'O', {0x6, 0x9, 0x9, 0x9, 0x6},
    'P', {0xe, 0x9, 0xe, 0x8, 0x8},
    'Q', {0x6, 0x9, 0x9, 0xb, 0x7},
    'R', {0xe, 0x9, 0xe, 0xa, 0x9},
    'S', {0x7, 0x8, 0x6, 0x1, 0xe},
    'T', {0xe, 0x4, 0x4, 0x4, 0x4},
    'U', {0x9, 0x9, 0x9, 0x9, 0x6},
    'V', {0x9, 0x9, 0x9, 0x6, 0x6},
    'W', {0x9, 0x9, 0xf, 0xf, 0x9},
    'X', {0x9, 0x9, 0x6, 0x9, 0x9},
    'Y', {0x9, 0x5, 0x2, 0x2, 0x2},
    'Z', {0xf, 0x2, 0x4, 0x8, 0xf},
    '{', {0xe, 0x8, 0x8, 0x8, 0xe},
    '\\', {0x8, 0x8, 0x4, 0x2, 0x1},
    '}', {0x7, 0x1, 0x1, 0x1, 0x7},
    '^', {0x4, 0xa, 0x0, 0x0, 0x0},
    '_', {0x0, 0x0, 0x0, 0x0, 0xf},
    '`', {0x4, 0x2, 0x0, 0x0, 0x0},
    'a', {0x0, 0x5, 0xb, 0xb, 0x5},
    'b', {0x8, 0x8, 0xe, 0x9, 0xe},
    'c', {0x0, 0x7, 0x8, 0x8, 0x7},
    'd', {0x1, 0x1, 0x7, 0x9, 0x7},
    'e', {0x0, 0x6, 0xf, 0x8, 0x7},
    'f', {0x3, 0x4, 0xe, 0x4, 0x4},
    'g', {0x7, 0x9, 0x7, 0x1, 0x7},
    'h', {0x8, 0x8, 0xe, 0x9, 0x9},
    'i', {0x0, 0x2, 0x0, 0x2, 0x2},
    'j', {0x1, 0x0, 0x1, 0x1, 0x6},
    'k', {0x8, 0xa, 0xc, 0xa, 0x9},
    'l', {0xc, 0x4, 0x4, 0x4, 0xe},
    'm', {0x0, 0x9, 0xf, 0xf, 0x9},
    'n', {0x0, 0xe, 0x9, 0x9, 0x9},
    'o', {0x0, 0x6, 0x9, 0x9, 0x6},
    'p', {0x0, 0xe, 0x9, 0xe, 0x8},
    'q', {0x0, 0x6, 0x9, 0x7, 0x1},
    'r', {0x0, 0xb, 0xc, 0x8, 0x8},
    's', {0x0, 0x7, 0x4, 0x2, 0xe},
    't', {0x4, 0xe, 0x4, 0x4, 0x3},
    'u', {0x0, 0x9, 0x9, 0x9, 0x6},
    'v', {0x0, 0x9, 0x9, 0x6, 0x6},
    'w', {0x0, 0x9, 0xf, 0xf, 0x6},
    'x', {0x0, 0x9, 0x6, 0x6, 0x9},
    'y', {0x0, 0x9, 0x7, 0x1, 0x6},
    'z', {0x0, 0xf, 0x2, 0x4, 0xf},
    '{', {0x6, 0x4, 0xc, 0x4, 0x6},
    '|', {0x4, 0x4, 0x0, 0x4, 0x4},
    '}', {0xc, 0x4, 0x6, 0x4, 0xc},
    '~', {0x0, 0x0, 0x5, 0xa, 0x0}
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
        for (int x=0;x<5;x++) {
          codebug_set_row(x,font[letter].line[x]
          )
}
void loop()
{
        for (int number=0;number<100;number++) {
          codebug_display_char(number);
          delay(1000);
        }
        
}
