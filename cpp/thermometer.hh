#ifndef THERMOMETER_HH_
#define THERMOMETER_HH_

/**
 * @class Thermometer
 * @brief
 */

class Thermometer
{
    class ThermometerData* m_model;

public:

    /**
     * @enum Type
     * @brief Selects the hardware backend for the used thermometer.
     */

    enum Type
    {
        TYPE_NONE=0,
        TYPE_DS1621=1
    };


    /**
     * @enum  Unit
     * @brief Part of the MVP Data Model of a thermometer
     */

    enum Unit
    {
        UNIT_CELSIUS=0,
        UNIT_FAHRENHEIT
    };


    //! initialization
    Thermometer( class I2C & dev );

    //! cleanup
    ~Thermometer();


    /**
     * @brief selects the data model for the given controller
     */

    void setModel( Type );

    /**
     * @brief triggers updates of the thermometer
     */

    void update();


    /**
     * @brief selects the displaying unit
     */

    void setUnit( Unit );


    /**
     * @brief adds a view to a given thermometer
     */

    void addView( class IView & );


    /**
     * @brief removes a view from a given thermometer
     */

    void delView( class IView & );


    /**
     * @brief gets the thermometer's temperature
     */

    float getTemperature() const;


    /**
     * @fn th_getunit
     * @brief gets the unit (@sa{enum thermo_unit})
     */

    Unit getUnit() const;


    /**
     * @fn thermometer_get_type
     * @brief gets the type (@sa{enum thermo_type})
     */

    Type getType() const;

};

#endif THERMOMETER_HH_
