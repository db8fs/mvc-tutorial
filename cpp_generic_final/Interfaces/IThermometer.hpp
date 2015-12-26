
#ifndef ITHERMOMETERMODEL_HPP_
#define ITHERMOMETERMODEL_HPP_

#include "IView.hpp"

/**
 * @interface IThermometer
 * @brief Polymorphic base class grouping common thermometer methods.
 */

class IThermometer
{
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


    virtual ~IThermometer() {}

    /**
     * @brief triggers updates of the thermometer
     */

    virtual void update() = 0;


    /**
     * @brief selects the displaying unit
     */

    virtual void setUnit( IThermometer::Unit unit ) = 0;


    /**
     * @brief gets the thermometer's temperature
     */

    virtual float getTemperature() const = 0;


    /**
     * @brief gets the unit (@sa{enum thermo_unit})
     */

    virtual IThermometer::Unit getUnit() const = 0;


    /**
     * @brief adds a view to a given thermometer
     */

    virtual void addView( IView<IThermometer> & view ) = 0;


    /**
     * @brief removes a view from a given thermometer
     */

    virtual void delView( IView<IThermometer> & view ) = 0;

    /**
     * @brief notifies about changed settings
     */

    virtual void notifyViews() = 0;

    /**
     * @brief gets the polymorphic type of the thermometer
     */

    virtual IThermometer::Type getType() const = 0;
};


#endif // ITHERMOMETERMODEL_HPP_
