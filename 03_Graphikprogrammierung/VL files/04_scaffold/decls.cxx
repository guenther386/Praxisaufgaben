#include "decls.h" // include from same directory
// booleans
bool f=true, not_f=false;

// declarations with integral types
char  c_dec = -12, c_oct = 0176, c_hex = 0x7d;   //  8 bit
unsigned short s = 65535u;                       // 16 bit
int i = -2147483647;                             // 32 bit
unsigned long l = 4294967295u;                   // 32 bit
long long ll = 9223372036854775807ll;            // 64 bit

// declarations with floating point types
float f_1 = 15.75f, f_2 = 1.575E1f;
double d_1 = 1575e-2, d_2 = -2.5e-345;

// declarations with character constants
char c_alpha = 'c', c_oct1 = '\176', c_hex1 = '\xcd';
const char* text = "\a ... bell, \b ... backspace, "
  "\f ... formfeed, \n ... newline, \r ... return, "
  "\t ... horizontal tab, \v ... vertical tab, "
  "\', \", \\, \? ... special characters";

// declaration with enumerate type
Number n = MINUS_ONE;
