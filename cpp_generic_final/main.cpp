#include <stdlib.h>
#include <stdint.h>
#include "IView.hpp"
#include "thermometer.hpp"
#include "i2cclient.hpp"
#include <stdio.h>
#include <unistd.h>

void lcd_gotoxy(int, int);
void lcd_puts( const char* );
void uart_puts( const char* );


/**
 * @fn UART_Logger
 * @brief Sample View implementation for displaying values on UART
 */

class UART_Logger : public IView< IThermometer >
{
public:
    UART_Logger() { /* uart init code */}

    void update( const IThermometer & data)
    {
        const int len=40;
        char buf[len+1];
        const char* unit( data.getUnit() == IThermometer::UNIT_CELSIUS ? "C" : "F" );

        snprintf( buf, len, "Temp: %3.1f °%s\n", data.getTemperature(), unit );
        uart_puts( buf );
    }
};


/**
 * @class LCD_Logger
 * @brief Sample View implementation displaying the thermometer value on a LCD
 */

class LCD_Logger : public IView< IThermometer >
{
public:

    LCD_Logger() { /* lcd init code */ }

    void update( const IThermometer & data )
    {
        const int len=40;
        char buf[len+1];
        const char* unit( data.getUnit() == IThermometer::UNIT_CELSIUS ? "C" : "F" );

        snprintf( buf, len, "Temp: %3.1f °%s\n", data.getTemperature(), unit );

        lcd_gotoxy(0, 0);
        lcd_puts( buf );
    }
};


int main(int argc, char** argv)
{
    LCD_Logger  loggerLCD;
    UART_Logger loggerUART;

    I2C_Client port(1, 0xCD);
    Thermometer sensor( port, IThermometer::TYPE_DS1621 );

    sensor.setUnit( IThermometer::UNIT_FAHRENHEIT );
    sensor.addView( loggerLCD );
    sensor.addView( loggerUART );

    sensor.setModel( port, IThermometer::TYPE_DS1621 );

    while(1)
    {
        sensor.update();

        // wait 1 sec till next data acquisition
        sleep(1);
    }

    return 0;
}
