
#ifndef IVIEW_HH_
#define IVIEW_HH_

/**
 * @interface IView
 * @brief Implementers may observe a thermometer
 */

template< class Thermometer >
class IView
{
public:
    virtual ~IView() {}

    virtual void update( const Thermometer & ) = 0;

};


#endif // IVIEW_HH_
