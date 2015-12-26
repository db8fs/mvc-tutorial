#ifndef SENSOR_DS1621_HPP_
#define SENSOR_DS1621_HPP_

#include "IThermometer.hpp"

/**
 * @class SensorDS1621
 * @brief Maxim DS1621
 */

class SensorDS1621
{
    //! sensor value [sensor's 9-bit representation]
    uint16_t m_value;

    //! temperature [deg C]
    uint16_t m_temperature;

    //! output unit
    IThermometer::Unit m_unit;

    //! observer object to notify about changes
    void* m_obj;

    //! observer callback
    void (*m_callback)( void* );

    //! notifies the observing object
    void notifyObserver();

public:
    SensorDS1621();


    //! destruction
    ~SensorDS1621();


    /**
     * @brief sets the sensor's value
     */

    void setValue( uint16_t );


    /**
     * @brief sets the unit for sensor values
     */

    void setUnit( IThermometer::Unit );



    /**
     * @brief gets the thermometer's temperature
     */

    float getTemperature() const;


    /**
     * @brief gets the unit of the temperature
     */

    IThermometer::Unit getUnit() const;

    /**
     * @brief gets the polymorphic type of the sensor
     */

    IThermometer::Type getType() const;


    /**
     * @brief sets an object observing data model changes
     */

    void setObserver( void* obj, void (*callback)(void*) );

};


#endif // SENSOR_DS1621_HPP
