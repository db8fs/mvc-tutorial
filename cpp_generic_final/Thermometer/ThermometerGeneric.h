
#ifndef THERMOMETER_GENERIC_HPP_
#define THERMOMETER_GENERIC_HPP_

/**
 * @file ThermometerGeneric.hpp
 * @author Dipl.-Inf. Falk Schilling <falk.schilling.de@ieee.org>
 * @copyright LGPLv3
 */

#include "IView.hpp"
#include "IThermometer.hpp"


/**
 * @class ThermometerGeneric
 * @brief A MVP policy for generation of polymorphic thermometer classes.
 * @tparam Port - the physical port being the data source
 * @tparam DataModel - the sensor implementation to use
 */

template< class Port, class DataModel >
class ThermometerGeneric : public IThermometer
{
    //! reference to the physical port (data source)
    Port & m_port;

    //! sensor implementation
    DataModel m_model;

    //! maximum number of views that may be registered
    static const int MAX_VIEWS=16;

    //! the views being notified about changes
    IView< IThermometer >* m_views[ MAX_VIEWS ];

    //! callback being called by the data model
    static void sensorChanged( void* );

    /**
     * @brief notifies about changed settings
     */

    void notifyViews();

public:

    /**
     * @brief construction by type conversion using the given port
     */

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

};


#include "ThermometerGeneric_Private.h"


#endif // THERMOMETER_GENERIC_HPP_
