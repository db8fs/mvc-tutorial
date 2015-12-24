#include "thermometer.hh"
#include "IView.hh"
#include <iostream>
#include <string>


/**
 * @fn format_temperature
 * @brief creates output string
 */

static void format_temperature( char* buf, int len, const Thermometer & th )
{
    if( th.getType() == Thermometer::TYPE_DS1621 ) // sensor provides Celsius units
    {
        switch( th.getUnit() )
        {
        case UNIT_CELSIUS:
            snprintf( buf, len, "Temp: %3.1f °C\n", th.getTemperature() );
            break;

        case UNIT_FAHRENHEIT:
            snprintf( buf, len, "Temp: %3.1f °F\n", th.getTemperature() * 1.8f / 32.f );
            break;

        default:
            break;
        }
    }
}


/**
 * @fn UART_Logger
 * @brief Sample View implementation for displaying values on UART
 */

class UART_Logger : public IView
{
public:
    UART_Logger() { /* uart init code */}

    void update( const Thermometer & th)
    {
        const int len=40;
        char buf[len+1];
        format_temperature( buf, len, th );
        uart_puts( buf );
    }
};


/**
 * @fn display_lcd
 * @brief Sample View implementation displaying the thermometer value on a LCD
 */

class LCD_Logger : public IView
{
public:

    LCD_Logger() { /* lcd init code */ }

    void update( const Thermometer & th )
    {
        const int len=40;
        char buf[len+1];
        format_temperature( buf, len, th );

        lcd_gotoxy(0, 0);
        lcd_puts( buf );
    }
};


int main(int argc, char** argv)
{
    LCD_Logger  loggerLCD;
    UART_Logger loggerUART;

    class I2C port(1, 0xCD);

    Thermometer sensor( port );

    sensor.setType( Thermometer::TYPE_DS1621 );
    sensor.setUnit( Thermometer::UNIT_FAHRENHEIT );
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
