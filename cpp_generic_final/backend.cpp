#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void lcd_gotoxy(int x, int y)
{
}

void lcd_puts( const char* str )
{
    printf("LCD: %s", str );
}

void uart_puts( const char* str )
{
    printf("UART: %s", str);
}

void i2c_read_float(int port, int id, float* val)
{
    if( NULL != val )
    {

        printf("I2C read %f\n", *val );
    }
}


void i2c_read_uint16(int port, int id, uint16_t* val )
{
    if( NULL != val )
    {
        *val = rand() % 65536;
        printf("I2C read %d\n", *val);
    }
}
