#ifndef THERMOMETER_HH_
#define THERMOMETER_HH_

/**
 * @file Thermometer.hpp
 * @author Dipl.-Inf. Falk Schilling <falk.schilling.de@ieee.org>
 * @copyright LGPLv3
 */

#include "IThermometer.hpp"

/**
 * @class Thermometer
 * @brief A flexible and simple to use software asset modelling a thermometer.
 * @detail Uses the MVC compound pattern to select the driver at runtime.
 */

class Thermometer
{
    //! the data model of the thermometer
    class IThermometer* m_model;

public:

    /**
     * @brief Policy for construction of a sensor with protocol autodetection
     * @tparam protocol type of the sensor
     */

    template< typename Port >
    Thermometer( Port &, IThermometer::Type );


    //! cleanup
    ~Thermometer();


    /**
     * @brief triggers updates of the thermometer
     */

    void update();


    /**
     * @brief gets the data model with read only access
     */

    const class IThermometer & getModel() const;


    /**
     * @brief selects the
     * @tparam the protocol type of the sensor
     */

    template< typename Port >
    void setModel( Port &, IThermometer::Type );


    /**
     * @brief selects the displaying unit
     */

    void setUnit( IThermometer::Unit );


    /**
     * @brief adds a view to a given thermometer
     */

    void addView( IView<IThermometer> & );


    /**
     * @brief removes a view from a given thermometer
     */

    void delView( IView<IThermometer> & );

};



#endif //THERMOMETER_HH_
