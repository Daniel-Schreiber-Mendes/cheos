

volatile char *videoadress = 0xb8000;


void printc(char const *string)
{
    for (unsigned short int i=0; string[i] != 0; ++i)
    {
        videoadress[i*2] = string[i];
    }
}
