
#ifndef THERMOMETER_GENERIC_HPP_
#define THERMOMETER_GENERIC_HPP_

#include "IView.hpp"
#include "IThermometer.hpp"

/**
 * @class ThermometerGeneric
 * @brief A policy for generation of polymorphic thermometer classes.
 */

template< class Port, class DataModel >
class ThermometerGeneric : public IThermometer
{
    Port & m_port;
    DataModel m_model;

    static const int MAX_VIEWS=16;

    //! the views being notified about changes
    IView< IThermometer >* m_views[ MAX_VIEWS ];

    //! callback being called by the data model
    static void sensorChanged( void* );

public:

    ThermometerGeneric( Port & port );

    /**
     * @brief triggers updates of the thermometer
     */

    void update();


    /**
     * @brief selects the displaying unit
     */

    void setUnit( IThermometer::Unit );


    /**
     * @brief gets the thermometer's temperature
     */

    float getTemperature() const;


    /**
     * @brief gets the unit
     */

    IThermometer::Unit getUnit() const;

    /**
     * @brief gets the type of the sensor
     */

    IThermometer::Type getType() const;


    /**
     * @brief adds a view to a given thermometer
     */

    void addView( class IView<IThermometer> & view );


    /**
     * @brief removes a view from a given thermometer
     */

    void delView( class IView<IThermometer> & view );

    /**
     * @brief notifies about changed settings
     */

    void notifyViews();

};


#include "thermometer_generic_impl.hpp"


#endif // THERMOMETER_GENERIC_HPP_
