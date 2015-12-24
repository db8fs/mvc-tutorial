#ifndef SENSOR_DS1621_HPP_
#define SENSOR_DS1621_HPP_


/**
 * @class SensorDS1621
 * @brief Maxim DS1621
 */

class SensorDS1621
{
public:

    /**
     * @enum  Unit
     * @brief Part of the MVP Data Model of a thermometer
     */

    enum Unit
    {
        UNIT_CELSIUS=0,
        UNIT_FAHRENHEIT
    };

private:

    //! sensor value [sensor's 9-bit representation]
    uint16_t m_value;

    //! temperature [deg C]
    uint16_t m_temperature;

    //! output unit
    Unit m_unit;

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

    void setUnit( Unit );



    /**
     * @brief gets the thermometer's temperature
     */

    float getTemperature() const;


    /**
     * @brief gets the unit of the temperature
     */

    Unit getUnit() const;

    /**
     * @brief sets an object observing data model changes
     */

    void setObserver( void* obj, void (*callback)(void*) );

};


#endif // SENSOR_DS1621_HPP
