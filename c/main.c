#include "thermometer.h"
#include <stdio.h>

/**
 * @fn format_temperature
 * @brief creates output string
 */

static void format_temperature( char* buf, int len, const struct thermo_controller* const th )
{
    if( thermometer_get_type( th ) == TYPE_DS1621 ) // sensor provides Celsius units
    {
        switch( thermometer_get_unit( th ) )
        {
        case UNIT_CELSIUS:
            snprintf( buf, len, "Temp: %3.1f °C\n", thermometer_get_temperature(th) );
            break;

        case UNIT_FAHRENHEIT:
            snprintf( buf, len, "Temp: %3.1f °F\n", thermometer_get_temperature(th) * 1.8f / 32.f );
            break;

        default:
            break;
        }
    }
}


/**
 * @fn display_uart
 * @brief Sample View implementation for displaying values on UART
 */

static void display_uart( const struct thermo_controller* const th )
{
    const int len=40;
    char buf[len+1];
    format_temperature( buf, len, th );
    uart_puts( buf );
}


/**
 * @fn display_lcd
 * @brief Sample View implementation displaying the thermometer value on a LCD
 */

static void display_lcd( const struct thermo_controller* const th )
{
    const int len=40;
    char buf[len+1];
    format_temperature( buf, len, th );

    lcd_gotoxy(0, 0);
    lcd_puts( buf );
}


int main(int argc, char** argv)
{
    struct thermo_controller* sensor = thermometer_init_i2c( 1, 0xCD );

    thermometer_set_model( sensor, TYPE_DS1621 );
    thermometer_set_unit( sensor, UNIT_FAHRENHEIT );
    thermometer_add_view( sensor, &display_uart );
    thermometer_add_view( sensor, &display_lcd );

    // ... lcd_init ... uart_init ...

    while(1)
    {
        thermometer_update( sensor );

        // wait 1 sec till next data acquisition
        sleep(1);
    }

    thermometer_cleanup_i2c( sensor );

    return 0;
}
