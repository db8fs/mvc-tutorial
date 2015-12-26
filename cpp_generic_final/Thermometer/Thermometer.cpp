
/**
 * @file Thermometer.cpp
 * @author Dipl.-Inf. Falk Schilling <falk.schilling.de@ieee.org>
 * @copyright LGPLv3
 */

#include <stdint.h>
#include <stdlib.h>

#include "I2C_Client.h"
#include "Thermometer.h"
#include "ThermometerGeneric.h"

#include "Sensor_DS1621.h"


/**
 * @brief Object factory for thermometer creation.
 */

static IThermometer* create( I2C_Client & dev, IThermometer::Type type )
{
    switch( type )
    {
    case IThermometer::TYPE_DS1621:
        return new ThermometerGeneric<I2C_Client, Sensor_DS1621>( dev );

    default:
        break;
    }

    // invalid parameters have been passed
    exit(0);
}


/**
 * @brief selects an I2C thermometer backend
 */

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


/**
 * @brief constructor specialization for I2C protocol
 */

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
