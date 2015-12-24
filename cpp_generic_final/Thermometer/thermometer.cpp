#include <stdint.h>
#include <stdlib.h>

#include "i2cclient.hpp"
#include "thermometer.hpp"

#include "thermometer_generic.hpp"
#include "sensor_ds1621.hpp"


/**
 * @brief Object factory for thermometer creation.
 */

static IThermometer* create( I2C_Client & dev, IThermometer::Type type )
{
    switch( type )
    {
    case IThermometer::TYPE_DS1621:
        return new ThermometerGeneric<I2C_Client, SensorDS1621>( dev );

    default:
        break;
    }

    // invalid parameters have been passed
    exit(0);
}

template<>
void Thermometer::setModel<I2C_Client>( I2C_Client & port,
                                        IThermometer::Type type )
{
    if( NULL != m_model )
    {
        if( m_model->getType() == type )
        {
            return;
        }

        delete m_model;
    }

    m_model = create( port, type );
}


// constructor specialization for I2C protocol
template<>
Thermometer::Thermometer<I2C_Client>(I2C_Client & dev, IThermometer::Type type)
: m_model(NULL)
{
    Thermometer::setModel<I2C_Client>( dev, type );
}


Thermometer::~Thermometer()
{
    delete m_model;
}


void Thermometer::update()
{
    m_model->update();
}


void Thermometer::setUnit( IThermometer::Unit unit )
{
    m_model->setUnit( unit );
}


void Thermometer::addView( IView<IThermometer> & view )
{
    m_model->addView( view );
}

void Thermometer::delView( IView<IThermometer> & view )
{
    m_model->delView( view );
}
