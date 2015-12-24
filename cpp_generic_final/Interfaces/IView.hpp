
#ifndef IVIEW_HH_
#define IVIEW_HH_

/**
 * @interface IView
 * @brief Implementers may observe an object
 */

template< class T >
class IView
{
public:
    virtual ~IView() {}

    virtual void update( const T & ) = 0;

};


#endif // IVIEW_HH_
