
#ifndef THERMOMETER_PRIVATE_HPP_
#define THERMOMETER_PRIVATE_HPP_

#include "IView.hpp"

/**
 * @class Thermometer
 * @brief Thin controller class data acquisition
 */

template< class Port, class DataModel >
class Thermometer
{
    Port & m_port;
    DataModel m_model;

    static const int MAX_VIEWS=16;

    //! the views being notified about changes
    IView< Thermometer >* m_views[ MAX_VIEWS ];

    //! callback being called by the data model
    static void sensorChanged( void* );

public:

    Thermometer( Port & port );

    /**
     * @brief triggers updates of the thermometer
     */

    void update();


    /**
     * @brief selects the displaying unit
     */

    void setUnit( typename DataModel::Unit unit );


    /**
     * @brief gets the thermometer's temperature
     */

    float getTemperature() const;


    /**
     * @brief gets the unit (@sa{enum thermo_unit})
     */

    typename DataModel::Unit getUnit() const;


    /**
     * @brief adds a view to a given thermometer
     */

    void addView( class IView<Thermometer> & view );


    /**
     * @brief removes a view from a given thermometer
     */

    void delView( class IView<Thermometer> & view );

    /**
     * @brief notifies about changed settings
     */

    void notifyViews();

};



template< class Port, class DataModel >
Thermometer<Port,DataModel>::Thermometer( Port & port )
: m_port(port),
    m_model()
{
    for(int i(0); i<MAX_VIEWS; ++i)
    {
        m_views[i] = NULL;
    }

    m_model.setObserver( this, &Thermometer<Port, DataModel>::sensorChanged );
}


template< class Port, class DataModel >
void Thermometer<Port,DataModel>::update()
{
    m_model.setValue( m_port.getValue() );
}


template< class Port, class DataModel >
void Thermometer<Port,DataModel>::setUnit( typename DataModel::Unit unit)
{
    m_model.setUnit( unit );
}



template< class Port, class DataModel >
float Thermometer<Port,DataModel>::getTemperature() const
{
    return m_model.getTemperature();
}


template< class Port, class DataModel >
typename DataModel::Unit Thermometer<Port,DataModel>::getUnit() const
{
    return m_model.getUnit();
}

template< class Port, class DataModel >
void Thermometer<Port,DataModel>::sensorChanged( void* obj )
{
    static_cast<Thermometer<Port, DataModel>* >( obj )->notifyViews();
}

template< class Port, class DataModel>
void Thermometer<Port,DataModel>::notifyViews()
{
    for( int i(0); i< Thermometer<Port,DataModel>::MAX_VIEWS; ++i )
    {
        if( m_views[i] != NULL )
        {
            m_views[i]->update( *this );
        }
    }
}

template< class Port, class DataModel>
void Thermometer<Port,DataModel>::addView( class IView< Thermometer > & view )
{
    for(int i(0); i< Thermometer<Port, DataModel>::MAX_VIEWS; ++i)
    {
        if( m_views[i] == NULL )
        {
            m_views[i] = &view;
            break;
        }
    }
}


template< class Port, class DataModel>
void Thermometer<Port,DataModel>::delView( class IView< Thermometer > & view )
{
    for(int i(0); i<Thermometer<Port,DataModel>::MAX_VIEWS; ++i)
    {
        if( m_views[i] == &view )
        {
            m_views[i] = NULL;
        }
    }
}



#endif // THERMOMETER_PRIVATE_HPP_
