#include <stdlib.h>
#include <stdint.h>
#include "thermometer.hpp"
#include "i2cclient.hpp"
#include "sensor_ds1621.hpp"
#include <stdio.h>
#include <unistd.h>

void lcd_gotoxy(int, int);
void lcd_puts( const char* );
void uart_puts( const char* );


/**
 * @fn UART_Logger
 * @brief Sample View implementation for displaying values on UART
 */

template< class Thermometer>
class UART_Logger : public IView< Thermometer >
{
public:
    UART_Logger() { /* uart init code */}

    void update( const Thermometer & th)
    {
        const int len=40;
        char buf[len+1];
        const char* unit( th.getUnit() == SensorDS1621::UNIT_CELSIUS ? "C" : "F" );

        snprintf( buf, len, "Temp: %3.1f °%s\n", th.getTemperature(), unit );
        uart_puts( buf );
    }
};


/**
 * @class LCD_Logger
 * @brief Sample View implementation displaying the thermometer value on a LCD
 */

template< class Thermometer >
class LCD_Logger : public IView< Thermometer >
{
public:

    LCD_Logger() { /* lcd init code */ }

    void update( const Thermometer & th )
    {
        const int len=40;
        char buf[len+1];
        const char* unit( th.getUnit() == SensorDS1621::UNIT_CELSIUS ? "C" : "F" );

        snprintf( buf, len, "Temp: %3.1f °%s\n", th.getTemperature(), unit );

        lcd_gotoxy(0, 0);
        lcd_puts( buf );
    }
};



int main(int argc, char** argv)
{
    typedef SensorDS1621 SensorType;
    typedef Thermometer<I2CClient, SensorType> Thermometer;

    LCD_Logger< Thermometer >  loggerLCD;
    UART_Logger< Thermometer > loggerUART;

    I2CClient port(1, 0xCD);

    Thermometer sensor( port );

    sensor.setUnit( SensorType::UNIT_FAHRENHEIT );
    sensor.addView( loggerLCD );
    sensor.addView( loggerUART );

    while(1)
    {
        sensor.update();

        // wait 1 sec till next data acquisition
        sleep(1);
    }

    return 0;
}
