
#ifndef THERMOMETER_GENERIC_PRIVATE_HPP_
#define THERMOMETER_GENERIC_PRIVATE_HPP_

/**
 * @file ThermometerGenericPrivate.hpp
 * @author Falk Schilling <falk.schilling.de@ieee.org>
 * @copyright LGPLv3
 */

template< class Port, class DataModel >
ThermometerGeneric<Port,DataModel>::ThermometerGeneric( Port & port )
: m_port(port),
  m_model()
{
    for(int i(0); i<ThermometerGeneric<Port,DataModel>::MAX_VIEWS; ++i)
    {
        m_views[i] = NULL;
    }

    m_model.setObserver( this, &ThermometerGeneric<Port,DataModel>::sensorChanged );
}


template< class Port, class DataModel >
void ThermometerGeneric<Port,DataModel>::update()
{
    m_model.setValue( m_port.getValue() );
}


template< class Port, class DataModel >
void ThermometerGeneric<Port,DataModel>::setUnit( IThermometer::Unit unit)
{
    m_model.setUnit( unit );
}


template< class Port, class DataModel >
float ThermometerGeneric<Port,DataModel>::getTemperature() const
{
    return m_model.getTemperature();
}


template< class Port, class DataModel >
IThermometer::Unit ThermometerGeneric<Port,DataModel>::getUnit() const
{
    return m_model.getUnit();
}

template< class Port, class DataModel >
IThermometer::Type ThermometerGeneric<Port,DataModel>::getType() const
{
    return m_model.getType();
}

template< class Port, class DataModel >
void ThermometerGeneric<Port,DataModel>::sensorChanged( void* obj )
{
    static_cast<ThermometerGeneric<Port,DataModel>* >( obj )->notifyViews();
}

template< class Port, class DataModel>
void ThermometerGeneric<Port,DataModel>::notifyViews()
{
    for( int i(0); i< ThermometerGeneric<Port,DataModel>::MAX_VIEWS; ++i )
    {
        if( m_views[i] != NULL )
        {
            m_views[i]->update( *this );
        }
    }
}

template< class Port, class DataModel>
void ThermometerGeneric<Port,DataModel>::addView( class IView< IThermometer > & view )
{
    for(int i(0); i< ThermometerGeneric<Port, DataModel>::MAX_VIEWS; ++i)
    {
        if( m_views[i] == NULL )
        {
            m_views[i] = &view;
            break;
        }
    }
}


template< class Port, class DataModel>
void ThermometerGeneric<Port,DataModel>::delView( class IView< IThermometer > & view )
{
    for(int i(0); i<ThermometerGeneric<Port,DataModel>::MAX_VIEWS; ++i)
    {
        if( m_views[i] == &view )
        {
            m_views[i] = NULL;
        }
    }
}



#endif // THERMOMETER_GENERIC_PRIVATE_HPP_
