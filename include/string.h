#ifndef STRING_H
#define STRING_H
#include <types.h>


void i16toha(I16 n, C *str); //integer to hex ascii
void i32toha(I32 n, C *str);
void i64toha(I64 n, C *str);
void btoha(U8 n, C *str); //byte to hex asii

#endif