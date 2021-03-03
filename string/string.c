#include "string.h"


static C ntoha_table[16] = "0123456789ABCDEF";


void i16toha(I16 n, C *str)
{
	btoha(n, str + 2);
	btoha(n >> 8, str);
}


void i32toha(I32 n, C *str)
{
	btoha(n, str + 6);
	btoha(n >> 8, str + 4);
	btoha(n >> 16, str + 2);
	btoha(n >> 24, str);
}


void i64toha(I64 n, C *str)
{
	i32toha(n, str + 8);
	i32toha(n >> 32, str);
}


void btoha(U8 n, C *str)
{
	str[1] = ntoha_table[n & 0x0F];
	str[0] = ntoha_table[n >> 4];
}