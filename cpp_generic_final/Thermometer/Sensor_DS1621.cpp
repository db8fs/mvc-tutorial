#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "Sensor_DS1621.h"


static float convertSensorValue( uint16_t value )
{
    float temp( (float)(char)((value >> 8) & 0xFF ) );
    temp += (float)(value & 0xFF) / 256.f;
    return temp;
}

static float convertToFahrenheit( float value )
{
    return value * 1.8f / 32.f;
}

Sensor_DS1621::Sensor_DS1621()
    : m_value(0U),
      m_temperature(0.f),
      m_unit( IThermometer::UNIT_CELSIUS ),
      m_obj(NULL),
      m_callback(NULL)
{
}


Sensor_DS1621::~Sensor_DS1621()
{
}


void Sensor_DS1621::setValue( uint16_t value )
{
    if( value != Sensor_DS1621::m_value )
    {
        Sensor_DS1621::m_value = value;
        m_temperature = convertSensorValue( value );

        Sensor_DS1621::notifyObserver();
    }
}


void Sensor_DS1621::setUnit( IThermometer::Unit unit )
{
    if( unit != Sensor_DS1621::m_unit )
    {
        Sensor_DS1621::m_unit = unit;
        Sensor_DS1621::notifyObserver();
    }
}


float Sensor_DS1621::getTemperature() const
{
    if( Sensor_DS1621::m_unit == IThermometer::UNIT_FAHRENHEIT )
    {
        return convertToFahrenheit( m_temperature  );
    }

    return Sensor_DS1621::m_temperature;
}


IThermometer::Unit Sensor_DS1621::getUnit() const
{
    return Sensor_DS1621::m_unit;
}

IThermometer::Type Sensor_DS1621::getType() const
{
    return IThermometer::TYPE_DS1621;
}


void Sensor_DS1621::setObserver( void* obj, void (*callback)(void*) )
{
    m_obj = obj;
    m_callback = callback;
}

void Sensor_DS1621::notifyObserver()
{
    if( NULL != m_obj && NULL != m_callback)
    {
        m_callback( m_obj );
    }
}
