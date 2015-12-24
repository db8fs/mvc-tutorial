#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "sensor_ds1621.hpp"


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

SensorDS1621::SensorDS1621()
    : m_value(0U),
      m_temperature(0.f),
      m_unit( IThermometer::UNIT_CELSIUS ),
      m_obj(NULL),
      m_callback(NULL)
{
}


SensorDS1621::~SensorDS1621()
{
}


void SensorDS1621::setValue( uint16_t value )
{
    if( value != SensorDS1621::m_value )
    {
        SensorDS1621::m_value = value;
        m_temperature = convertSensorValue( value );

        SensorDS1621::notifyObserver();
    }
}


void SensorDS1621::setUnit( IThermometer::Unit unit )
{
    if( unit != SensorDS1621::m_unit )
    {
        SensorDS1621::m_unit = unit;
        SensorDS1621::notifyObserver();
    }
}


float SensorDS1621::getTemperature() const
{
    if( SensorDS1621::m_unit == IThermometer::UNIT_FAHRENHEIT )
    {
        return convertToFahrenheit( m_temperature  );
    }

    return SensorDS1621::m_temperature;
}


IThermometer::Unit SensorDS1621::getUnit() const
{
    return SensorDS1621::m_unit;
}

IThermometer::Type SensorDS1621::getType() const
{
    return IThermometer::TYPE_DS1621;
}


void SensorDS1621::setObserver( void* obj, void (*callback)(void*) )
{
    m_obj = obj;
    m_callback = callback;
}

void SensorDS1621::notifyObserver()
{
    if( NULL != m_obj && NULL != m_callback)
    {
        m_callback( m_obj );
    }
}
