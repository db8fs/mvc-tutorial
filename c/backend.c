/**
 * @file backend.c
 * @brief Simulates native API for UART/LCD access
 */

#include <stdio.h>

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
